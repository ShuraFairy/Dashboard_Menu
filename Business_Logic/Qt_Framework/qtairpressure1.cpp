#include "qtairpressure1.h"
#include <QDebug>
#include <QTimer>
#include <iomanip>
#include <sstream>
#include <unistd.h>

using namespace std;

mutex QtAirPressure1::m_build_mutex;
QtAirPressure1* QtAirPressure1::m_ptr_instance(nullptr);

QtAirPressure1::QtAirPressure1(QObject* parent)
    : QObject(parent)
    , _air_pressure_1(-AIRPRESSURE_MIN_ANGLE)
{
    if (!m_ptr_instance)
        m_ptr_instance = this;
    m_ptr_cached_msgs = HmiHandler::getInstance();
    init_subscribe();
}

QtAirPressure1::~QtAirPressure1()
{
    qDebug() << "QtAirpressure1 Destructor called!!!" << Qt::endl;
}

QtAirPressure1* QtAirPressure1::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = new QtAirPressure1;
    }
    return m_ptr_instance;
    CATCH_BLOCK
}

void QtAirPressure1::update_gui()
{
    TRY_BLOCK
    qreal air_pressure1_value;
    if (_state == QmlState::QMLSTATE_NORMAL)
    {
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_AIR1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            AIR1_t* ptr_air = reinterpret_cast<AIR1_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_AIR1_ID));
            air_pressure1_value = (ptr_air->service_brake_airpressure_circuit2 * AIRPRESSURE_FACTOR * AIRPRESSURE_ANGLE / 100) - AIRPRESSURE_MIN_ANGLE;

            if(air_pressure1_value > AIRPRESSURE_MAX_ANGLE)
                air_pressure1_value = AIRPRESSURE_MAX_ANGLE;

            set_air_pressure_1(air_pressure1_value);
        }
        else
            set_air_pressure_1(-AIRPRESSURE_MIN_ANGLE);
    }
    CATCH_BLOCK
}

bool QtAirPressure1::update_info(uint32_t _id)
{
    TRY_BLOCK
    if (_state != QmlState::QMLSTATE_NORMAL)
        return false;

    if (_id == HMIHANDLER_AIR1_ID)
        update_gui();

    return true;
    CATCH_BLOCK
}

qreal QtAirPressure1::get_air_pressure_1() const
{
    TRY_BLOCK
    return _air_pressure_1;
    CATCH_BLOCK
}

void QtAirPressure1::set_air_pressure_1(qreal new_air_pressure_1)
{
    TRY_BLOCK
    if (!(qFuzzyCompare(_air_pressure_1, new_air_pressure_1))) {
        _air_pressure_1 = new_air_pressure_1;
        airpressure1_data = _air_pressure_1;
        emit air_pressure_1_changed();
        emit air_pressure1_telltale(airpressure1_data);
    }
    CATCH_BLOCK
}

void QtAirPressure1::qml_responses(int value)
{
    TRY_BLOCK
    QmlState state = (QmlState)value;
    QTimer* timer;
    _state = state;

    if (state == QmlState::QMLSTATE_INPROGRESS)
        qDebug() << "Loading In Progress" << Qt::endl;
    else if(state == QmlState::QMLSTATE_LOADING_COMPLETED)
    {
        qDebug() << "Loading Completed" << Qt::endl;
        timer = new QTimer();
        set_air_pressure_1(AIRPRESSURE_MAX_ANGLE);

        connect(timer, &QTimer::timeout, [=] {
            set_air_pressure_1(-AIRPRESSURE_MIN_ANGLE);
            _state = QmlState::QMLSTATE_NORMAL;
            timer->stop();
            delete timer;
        });

        timer->start(2000);
    }
    CATCH_BLOCK
}

void QtAirPressure1::init_subscribe()
{
    TRY_BLOCK
    auto ptrnotifer = subscribe_notifer::get_instance();
    ptrnotifer->subscribe(HMIHANDLER_AIR1_ID, this);
    CATCH_BLOCK
}
