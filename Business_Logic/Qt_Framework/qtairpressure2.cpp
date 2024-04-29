#include "qtairpressure2.h"

mutex QtAirPressure2::m_build_mutex;
QtAirPressure2* QtAirPressure2::m_ptr_instance(nullptr);

QtAirPressure2::QtAirPressure2(QObject* parent)
    : QObject{ parent }
    , _air_pressure_2(AIRPRESSURE_MIN_ANGLE)
{
    if (!m_ptr_instance)
        m_ptr_instance = this;
    m_ptr_cached_msgs = HmiHandler::getInstance();
    init_subscribe();
}

QtAirPressure2::~QtAirPressure2()
{
    qDebug() << "QtAirpressure2 Destructor called!!!" << Qt::endl;
}

QtAirPressure2* QtAirPressure2::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = new QtAirPressure2;
    }
    return m_ptr_instance;
    CATCH_BLOCK
}

void QtAirPressure2::update_gui()
{
    TRY_BLOCK
    qreal air_pressure2_value;
    if (_state == QmlState::QMLSTATE_NORMAL)
    {
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_AIR1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            AIR1_t* ptr_msg = reinterpret_cast<AIR1_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_AIR1_ID));
            air_pressure2_value = (ptr_msg->service_brake_airpressure_circuit1 * AIRPRESSURE_FACTOR * AIRPRESSURE_ANGLE / 100) - AIRPRESSURE_MIN_ANGLE;

            if (air_pressure2_value > AIRPRESSURE_MAX_ANGLE)
                air_pressure2_value = AIRPRESSURE_MAX_ANGLE;

            set_air_pressure_2(air_pressure2_value);
        }
        else
            set_air_pressure_2(-AIRPRESSURE_MIN_ANGLE);
    }
    CATCH_BLOCK
}

bool QtAirPressure2::update_info(uint32_t _id)
{
    TRY_BLOCK
    if (_state != QmlState::QMLSTATE_NORMAL)
        return false;
    if (_id == HMIHANDLER_AIR1_ID)
        update_gui();

    return true;
    CATCH_BLOCK
}

qreal QtAirPressure2::get_air_pressure_2() const
{
    TRY_BLOCK
    return _air_pressure_2;
    CATCH_BLOCK
}

void QtAirPressure2::set_air_pressure_2(qreal new_air_pressure_2)
{
    TRY_BLOCK
    if (!(qFuzzyCompare(_air_pressure_2, new_air_pressure_2))) {
        _air_pressure_2 = new_air_pressure_2;
        airpressure2_data = _air_pressure_2;
        emit air_pressure_2_changed();
        emit air_pressure2_telltale(airpressure2_data);
    }
    CATCH_BLOCK
}

void QtAirPressure2::qml_responses(int value)
{
    TRY_BLOCK
    QmlState state = (QmlState)value;
    QTimer* timer;
    _state = state;
    if (state == QmlState::QMLSTATE_INPROGRESS)
    {
        qDebug() << "Loading In Progress" << Qt::endl;
    }
    else if(state == QmlState::QMLSTATE_LOADING_COMPLETED)
    {
        qDebug() << "Loading Completed" << Qt::endl;
        timer = new QTimer();
        set_air_pressure_2(AIRPRESSURE_MAX_ANGLE);
        connect(timer, &QTimer::timeout, [=] {
            set_air_pressure_2(-AIRPRESSURE_MIN_ANGLE);
            _state = QmlState::QMLSTATE_NORMAL;
            timer->stop();
            delete timer;
        });
        timer->start(2000);
    }
    CATCH_BLOCK
}

void QtAirPressure2::init_subscribe()
{
    TRY_BLOCK
    auto ptrnotifer = subscribe_notifer::get_instance();
    ptrnotifer->subscribe(HMIHANDLER_AIR1_ID, this);
    CATCH_BLOCK
}
