#include "qtspeedometer.h"
#include <QDebug>
#include <QTimer>
#include <unistd.h>

mutex QtSpeedometer::m_build_mutex;
QtSpeedometer* QtSpeedometer::m_ptr_instance(nullptr);

QtSpeedometer::QtSpeedometer(QObject* parent)
    : QObject{ parent }
    , _filter_buffer()
    , _speed(MIN_SPEEDOMETER_ANGLE)
{
    if (!m_ptr_instance)
        m_ptr_instance = this;
    m_ptr_cached_msg_handler = HmiHandler::getInstance();
    filter_init();
    init_subscribe();
}

QtSpeedometer::~QtSpeedometer()
{
    qDebug() << "QtSpeedometer Destructor called!!!" << Qt::endl;
}

QtSpeedometer* QtSpeedometer::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = new QtSpeedometer;
    }
    return m_ptr_instance;
    CATCH_BLOCK
}

void QtSpeedometer::update_gui()
{
    TRY_BLOCK
    qreal temp_speed;
    can_msg_state_e is_new_data = m_ptr_cached_msg_handler->get_ptr_to_msg(HMIHANDLER_CCVS1_ID)->get_state();
    if (_state == QmlState::QMLSTATE_NORMAL)
    {
        if (is_new_data == CAN_MESSAGE_STATE_OK)
        {
            CCVS1_t* ptr_msg = reinterpret_cast<CCVS1_t*>(m_ptr_cached_msg_handler->get_data_from_msg(HMIHANDLER_CCVS1_ID));
            if(ptr_msg->wheel_based_vehicle_speed == 0xFFFF)
                return;

            temp_speed = static_cast<qreal>(ptr_msg->wheel_based_vehicle_speed * SPEEDOMETER_FACTOR);

            if (temp_speed > MAX_SPEEDOMETER_ANGLE)
                temp_speed = MAX_SPEEDOMETER_ANGLE;

            set_speed(temp_speed);
        }
        else
            set_speed(MIN_SPEEDOMETER_ANGLE);
    }
    CATCH_BLOCK
}

bool QtSpeedometer::update_info(uint32_t _id)
{
    TRY_BLOCK
    if (_state != QmlState::QMLSTATE_NORMAL)
        return false;
    if (_id == HMIHANDLER_CCVS1_ID)
        update_gui();
    return true;
    CATCH_BLOCK
}

qreal QtSpeedometer::get_speed() const
{
    TRY_BLOCK
    return _speed;
    CATCH_BLOCK
}

void QtSpeedometer::set_speed(qreal new_speed)
{
    TRY_BLOCK
    if (_speed != new_speed)
    {
        _speed = new_speed;
    //_speed = static_cast<qreal>(mt_dsp_mavg_f32_calc(&_gauge_filter, static_cast<float>(new_speed)));
        emit speed_changed();
    }
    CATCH_BLOCK
}

void QtSpeedometer::qml_responses(int value)
{
    TRY_BLOCK
    QmlState state = (QmlState)value;
    QTimer* timer;
    _state = state;

    if (state == QMLSTATE_INPROGRESS){
        qDebug() << "Loading In Progress" << Qt::endl;
    }else if(state == QMLSTATE_LOADING_COMPLETED){
        qDebug() << "Loading Completed" << Qt::endl;
        timer = new QTimer();
        set_speed(MAX_SPEEDOMETER_ANGLE);

        connect(timer, &QTimer::timeout, [=] {
            set_speed(MIN_SPEEDOMETER_ANGLE);
            _state = QmlState::QMLSTATE_NORMAL;
            timer->stop();
            delete timer;
        });
        timer->start(2000);
    }
    CATCH_BLOCK
}

void QtSpeedometer::init_subscribe()
{
    TRY_BLOCK
    auto ptr_notifer = subscribe_notifer::get_instance();
    ptr_notifer->subscribe(HMIHANDLER_CCVS1_ID, this);
    CATCH_BLOCK
}

void QtSpeedometer::filter_init()
{
    TRY_BLOCK
    _gauge_filter.window_size = QTSPEEDOMETER_GAUGE_FILTER_WINDOW_SIZE;
    _gauge_filter.window_buffer = _filter_buffer;
    mt_dsp_mavg_f32_init(&_gauge_filter);
    CATCH_BLOCK
}
