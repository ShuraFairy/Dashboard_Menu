#include "qtenginemeter.h"

mutex QtEngineMeter::m_build_mutex;
QtEngineMeter* QtEngineMeter::m_ptr_instance(nullptr);

QtEngineMeter::QtEngineMeter(QObject* parent)
    : QObject { parent }
    , _engine_speed(MIN_ENGINESPEED_ANGLE)
    , _filter_buffer()
{
    if (!m_ptr_instance)
        m_ptr_instance = this;
    m_ptr_cached_msgs = HmiHandler::getInstance();
    filter_init();
    init_subscribe();
}

QtEngineMeter::~QtEngineMeter()
{
    qDebug() << "QtEnginemeter Destructor called!!!" << Qt::endl;
}

QtEngineMeter* QtEngineMeter::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = new QtEngineMeter;
    }
    return m_ptr_instance;
    CATCH_BLOCK
}

void QtEngineMeter::update_gui()
{
    TRY_BLOCK
    if (_state == QmlState::QMLSTATE_NORMAL)
    {
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_EEC1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            EEC1_t* ptr_msg = reinterpret_cast<EEC1_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_EEC1_ID));
            qreal temp_engine_speed = ptr_msg->eng_speed * ENGINESPEED_FACTOR;

            set_engine_speed(temp_engine_speed);
        }
        else
            set_engine_speed(MIN_ENGINESPEED_ANGLE);
    }
    CATCH_BLOCK
}

bool QtEngineMeter::update_info(uint32_t _id)
{
    TRY_BLOCK
    if (_state != QmlState::QMLSTATE_NORMAL)
        return false;
    if (_id == HMIHANDLER_EEC1_ID)
        update_gui();
    return true;
    CATCH_BLOCK
}

qreal QtEngineMeter::get_engine_speed() const
{
    TRY_BLOCK
    return _engine_speed;
    CATCH_BLOCK
}

void QtEngineMeter::set_engine_speed(qreal new_engine_Speed)
{
    TRY_BLOCK
    if (_engine_speed != new_engine_Speed)
    {
        _engine_speed = new_engine_Speed;
        emit engine_speed_changed();
    }
    CATCH_BLOCK
}

void QtEngineMeter::qml_responses(int value)
{
    TRY_BLOCK
    QmlState state = (QmlState)value;
    QTimer* timer;
    _state = state;
    if(state == QmlState::QMLSTATE_INPROGRESS)
        qDebug() << "Loading In Progress" << Qt::endl;
    else if(state == QmlState::QMLSTATE_LOADING_COMPLETED)
    {
        qDebug() << "Loading Completed" << Qt::endl;
        timer = new QTimer();
        set_engine_speed(MAX_ENGINESPEED_ANGLE);

        connect(timer, &QTimer::timeout, [=] {
            set_engine_speed(MIN_ENGINESPEED_ANGLE);
            _state = QmlState::QMLSTATE_NORMAL;
            timer->stop();
            delete timer;
        });

        timer->start(2000);

    }
    CATCH_BLOCK
}

void QtEngineMeter::init_subscribe()
{
    TRY_BLOCK
    auto ptr_notifer = subscribe_notifer::get_instance();
    ptr_notifer->subscribe(HMIHANDLER_EEC1_ID, this);
    CATCH_BLOCK
}

void QtEngineMeter::filter_init()
{
    TRY_BLOCK
    _gauge_filter.window_size = QTENGINEMETER_GAUGE_FILTER_WINDOW_SIZE;
    _gauge_filter.window_buffer = _filter_buffer;
    mt_dsp_mavg_f32_init(&_gauge_filter);
    CATCH_BLOCK
}
