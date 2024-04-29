#include "qttelltales.h"

#define CONCAT_PATH ":/"
#define AIRPRESSURE_DIAL_ANGLE 63.36
#define VALID_VALUE "1"
#define INIT_VALUE "0"
#define BUSDOOR_MAX 4
#define DOOR_CLOSE "1"
#define STRUCT_UNIQUE_MEMBERS 8
#define STRUCT_DOOR_MEMBERS 14
#define BUSDOOR_IMAGE_STATIC "STATIC"
#define BUSDOOR_IMAGE_DYNAMIC "DYNAMIC"
#define BUSDOOR_STATUS_CLOSED "CLOSED"
#define BUSDOOR_STATUS_REQUEST "REQUEST"
#define BUSDOOR_STATUS_OPENING "OPENING"
#define BUSDOOR_STATUS_OPENED "OPENED"
#define BUSDOOR_STATUS_CLOSING "CLOSING"
#define BUSDOOR_STATUS_ERROR "ERROR"
#define BUSDOOR_STATUS_OBSTACLE_DETECT "OBSTACLE_DETECT"
#define BUSDOOR_PATH_CLOSED "/iC12_doors_close"
#define BUSDOOR_PATH_REQUEST "/iC12_doors_close_yellow.png"
#define BUSDOOR_PATH_LEFT "/iC12_door_left_red.png"
#define BUSDOOR_PATH_RIGHT "/iC12_door_right_red.png"
#define BUSDOOR_PATH_OBSTACLE "/iC12_doors_passenger.png"
#define BUSDOOR_PATH_ERROR "/iC12_doors_attention_red.png"

static uint8_t door_status = 0;

using std::vector;

mutex QtTelltales::m_build_mutex;
QtTelltales* QtTelltales::m_ptr_instance = nullptr;

QtTelltales::QtTelltales(QObject* parent)
    : QObject{ parent }
    , _map_telltale_data()
    , _bus_doors_data()
    , map_telltale_slots()
    //, check_door_status(false)
{
    if (!m_ptr_instance)
        m_ptr_instance = this;
    _temp_fuel_level = 0;

    json_handler = QtJsonHandler::get_instance();
    m_ptr_cached_msgs = HmiHandler::getInstance();
    json_handler->init();
    ptr_map_json = json_handler->get_json_data();

    init_telltales();
    update_map_telltale_data();
    update_map_init_data();

    update_all_telltale_visiblity(false);

    initialize_busdoors();
    set_bus_door_data(_bus_door_data);

//    _timer_door = new QTimer(this);
//    connect(_timer_door, SIGNAL(timeout()), this, SLOT(door_timer()));
    init_subscribe();
}

QtTelltales::~QtTelltales()
{
//    if (_timer_door->isActive())
//        delete _timer_door;
    qDebug() << "QtTelltale Destructor called!!!" << Qt::endl;
}

QtTelltales* QtTelltales::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = new QtTelltales;
    }
    return m_ptr_instance;
    CATCH_BLOCK
}
void QtTelltales::update_map_telltale_data()
{
    TRY_BLOCK
    map<QString, QtJsonHandler::JsonData>* map_json_data = json_handler->get_json_data();
    uint8_t telltale_position = 0;
    bool check_record = false;

    for (const auto &itterator : *map_json_data)
    {
        telltale_position = itterator.second.position;
        check_record = check_if_record_exists(telltale_position);

        if (check_record)
            _map_telltale_data[telltale_position] = {.telltale_name = itterator.second.symbol_number,
                                                     .telltale_position = itterator.second.position,
                                                     .category = itterator.second.telltale_category,
                                                     .priority = itterator.second.telltale_priority,
                                                     .telltale_color = itterator.second.colors[0],
                                                     .telltale_image_path = itterator.second.telltale_path
            };
    }
    CATCH_BLOCK
}

bool QtTelltales::check_if_record_exists(uint8_t telltale_position)
{
    TRY_BLOCK
    return (_map_telltale_data.find(telltale_position) == _map_telltale_data.end());
    CATCH_BLOCK
}

QtTelltales::TelltaleDataInit* QtTelltales::get_telltale_position(uint8_t telltale_position)
{
    TRY_BLOCK
    return &_map_telltale_data[telltale_position];
    CATCH_BLOCK
}

qreal QtTelltales::get_current() const
{
    TRY_BLOCK
    return _current;
    CATCH_BLOCK
}

void QtTelltales::set_current(qreal current)
{
    TRY_BLOCK
    if (!qFuzzyCompare(_current, current))
    {
        _current = current;
        emit current_changed();
    }
    CATCH_BLOCK
}

qreal QtTelltales::get_voltage() const
{
    TRY_BLOCK
    return _voltage;
    CATCH_BLOCK
}

void QtTelltales::set_voltage(qreal voltage)
{
    TRY_BLOCK
    if (!qFuzzyCompare(_voltage, voltage))
    {
        _voltage = voltage;
        emit voltage_changed();
    }
    CATCH_BLOCK
}

void QtTelltales::get_airpressure1_data(const qreal air_pressure1_data)
{
    TRY_BLOCK
    set_dialguage1(air_pressure1_data > AIRPRESSURE_DIAL_ANGLE);
    CATCH_BLOCK
}

void QtTelltales::get_airpressure2_data(const qreal air_pressure2_data)
{
    TRY_BLOCK
    set_dialguage2(air_pressure2_data > AIRPRESSURE_DIAL_ANGLE);
    CATCH_BLOCK
}

void QtTelltales::qml_responses(int value)
{
    TRY_BLOCK
    QmlState state = (QmlState)value;
    QTimer* timer;
    bool visibility;
    _state = state;

    switch (state) {
    case QmlState::QMLSTATE_INPROGRESS:
        qDebug() << "Loading In Progress" << Qt::endl;
        break;
    case QmlState::QMLSTATE_LOADING_COMPLETED: {
        qDebug() << "Loading Completed" << Qt::endl;
        visibility = true;
        timer = new QTimer();
        update_all_telltale_visiblity(visibility);
        if (visibility)
            visibility = false;
        connect(timer, &QTimer::timeout, [=] {
            update_all_telltale_visiblity(visibility);
            _state = QmlState::QMLSTATE_NORMAL;
            timer->stop();
//            if (_timer_door->isActive())
//                _timer_door->start(1000);
            delete timer;
        });
        timer->start(2000);
        break;
    }
    case QmlState::QMLSTATE_NORMAL:
//        if (!_timer_door)
//           _timer_door = new QTimer(this);
//        _timer_door->start(2000);
        break;
    case QmlState::QMLSTATE_MENU:
        break;
    default:
        break;
    }
    CATCH_BLOCK
}

bool QtTelltales::get_dialguage1() const
{
    TRY_BLOCK
    return _dialguage1;
    CATCH_BLOCK
}

void QtTelltales::set_dialguage1(bool newDialguage1)
{
    TRY_BLOCK
    if (_dialguage1 != newDialguage1)
    {
        _dialguage1 = newDialguage1;
        emit dialguage1_Changed();
    }
    CATCH_BLOCK
}

bool QtTelltales::get_dialguage2() const
{
    TRY_BLOCK
    return _dialguage2;
    CATCH_BLOCK
}

void QtTelltales::set_dialguage2(bool newDialguage2)
{
    TRY_BLOCK
    if (_dialguage2 != newDialguage2)
    {
        _dialguage2 = newDialguage2;
        emit dialguage2_Changed();
    }
    CATCH_BLOCK
}

void QtTelltales::update_all_telltale_visiblity(bool visibility)
{
    TRY_BLOCK
    QString visible;
    telltale_slot functptr;

    visible = (visibility) ? "true" : "false";

    TelltaleDataInit* telltale_init_data;
    for (auto itterator : map_telltale_slots)
    {
        telltale_init_data = get_telltale_position(itterator.first);
        telltale_pos[0][0] = telltale_init_data->telltale_image_path;
        telltale_pos[0][1] = visible;
        telltale_pos[0][2] = telltale_init_data->telltale_color;
        functptr = itterator.second;
        (this->*functptr)(telltale_pos);
    }
    CATCH_BLOCK
}

const QList<QStringList>& QtTelltales::get_bus_door_data() const
{
    TRY_BLOCK
    return _bus_door_data;
    CATCH_BLOCK
}

void QtTelltales::set_bus_door_data(const QList<QStringList>& newBus_door_data)
{
    TRY_BLOCK
    _bus_door_data = newBus_door_data;
    emit bus_door_data_Changed();
    CATCH_BLOCK
}

void QtTelltales::initialize_busdoors()
{
    TRY_BLOCK
    _bus_doors_data.insert(0, QStringList({BUSDOOR_PATH_CLOSED, "NA", "CLOSED", "STATIC"}));
    set_bus_door1(_bus_doors_data);
    set_bus_door2(_bus_doors_data);
    set_bus_door3(_bus_doors_data);
    set_bus_door4(_bus_doors_data);
    CATCH_BLOCK
}

void QtTelltales::update_bus_doors()
{
    TRY_BLOCK
    DC2_t* msg_ptr = nullptr;
    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_DC2_ID)->get_state() != CAN_MESSAGE_STATE_TIMEOUT)
        msg_ptr = reinterpret_cast<DC2_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_DC2_ID));

    _bus_doors_data[0][0] = BUSDOOR_PATH_CLOSED;
    _bus_doors_data[0][1] = "NA";
    _bus_doors_data[0][2] = BUSDOOR_STATUS_CLOSED;
    _bus_doors_data[0][3] = BUSDOOR_IMAGE_STATIC;

    if (msg_ptr)
    {
        if (msg_ptr->door1_request)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_REQUEST;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_REQUEST;
        }
        else if (msg_ptr->door1_error)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_ERROR;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_ERROR;
        }
        else if (msg_ptr->door1_locked)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_OBSTACLE;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_OBSTACLE_DETECT;
        }
        else if (msg_ptr->door1_closing || msg_ptr->door1_opened || msg_ptr->door1_opening)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_LEFT;
            _bus_doors_data[0][1] = BUSDOOR_PATH_RIGHT;
            _bus_doors_data[0][3] = BUSDOOR_IMAGE_DYNAMIC;
            if (msg_ptr->door1_closing)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_CLOSING;
            if (msg_ptr->door1_opened)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_OPENED;
            if (msg_ptr->door1_opening)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_OPENING;
        }
    }
    set_bus_door1(_bus_doors_data);

    _bus_doors_data[0][0] = BUSDOOR_PATH_CLOSED;
    _bus_doors_data[0][1] = "NA";
    _bus_doors_data[0][2] = BUSDOOR_STATUS_CLOSED;
    _bus_doors_data[0][3] = BUSDOOR_IMAGE_STATIC;
    if (msg_ptr)
    {
        if (msg_ptr->door2_request)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_REQUEST;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_REQUEST;
        }
        else if (msg_ptr->door2_error)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_ERROR;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_ERROR;
        }
        else if (msg_ptr->door2_locked)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_OBSTACLE;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_OBSTACLE_DETECT;
        }
        else if (msg_ptr->door2_closing || msg_ptr->door2_opened || msg_ptr->door2_opening)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_LEFT;
            _bus_doors_data[0][1] = BUSDOOR_PATH_RIGHT;
            _bus_doors_data[0][3] = BUSDOOR_IMAGE_DYNAMIC;
            if (msg_ptr->door2_closing)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_CLOSING;
            if (msg_ptr->door2_opened)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_OPENED;
            if (msg_ptr->door2_opening)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_OPENING;
        }
    }
    set_bus_door2(_bus_doors_data);

    _bus_doors_data[0][0] = BUSDOOR_PATH_CLOSED;
    _bus_doors_data[0][1] = "NA";
    _bus_doors_data[0][2] = BUSDOOR_STATUS_CLOSED;
    _bus_doors_data[0][3] = BUSDOOR_IMAGE_STATIC;
    if (msg_ptr)
    {
        if (msg_ptr->door3_request)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_REQUEST;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_REQUEST;
        }
        else if (msg_ptr->door3_error)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_ERROR;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_ERROR;
        }
        else if (msg_ptr->door3_locked)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_OBSTACLE;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_OBSTACLE_DETECT;
        }
        else if (msg_ptr->door3_closing || msg_ptr->door3_opened || msg_ptr->door3_opening)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_LEFT;
            _bus_doors_data[0][1] = BUSDOOR_PATH_RIGHT;
            _bus_doors_data[0][3] = BUSDOOR_IMAGE_DYNAMIC;
            if (msg_ptr->door3_closing)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_CLOSING;
            if (msg_ptr->door3_opened)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_OPENED;
            if (msg_ptr->door3_opening)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_OPENING;
        }
    }
    set_bus_door3(_bus_doors_data);

    _bus_doors_data[0][0] = BUSDOOR_PATH_CLOSED;
    _bus_doors_data[0][1] = "NA";
    _bus_doors_data[0][2] = BUSDOOR_STATUS_CLOSED;
    _bus_doors_data[0][3] = BUSDOOR_IMAGE_STATIC;

    if (msg_ptr)
    {
        if (msg_ptr->door4_request)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_REQUEST;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_REQUEST;
        }
        else if (msg_ptr->door4_error)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_ERROR;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_ERROR;
        }
        else if (msg_ptr->door4_locked)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_OBSTACLE;
            _bus_doors_data[0][2] = BUSDOOR_STATUS_OBSTACLE_DETECT;
        }
        else if (msg_ptr->door4_closing || msg_ptr->door4_opened || msg_ptr->door4_opening)
        {
            _bus_doors_data[0][0] = BUSDOOR_PATH_LEFT;
            _bus_doors_data[0][1] = BUSDOOR_PATH_RIGHT;
            _bus_doors_data[0][3] = BUSDOOR_IMAGE_DYNAMIC;
            if (msg_ptr->door4_closing)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_CLOSING;
            if (msg_ptr->door4_opened)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_OPENED;
            if (msg_ptr->door4_opening)
                _bus_doors_data[0][2] = BUSDOOR_STATUS_OPENING;
        }
    }
    set_bus_door4(_bus_doors_data);
    CATCH_BLOCK
}
void QtTelltales::update_all_telltales()
{
    TRY_BLOCK
    uint8_t value;

    for(auto it : *ptr_map_json)
    {
        if (_map_telltale_data[it.second.position].priority >= it.second.telltale_priority
                || _map_telltale_data[it.second.position].telltale_color == INIT_COLOR_TRANSPARENT)
        {
            if (it.second.telltale_category == TELLTALE_A
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_A_ID)->is_updated())
                {
                    TT_GRP_A_t* msg_grpa = reinterpret_cast<TT_GRP_A_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_A_ID));

                    if (it.second.symbol_number == TELLTALE_A01)
                        value = msg_grpa->A01;
                    else if (it.second.symbol_number == TELLTALE_A02)
                        value = msg_grpa->A02;
                    else if (it.second.symbol_number == TELLTALE_A05)
                        value = msg_grpa->A05;
                    else if (it.second.symbol_number == TELLTALE_A06)
                        value = msg_grpa->A06;
                    else if (it.second.symbol_number == TELLTALE_A09)
                        value = msg_grpa->A09;
                    else if (it.second.symbol_number == TELLTALE_A27)
                        value = msg_grpa->A27;
                    else if (it.second.symbol_number == TELLTALE_A37)
                        value = msg_grpa->A37;
                    else if (it.second.symbol_number == TELLTALE_A40)
                        value = msg_grpa->A40;
                    else if (it.second.symbol_number == TELLTALE_A41)
                        value = msg_grpa->A41;
                    else if (it.second.symbol_number == TELLTALE_A42)
                        value = msg_grpa->A42;
                    else if (it.second.symbol_number == TELLTALE_A21)
                        value = msg_grpa->A21;
                    else if (it.second.symbol_number == TELLTALE_A43)
                        value = msg_grpa->A43;
                    else if (it.second.symbol_number == TELLTALE_A46)
                        value = msg_grpa->A46;
                    else if (it.second.symbol_number == TELLTALE_A47)
                        value = msg_grpa->A47;
                    else if (it.second.symbol_number == TELLTALE_A48)
                        value = msg_grpa->A48;
                    else if (it.second.symbol_number == TELLTALE_A49)
                        value = msg_grpa->A49;
                    else if (it.second.symbol_number == TELLTALE_A50)
                        value = msg_grpa->A50;
                    else if (it.second.symbol_number == TELLTALE_A51)
                        value = msg_grpa->A51;
                    else if (it.second.symbol_number == TELLTALE_A52)
                        value = msg_grpa->A52;
                    else if (it.second.symbol_number == TELLTALE_A53)
                        value = msg_grpa->A53;
                    else if (it.second.symbol_number == TELLTALE_A24)
                        value = msg_grpa->A24;
                }

            if (it.second.telltale_category == TELLTALE_B
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_B_ID)->is_updated())
            {
                    TT_GRP_B_t* msg_grpb = reinterpret_cast<TT_GRP_B_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_B_ID));

                    if (it.second.symbol_number == TELLTALE_B01)
                        value = msg_grpb->B01;
                    if (it.second.symbol_number == TELLTALE_B02)
                        value = msg_grpb->B02;
                    if (it.second.symbol_number == TELLTALE_B03)
                        value = msg_grpb->B03;
                    if (it.second.symbol_number == TELLTALE_B04)
                        value = msg_grpb->B04;
                    if (it.second.symbol_number == TELLTALE_B05)
                        value = msg_grpb->B05;
                    if (it.second.symbol_number == TELLTALE_B10)
                        value = msg_grpb->B10;
                    if (it.second.symbol_number == TELLTALE_B14)
                        value = msg_grpb->B14;
                    if (it.second.symbol_number == TELLTALE_B15)
                        value = msg_grpb->B15;
                    if (it.second.symbol_number == TELLTALE_B21)
                        value = msg_grpb->B21;
                    if (it.second.symbol_number == TELLTALE_B22)
                        value = msg_grpb->B22;
                    if (it.second.symbol_number == TELLTALE_B23)
                        value = msg_grpb->B23;
                    if (it.second.symbol_number == TELLTALE_B24)
                        value = msg_grpb->B24;
                    if (it.second.symbol_number == TELLTALE_B26)
                        value = msg_grpb->B26;
            }

            if (it.second.telltale_category == TELLTALE_C
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_C_ID)->is_updated())
            {
                    TT_GRP_C_t* msg_grpc = reinterpret_cast<TT_GRP_C_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_C_ID));

                    if (it.second.symbol_number == TELLTALE_C02)
                        value = msg_grpc->C02;
                    if (it.second.symbol_number == TELLTALE_C25)
                        value = msg_grpc->C25;
                    if (it.second.symbol_number == TELLTALE_C26)
                        value = msg_grpc->C26;
                    if (it.second.symbol_number == TELLTALE_C27)
                        value = msg_grpc->C27;
                    if (it.second.symbol_number == TELLTALE_C28)
                        value = msg_grpc->C28;
                    if (it.second.symbol_number == TELLTALE_C29)
                        value = msg_grpc->C29;
                    if (it.second.symbol_number == TELLTALE_C30)
                        value = msg_grpc->C30;
                    if (it.second.symbol_number == TELLTALE_C31)
                        value = msg_grpc->C31;
                    if (it.second.symbol_number == TELLTALE_C07)
                        value = msg_grpc->C07;
                    if (it.second.symbol_number == TELLTALE_C18)
                        value = msg_grpc->C18;
            }

            if (it.second.telltale_category == TELLTALE_D
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_D_ID)->is_updated())
            {
                    TT_GRP_D_t* msg_grpd = reinterpret_cast<TT_GRP_D_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_D_ID));

                    if (it.second.symbol_number == TELLTALE_D31)
                        value = msg_grpd->D31;
                    if (it.second.symbol_number == TELLTALE_D44)
                        value = msg_grpd->D44;
                    if (it.second.symbol_number == TELLTALE_D45)
                        value = msg_grpd->D45;
                    if (it.second.symbol_number == TELLTALE_D46)
                        value = msg_grpd->D46;
                    if (it.second.symbol_number == TELLTALE_D47)
                        value = msg_grpd->D47;
                    if (it.second.symbol_number == TELLTALE_D48)
                        value = msg_grpd->D48;
                    if (it.second.symbol_number == TELLTALE_D49)
                        value = msg_grpd->D49;
                    if (it.second.symbol_number == TELLTALE_D50)
                        value = msg_grpd->D50;
                    if (it.second.symbol_number == TELLTALE_D51)
                        value = msg_grpd->D51;
            }

            if (it.second.telltale_category == TELLTALE_E
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_E_ID)->is_updated())
            {
                    TT_GRP_E_t* msg_grpe = reinterpret_cast<TT_GRP_E_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_E_ID));

                    if (it.second.symbol_number == TELLTALE_E15)
                        value = msg_grpe->E15;
                    if (it.second.symbol_number == TELLTALE_E16)
                        value = msg_grpe->E16;
                    if (it.second.symbol_number == TELLTALE_E17)
                        value = msg_grpe->E17;
                    if (it.second.symbol_number == TELLTALE_E18)
                        value = msg_grpe->E18;
                    if (it.second.symbol_number == TELLTALE_E19)
                        value = msg_grpe->E19;
                    if (it.second.symbol_number == TELLTALE_E20)
                        value = msg_grpe->E20;
            }

            if (it.second.telltale_category == TELLTALE_F
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_F_ID)->is_updated())
            {
                    TT_GRP_F_t* msg_grpf = reinterpret_cast<TT_GRP_F_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_F_ID));

                    if (it.second.symbol_number == TELLTALE_F01)
                        value = msg_grpf->F01;
                    if (it.second.symbol_number == TELLTALE_F02)
                        value = msg_grpf->F02;
                    if (it.second.symbol_number == TELLTALE_F03)
                        value = msg_grpf->F03;
                    if (it.second.symbol_number == TELLTALE_F04)
                        value = msg_grpf->F04;
                    if (it.second.symbol_number == TELLTALE_F05)
                        value = msg_grpf->F05;
                    if (it.second.symbol_number == TELLTALE_F10)
                        value = msg_grpf->F10;
                    if (it.second.symbol_number == TELLTALE_F15)
                        value = msg_grpf->F15;
                    if (it.second.symbol_number == TELLTALE_F16)
                        value = msg_grpf->F16;
                    if (it.second.symbol_number == TELLTALE_F30)
                        value = msg_grpf->F30;
                    if (it.second.symbol_number == TELLTALE_F31)
                        value = msg_grpf->F31;
                    if (it.second.symbol_number == TELLTALE_F32)
                        value = msg_grpf->F32;
                    if (it.second.symbol_number == TELLTALE_F33)
                        value = msg_grpf->F33;
                    if (it.second.symbol_number == TELLTALE_F34)
                        value = msg_grpf->F34;
                    if (it.second.symbol_number == TELLTALE_F35)
                        value = msg_grpf->F35;
                    if (it.second.symbol_number == TELLTALE_F36)
                        value = msg_grpf->F36;
                    if (it.second.symbol_number == TELLTALE_F23)
                        value = msg_grpf->F23;
                    if (it.second.symbol_number == TELLTALE_F19)
                        value = msg_grpf->F19;
                    if (it.second.symbol_number == TELLTALE_F18)
                        value = msg_grpf->F18;
                    if (it.second.symbol_number == TELLTALE_F22)
                        value = msg_grpf->F22;
            }


            if (it.second.telltale_category == TELLTALE_G
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_G_ID)->is_updated())
            {
                    TT_GRP_G_t* msg_grpg = reinterpret_cast<TT_GRP_G_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_G_ID));

                    if (it.second.symbol_number == TELLTALE_G01)
                        value = msg_grpg->G01;
                    if (it.second.symbol_number == TELLTALE_G21)
                        value = msg_grpg->G21;
                    if (it.second.symbol_number == TELLTALE_G22)
                        value = msg_grpg->G22;
                    if (it.second.symbol_number == TELLTALE_G23)
                        value = msg_grpg->G23;
                    if (it.second.symbol_number == TELLTALE_G24)
                        value = msg_grpg->G24;
                    if (it.second.symbol_number == TELLTALE_G25)
                        value = msg_grpg->G25;
                    if (it.second.symbol_number == TELLTALE_G26)
                        value = msg_grpg->G26;
                    if (it.second.symbol_number == TELLTALE_G10)
                        value = msg_grpg->G10;
            }

            if (it.second.telltale_category == TELLTALE_H
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_H_ID)->is_updated())
            {
                    TT_GRP_H_t* msg_grph = reinterpret_cast<TT_GRP_H_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_H_ID));

                    if (it.second.symbol_number == TELLTALE_H01)
                        value = msg_grph->H01;
                    if (it.second.symbol_number == TELLTALE_H02)
                        value = msg_grph->H02;
                    if (it.second.symbol_number == TELLTALE_H03)
                        value = msg_grph->H03;
                    if (it.second.symbol_number == TELLTALE_H04)
                        value = msg_grph->H04;
                    if (it.second.symbol_number == TELLTALE_H05)
                        value = msg_grph->H05;
            }

            if (it.second.telltale_category == TELLTALE_I
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_I_ID)->is_updated())
            {
                    TT_GRP_I_t* msg_grpi = reinterpret_cast<TT_GRP_I_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_I_ID));

                    if (it.second.symbol_number == TELLTALE_I30)
                        value = msg_grpi->I30;
            }

            if (it.second.telltale_category == TELLTALE_K
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_K_ID)->is_updated())
            {
                    TT_GRP_K_t* msg_grpk = reinterpret_cast<TT_GRP_K_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_K_ID));

                    if (it.second.symbol_number == TELLTALE_K01)
                        value = msg_grpk->K01;
                    if (it.second.symbol_number == TELLTALE_K10)
                        value = msg_grpk->K10;
                    if (it.second.symbol_number == TELLTALE_K13)
                        value = msg_grpk->K13;
                    if (it.second.symbol_number == TELLTALE_K28)
                        value = msg_grpk->K28;
                    if (it.second.symbol_number == TELLTALE_K29)
                        value = msg_grpk->K29;
                    if (it.second.symbol_number == TELLTALE_K30)
                        value = msg_grpk->K30;
                    if (it.second.symbol_number == TELLTALE_K31)
                        value = msg_grpk->K31;
                    if (it.second.symbol_number == TELLTALE_K32)
                        value = msg_grpk->K32;
                    if (it.second.symbol_number == TELLTALE_K33)
                        value = msg_grpk->K33;
                    if (it.second.symbol_number == TELLTALE_K34)
                        value = msg_grpk->K34;
                    if (it.second.symbol_number == TELLTALE_K35)
                        value = msg_grpk->K35;
            }

            if (it.second.telltale_category == TELLTALE_P
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_P_ID)->is_updated())
            {
                    TT_GRP_P_t* msg_grpp = reinterpret_cast<TT_GRP_P_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_P_ID));

                    if (it.second.symbol_number == TELLTALE_P08)
                        value = msg_grpp->P08;
            }

            if (it.second.telltale_category == TELLTALE_M
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_M_ID)->is_updated())
            {
                    TT_GRP_M_t* msg_grpm = reinterpret_cast<TT_GRP_M_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_M_ID));

                    if (it.second.symbol_number == TELLTALE_M01)
                        value = msg_grpm->M01;
            }

            if (it.second.telltale_category == TELLTALE_J
                && m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_J_ID)->is_updated())
            {
                    TT_GRP_J_t* msg_grpj = reinterpret_cast<TT_GRP_J_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_J_ID));

                    if (it.second.symbol_number == TELLTALE_J07)
                        value = msg_grpj->J07;
            }
        }
        if (value && it.second.colors[value - 1] != "")
        {
            _map_telltale_data[it.second.position].telltale_name = it.second.symbol_number;
            _map_telltale_data[it.second.position].priority = it.second.telltale_priority;
            _map_telltale_data[it.second.position].telltale_color = it.second.colors[value - 1];
            telltale_pos[0][0] = it.second.telltale_path;
            telltale_pos[0][1] = "true";
            telltale_pos[0][2] = it.second.colors[value - 1];
            auto functptr = map_telltale_slots[it.second.position];
            (this->*functptr)(telltale_pos);
        }
        else if (_map_telltale_data[it.second.position].telltale_name == it.second.symbol_number)
        {
            _map_telltale_data[it.second.position].telltale_color = INIT_COLOR_TRANSPARENT;
            telltale_pos[0][0] = it.second.telltale_path;
            telltale_pos[0][1] = "false";
            telltale_pos[0][2] = INIT_COLOR_TRANSPARENT;
            auto functptr = map_telltale_slots[it.second.position];
            (this->*functptr)(telltale_pos);
        }
    }
    CATCH_BLOCK
}

void QtTelltales::update_gui()
{
    TRY_BLOCK
    if (_state == QmlState::QMLSTATE_NORMAL)
    {
        update_all_telltales();
        update_bus_doors();
    }
    CATCH_BLOCK
}

bool QtTelltales::check_priority(QString _name)
{
    TRY_BLOCK
    return ((ptr_map_json->find(_name) != ptr_map_json->end()) && (_map_telltale_data[(*(ptr_map_json))[_name].position].priority >= (*(ptr_map_json))[_name].telltale_priority
            || _map_telltale_data[(*(ptr_map_json))[_name].position].telltale_color == INIT_COLOR_TRANSPARENT));
    CATCH_BLOCK
}

void QtTelltales::apply_telltale(uint8_t _value, QString _name)
{
    TRY_BLOCK
    if (_value && (*(ptr_map_json))[_name].colors[_value - 1] != "")
    {
        _map_telltale_data[(*(ptr_map_json))[_name].position].telltale_name = (*(ptr_map_json))[_name].symbol_number;
        _map_telltale_data[(*(ptr_map_json))[_name].position].priority = (*(ptr_map_json))[_name].telltale_priority;
        _map_telltale_data[(*(ptr_map_json))[_name].position].telltale_color = (*(ptr_map_json))[_name].colors[_value - 1];
        telltale_pos[0][0] = (*(ptr_map_json))[_name].telltale_path;
        telltale_pos[0][1] = "true";
        telltale_pos[0][2] = (*(ptr_map_json))[_name].colors[_value - 1];
        auto functptr = map_telltale_slots[(*(ptr_map_json))[_name].position];
        (this->*functptr)(telltale_pos);
    }
    else if ((_map_telltale_data[(*(ptr_map_json))[_name].position].telltale_name == (*(ptr_map_json))[_name].symbol_number) && !_value)
    {
        _map_telltale_data[(*(ptr_map_json))[_name].position].telltale_color = INIT_COLOR_TRANSPARENT;
        telltale_pos[0][0] = (*(ptr_map_json))[_name].telltale_path;
        telltale_pos[0][1] = "false";
        telltale_pos[0][2] = INIT_COLOR_TRANSPARENT;
        auto functptr = map_telltale_slots[(*(ptr_map_json))[_name].position];
        (this->*functptr)(telltale_pos);
    }
    CATCH_BLOCK
}


bool QtTelltales::update_info(uint32_t _id)
{
    TRY_BLOCK
    if (_state != QmlState::QMLSTATE_NORMAL)
        return false;
    switch (_id)
    {
    case HMIHANDLER_DC2_ID:
        update_bus_doors();
        return true;
        break;
    case HMIHANDLER_TT_GRP_A_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_A_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            TT_GRP_A_t* msg_grpa = reinterpret_cast<TT_GRP_A_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_A_ID));
            if (check_priority(TELLTALE_A01))
                apply_telltale(msg_grpa->A01, TELLTALE_A01);
            if (check_priority(TELLTALE_A02))
                apply_telltale(msg_grpa->A02, TELLTALE_A02);
            if (check_priority(TELLTALE_A05))
                apply_telltale(msg_grpa->A05, TELLTALE_A05);
            if (check_priority(TELLTALE_A06))
                apply_telltale(msg_grpa->A06, TELLTALE_A06);
            if (check_priority(TELLTALE_A09))
                apply_telltale(msg_grpa->A09, TELLTALE_A09);
            if (check_priority(TELLTALE_A27))
                apply_telltale(msg_grpa->A27, TELLTALE_A27);
            if (check_priority(TELLTALE_A37))
                apply_telltale(msg_grpa->A37, TELLTALE_A37);
            if (check_priority(TELLTALE_A40))
                apply_telltale(msg_grpa->A40, TELLTALE_A40);
            if (check_priority(TELLTALE_A41))
                apply_telltale(msg_grpa->A41, TELLTALE_A41);
            if (check_priority(TELLTALE_A42))
                apply_telltale(msg_grpa->A42, TELLTALE_A42);
            if (check_priority(TELLTALE_A21))
                apply_telltale(msg_grpa->A21, TELLTALE_A21);
            if (check_priority(TELLTALE_A43))
                apply_telltale(msg_grpa->A43, TELLTALE_A43);
            if (check_priority(TELLTALE_A46))
                apply_telltale(msg_grpa->A46, TELLTALE_A46);
            if (check_priority(TELLTALE_A47))
                apply_telltale(msg_grpa->A47, TELLTALE_A47);
            if (check_priority(TELLTALE_A48))
                apply_telltale(msg_grpa->A48, TELLTALE_A48);
            if (check_priority(TELLTALE_A49))
                apply_telltale(msg_grpa->A49, TELLTALE_A49);
            if (check_priority(TELLTALE_A50))
                apply_telltale(msg_grpa->A50, TELLTALE_A50);
            if (check_priority(TELLTALE_A51))
                apply_telltale(msg_grpa->A51, TELLTALE_A51);
            if (check_priority(TELLTALE_A52))
                apply_telltale(msg_grpa->A52, TELLTALE_A52);
            if (check_priority(TELLTALE_A53))
                apply_telltale(msg_grpa->A53, TELLTALE_A53);
            if (check_priority(TELLTALE_A24))
                apply_telltale(msg_grpa->A24, TELLTALE_A24);
        }
        break;
    case HMIHANDLER_TT_GRP_B_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_B_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            TT_GRP_B_t* msg_grpb = reinterpret_cast<TT_GRP_B_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_B_ID));
            if (check_priority(TELLTALE_B01))
                apply_telltale(msg_grpb->B01, TELLTALE_B01);
            if (check_priority(TELLTALE_B02))
                apply_telltale(msg_grpb->B02, TELLTALE_B02);
            if (check_priority(TELLTALE_B03))
                apply_telltale(msg_grpb->B03, TELLTALE_B03);
            if (check_priority(TELLTALE_B04))
                apply_telltale(msg_grpb->B04, TELLTALE_B04);
            if (check_priority(TELLTALE_B05))
                apply_telltale(msg_grpb->B05, TELLTALE_B05);
            if (check_priority(TELLTALE_B10))
                apply_telltale(msg_grpb->B10, TELLTALE_B10);
            if (check_priority(TELLTALE_B14))
                apply_telltale(msg_grpb->B14, TELLTALE_B14);
            if (check_priority(TELLTALE_B15))
                apply_telltale(msg_grpb->B15, TELLTALE_B15);
            if (check_priority(TELLTALE_B21))
                apply_telltale(msg_grpb->B21, TELLTALE_B21);
            if (check_priority(TELLTALE_B22))
                apply_telltale(msg_grpb->B22, TELLTALE_B22);
            if (check_priority(TELLTALE_B23))
                apply_telltale(msg_grpb->B23, TELLTALE_B23);
            if (check_priority(TELLTALE_B24))
                apply_telltale(msg_grpb->B24, TELLTALE_B24);
            if (check_priority(TELLTALE_B26))
                apply_telltale(msg_grpb->B26, TELLTALE_B26);
        }
        break;
    case HMIHANDLER_TT_GRP_C_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_C_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            TT_GRP_C_t* msg_grpc = reinterpret_cast<TT_GRP_C_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_C_ID));

            if (check_priority(TELLTALE_C02))
                apply_telltale(msg_grpc->C02, TELLTALE_C02);
            if (check_priority(TELLTALE_C25))
                apply_telltale(msg_grpc->C25, TELLTALE_C25);
            if (check_priority(TELLTALE_C26))
                apply_telltale(msg_grpc->C26, TELLTALE_C26);
            if (check_priority(TELLTALE_C27))
                apply_telltale(msg_grpc->C27, TELLTALE_C27);
            if (check_priority(TELLTALE_C28))
                apply_telltale(msg_grpc->C28, TELLTALE_C28);
            if (check_priority(TELLTALE_C29))
                apply_telltale(msg_grpc->C29, TELLTALE_C29);
            if (check_priority(TELLTALE_C30))
                apply_telltale(msg_grpc->C30, TELLTALE_C30);
            if (check_priority(TELLTALE_C31))
                apply_telltale(msg_grpc->C31, TELLTALE_C31);
            if (check_priority(TELLTALE_C07))
                apply_telltale(msg_grpc->C07, TELLTALE_C07);
            if (check_priority(TELLTALE_C18))
                apply_telltale(msg_grpc->C18, TELLTALE_C18);
        }
        break;
    case HMIHANDLER_TT_GRP_D_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_D_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
                TT_GRP_D_t* msg_grpd = reinterpret_cast<TT_GRP_D_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_D_ID));

                if (check_priority(TELLTALE_D31))
                    apply_telltale(msg_grpd->D31, TELLTALE_D31);
                if (check_priority(TELLTALE_D44))
                    apply_telltale(msg_grpd->D44, TELLTALE_D44);
                if (check_priority(TELLTALE_D45))
                    apply_telltale(msg_grpd->D45, TELLTALE_D45);
                if (check_priority(TELLTALE_D46))
                    apply_telltale(msg_grpd->D46, TELLTALE_D46);
                if (check_priority(TELLTALE_D47))
                    apply_telltale(msg_grpd->D47, TELLTALE_D47);
                if (check_priority(TELLTALE_D48))
                    apply_telltale(msg_grpd->D48, TELLTALE_D48);
                if (check_priority(TELLTALE_D49))
                    apply_telltale(msg_grpd->D49, TELLTALE_D49);
                if (check_priority(TELLTALE_D50))
                    apply_telltale(msg_grpd->D50, TELLTALE_D50);
                if (check_priority(TELLTALE_D51))
                    apply_telltale(msg_grpd->D51, TELLTALE_D51);
        }
        break;
    case HMIHANDLER_TT_GRP_E_ID:
        if(m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_E_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
                TT_GRP_E_t* msg_grpe = reinterpret_cast<TT_GRP_E_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_E_ID));

                if (check_priority(TELLTALE_E15))
                    apply_telltale(msg_grpe->E15, TELLTALE_E15);
                if (check_priority(TELLTALE_E16))
                    apply_telltale(msg_grpe->E16, TELLTALE_E16);
                if (check_priority(TELLTALE_E17))
                    apply_telltale(msg_grpe->E17, TELLTALE_E17);
                if (check_priority(TELLTALE_E18))
                    apply_telltale(msg_grpe->E18, TELLTALE_E18);
                if (check_priority(TELLTALE_E19))
                    apply_telltale(msg_grpe->E19, TELLTALE_E19);
                if (check_priority(TELLTALE_E20))
                    apply_telltale(msg_grpe->E20, TELLTALE_E20);
        }
        break;
    case HMIHANDLER_TT_GRP_F_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_F_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
                TT_GRP_F_t* msg_grpf = reinterpret_cast<TT_GRP_F_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_F_ID));

                if (check_priority(TELLTALE_F01))
                    apply_telltale(msg_grpf->F01, TELLTALE_F01);
                if (check_priority(TELLTALE_F02))
                    apply_telltale(msg_grpf->F02, TELLTALE_F02);
                if (check_priority(TELLTALE_F03))
                    apply_telltale(msg_grpf->F03, TELLTALE_F03);
                if (check_priority(TELLTALE_F04))
                    apply_telltale(msg_grpf->F04, TELLTALE_F04);
                if (check_priority(TELLTALE_F05))
                    apply_telltale(msg_grpf->F05, TELLTALE_F05);
                if (check_priority(TELLTALE_F10))
                    apply_telltale(msg_grpf->F10, TELLTALE_F10);
                if (check_priority(TELLTALE_F15))
                    apply_telltale(msg_grpf->F15, TELLTALE_F15);
                if (check_priority(TELLTALE_F16))
                    apply_telltale(msg_grpf->F16, TELLTALE_F16);
                if (check_priority(TELLTALE_F30))
                    apply_telltale(msg_grpf->F30, TELLTALE_F30);
                if (check_priority(TELLTALE_F31))
                    apply_telltale(msg_grpf->F31, TELLTALE_F31);
                if (check_priority(TELLTALE_F32))
                    apply_telltale(msg_grpf->F32, TELLTALE_F32);
                if (check_priority(TELLTALE_F33))
                    apply_telltale(msg_grpf->F33, TELLTALE_F33);
                if (check_priority(TELLTALE_F34))
                    apply_telltale(msg_grpf->F34, TELLTALE_F34);
                if (check_priority(TELLTALE_F35))
                    apply_telltale(msg_grpf->F35, TELLTALE_F35);
                if (check_priority(TELLTALE_F36))
                    apply_telltale(msg_grpf->F36, TELLTALE_F36);
                if (check_priority(TELLTALE_F23))
                    apply_telltale(msg_grpf->F23, TELLTALE_F23);
                if (check_priority(TELLTALE_F19))
                    apply_telltale(msg_grpf->F19, TELLTALE_F19);  
                if (check_priority(TELLTALE_F19))
                    apply_telltale(msg_grpf->F18, TELLTALE_F18);
                if (check_priority(TELLTALE_F19))
                    apply_telltale(msg_grpf->F22, TELLTALE_F22);

        }
        break;
    case HMIHANDLER_TT_GRP_G_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_G_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
                TT_GRP_G_t* msg_grpg = reinterpret_cast<TT_GRP_G_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_G_ID));

                if (check_priority(TELLTALE_G01))
                    apply_telltale(msg_grpg->G01, TELLTALE_G01);
                if (check_priority(TELLTALE_G21))
                    apply_telltale(msg_grpg->G21, TELLTALE_G21);
                if (check_priority(TELLTALE_G22))
                    apply_telltale(msg_grpg->G22, TELLTALE_G22);
                if (check_priority(TELLTALE_G23))
                    apply_telltale(msg_grpg->G23, TELLTALE_G23);
                if (check_priority(TELLTALE_G24))
                    apply_telltale(msg_grpg->G24, TELLTALE_G24);
                if (check_priority(TELLTALE_G25))
                    apply_telltale(msg_grpg->G25, TELLTALE_G25);
                if (check_priority(TELLTALE_G26))
                    apply_telltale(msg_grpg->G26, TELLTALE_G26);
                if (check_priority(TELLTALE_G10))
                    apply_telltale(msg_grpg->G10, TELLTALE_G10);

        }
        break;
    case HMIHANDLER_TT_GRP_H_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_H_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
                TT_GRP_H_t* msg_grph = reinterpret_cast<TT_GRP_H_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_H_ID));
                if (check_priority(TELLTALE_H01))
                    apply_telltale(msg_grph->H01, TELLTALE_H01);
                if (check_priority(TELLTALE_H02))
                    apply_telltale(msg_grph->H02, TELLTALE_H02);
                if (check_priority(TELLTALE_H03))
                    apply_telltale(msg_grph->H03, TELLTALE_H03);
                if (check_priority(TELLTALE_H04))
                    apply_telltale(msg_grph->H04, TELLTALE_H04);
                if (check_priority(TELLTALE_H05))
                    apply_telltale(msg_grph->H05, TELLTALE_H05);
        }
        break;
    case HMIHANDLER_TT_GRP_I_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_I_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
                TT_GRP_I_t* msg_grpi = reinterpret_cast<TT_GRP_I_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_I_ID));
                if (check_priority(TELLTALE_I30))
                    apply_telltale(msg_grpi->I30, TELLTALE_I30);
        }
        break;
    case HMIHANDLER_TT_GRP_J_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_J_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
                TT_GRP_J_t* msg_grpj = reinterpret_cast<TT_GRP_J_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_J_ID));

                if (check_priority(TELLTALE_J07))
                    apply_telltale(msg_grpj->J07, TELLTALE_J07);
        }
        break;
    case HMIHANDLER_TT_GRP_K_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_K_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
                TT_GRP_K_t* msg_grpk = reinterpret_cast<TT_GRP_K_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_K_ID));

                if (check_priority(TELLTALE_K01))
                    apply_telltale(msg_grpk->K01, TELLTALE_K01);
                if (check_priority(TELLTALE_K10))
                    apply_telltale(msg_grpk->K10, TELLTALE_K10);
                if (check_priority(TELLTALE_K13))
                    apply_telltale(msg_grpk->K13, TELLTALE_K13);
                if (check_priority(TELLTALE_K28))
                    apply_telltale(msg_grpk->K28, TELLTALE_K28);
                if (check_priority(TELLTALE_K29))
                    apply_telltale(msg_grpk->K29, TELLTALE_K29);
                if (check_priority(TELLTALE_K30))
                    apply_telltale(msg_grpk->K30, TELLTALE_K30);
                if (check_priority(TELLTALE_K31))
                    apply_telltale(msg_grpk->K31, TELLTALE_K31);
                if (check_priority(TELLTALE_K32))
                    apply_telltale(msg_grpk->K32, TELLTALE_K32);
                if (check_priority(TELLTALE_K33))
                    apply_telltale(msg_grpk->K33, TELLTALE_K33);
                if (check_priority(TELLTALE_K34))
                    apply_telltale(msg_grpk->K34, TELLTALE_K34);
                if (check_priority(TELLTALE_K35))
                    apply_telltale(msg_grpk->K35, TELLTALE_K35);
        }
        break;
    case HMIHANDLER_TT_GRP_M_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_M_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
                TT_GRP_M_t* msg_grpm = reinterpret_cast<TT_GRP_M_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_M_ID));

                if (check_priority(TELLTALE_M01))
                    apply_telltale(msg_grpm->M01, TELLTALE_M01);
        }
        break;
    case HMIHANDLER_TT_GRP_P_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_P_ID)->is_updated())
        {
                TT_GRP_P_t* msg_grpp = reinterpret_cast<TT_GRP_P_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_P_ID));

                if (check_priority(TELLTALE_P08))
                    apply_telltale(msg_grpp->P08, TELLTALE_P08);
        }
        break;
    }
    return true;
    CATCH_BLOCK
}

void QtTelltales::init_telltales()
{
    TRY_BLOCK
    telltale_pos.append(QStringList({ "NA", "NA", "NA" }));
    CATCH_BLOCK
}

void QtTelltales::update_map_init_data()
{
    TRY_BLOCK
    map_telltale_slots.insert({1, &QtTelltales::set_telltale_pos_1});
    map_telltale_slots.insert({2, &QtTelltales::set_telltale_pos_2});
    map_telltale_slots.insert({3, &QtTelltales::set_telltale_pos_3});
    map_telltale_slots.insert({4, &QtTelltales::set_telltale_pos_4});
    map_telltale_slots.insert({5, &QtTelltales::set_telltale_pos_5});
    map_telltale_slots.insert({6, &QtTelltales::set_telltale_pos_6});
    map_telltale_slots.insert({7, &QtTelltales::set_telltale_pos_7});
    map_telltale_slots.insert({8, &QtTelltales::set_telltale_pos_8});
    map_telltale_slots.insert({9, &QtTelltales::set_telltale_pos_9});
    map_telltale_slots.insert({10, &QtTelltales::set_telltale_pos_10});
    map_telltale_slots.insert({11, &QtTelltales::set_telltale_pos_11});
    map_telltale_slots.insert({12, &QtTelltales::set_telltale_pos_12});
    map_telltale_slots.insert({13, &QtTelltales::set_telltale_pos_13});
    map_telltale_slots.insert({14, &QtTelltales::set_telltale_pos_14});
    map_telltale_slots.insert({15, &QtTelltales::set_telltale_pos_15});
    map_telltale_slots.insert({16, &QtTelltales::set_telltale_pos_16});
    map_telltale_slots.insert({17, &QtTelltales::set_telltale_pos_17});
    map_telltale_slots.insert({18, &QtTelltales::set_telltale_pos_18});
    map_telltale_slots.insert({19, &QtTelltales::set_telltale_pos_19});
    map_telltale_slots.insert({20, &QtTelltales::set_telltale_pos_20});
    map_telltale_slots.insert({21, &QtTelltales::set_telltale_pos_21});
    map_telltale_slots.insert({22, &QtTelltales::set_telltale_pos_22});
    map_telltale_slots.insert({23, &QtTelltales::set_telltale_pos_23});
    map_telltale_slots.insert({24, &QtTelltales::set_telltale_pos_24});
    map_telltale_slots.insert({25, &QtTelltales::set_telltale_pos_25});
    map_telltale_slots.insert({26, &QtTelltales::set_telltale_pos_26});
    map_telltale_slots.insert({27, &QtTelltales::set_telltale_pos_27});
    map_telltale_slots.insert({28, &QtTelltales::set_telltale_pos_28});
    map_telltale_slots.insert({29, &QtTelltales::set_telltale_pos_29});
    map_telltale_slots.insert({30, &QtTelltales::set_telltale_pos_30});
    map_telltale_slots.insert({31, &QtTelltales::set_telltale_pos_31});
    map_telltale_slots.insert({32, &QtTelltales::set_telltale_pos_32});
    map_telltale_slots.insert({33, &QtTelltales::set_telltale_pos_33});
    map_telltale_slots.insert({34, &QtTelltales::set_telltale_pos_34});
    map_telltale_slots.insert({35, &QtTelltales::set_telltale_pos_35});
    map_telltale_slots.insert({36, &QtTelltales::set_telltale_pos_36});
    map_telltale_slots.insert({37, &QtTelltales::set_telltale_pos_37});
    map_telltale_slots.insert({38, &QtTelltales::set_telltale_pos_38});
    map_telltale_slots.insert({39, &QtTelltales::set_telltale_pos_39});
    map_telltale_slots.insert({40, &QtTelltales::set_telltale_pos_40});
    map_telltale_slots.insert({41, &QtTelltales::set_telltale_pos_41});
    map_telltale_slots.insert({42, &QtTelltales::set_telltale_pos_42});
    map_telltale_slots.insert({43, &QtTelltales::set_telltale_pos_43});
    map_telltale_slots.insert({44, &QtTelltales::set_telltale_pos_44});
    map_telltale_slots.insert({45, &QtTelltales::set_telltale_pos_45});
    map_telltale_slots.insert({46, &QtTelltales::set_telltale_pos_46});
    map_telltale_slots.insert({47, &QtTelltales::set_telltale_pos_47});
    map_telltale_slots.insert({48, &QtTelltales::set_telltale_pos_48});
    map_telltale_slots.insert({49, &QtTelltales::set_telltale_pos_49});
    map_telltale_slots.insert({50, &QtTelltales::set_telltale_pos_50});
    map_telltale_slots.insert({51, &QtTelltales::set_telltale_pos_51});
    map_telltale_slots.insert({52, &QtTelltales::set_telltale_pos_52});
    map_telltale_slots.insert({53, &QtTelltales::set_telltale_pos_53});
    map_telltale_slots.insert({54, &QtTelltales::set_telltale_pos_54});
    map_telltale_slots.insert({55, &QtTelltales::set_telltale_pos_55});
    map_telltale_slots.insert({56, &QtTelltales::set_telltale_pos_56});
    map_telltale_slots.insert({57, &QtTelltales::set_telltale_pos_57});
    map_telltale_slots.insert({58, &QtTelltales::set_telltale_pos_58});
    map_telltale_slots.insert({59, &QtTelltales::set_telltale_pos_59});
    map_telltale_slots.insert({60, &QtTelltales::set_telltale_pos_60});
    map_telltale_slots.insert({61, &QtTelltales::set_telltale_pos_61});
    map_telltale_slots.insert({62, &QtTelltales::set_telltale_pos_62});
    map_telltale_slots.insert({63, &QtTelltales::set_telltale_pos_63});
    map_telltale_slots.insert({64, &QtTelltales::set_telltale_pos_64});
    map_telltale_slots.insert({65, &QtTelltales::set_telltale_pos_65});
    map_telltale_slots.insert({66, &QtTelltales::set_telltale_pos_66});
    map_telltale_slots.insert({67, &QtTelltales::set_telltale_pos_67});
    map_telltale_slots.insert({68, &QtTelltales::set_telltale_pos_68});
    map_telltale_slots.insert({69, &QtTelltales::set_telltale_pos_69});
    map_telltale_slots.insert({70, &QtTelltales::set_telltale_pos_70});
    map_telltale_slots.insert({71, &QtTelltales::set_telltale_pos_71});
    map_telltale_slots.insert({72, &QtTelltales::set_telltale_pos_72});
    map_telltale_slots.insert({73, &QtTelltales::set_telltale_pos_73});
    map_telltale_slots.insert({74, &QtTelltales::set_telltale_pos_74});
    map_telltale_slots.insert({75, &QtTelltales::set_telltale_pos_75});
    map_telltale_slots.insert({76, &QtTelltales::set_telltale_pos_76});
    map_telltale_slots.insert({77, &QtTelltales::set_telltale_pos_77});
    map_telltale_slots.insert({78, &QtTelltales::set_telltale_pos_78});
    map_telltale_slots.insert({79, &QtTelltales::set_telltale_pos_79});
    map_telltale_slots.insert({80, &QtTelltales::set_telltale_pos_80});
    CATCH_BLOCK
}

const QList<QStringList>& QtTelltales::get_bus_door1() const
{
    TRY_BLOCK
    return _bus_door1;
    CATCH_BLOCK
}

void QtTelltales::set_bus_door1(const QList<QStringList>& newBus_door1)
{
    TRY_BLOCK
    if (_bus_door1 == newBus_door1)
        return;
    _bus_door1 = newBus_door1;
    emit bus_door1_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtTelltales::get_bus_door2() const
{
    TRY_BLOCK
    return _bus_door2;
    CATCH_BLOCK
}

void QtTelltales::set_bus_door2(const QList<QStringList>& newBus_door2)
{
    TRY_BLOCK
    if (_bus_door2 == newBus_door2)
        return;
    _bus_door2 = newBus_door2;
    emit bus_door2_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtTelltales::get_bus_door3() const
{
    TRY_BLOCK
    return _bus_door3;
    CATCH_BLOCK
}

void QtTelltales::set_bus_door3(const QList<QStringList>& newBus_door3)
{
    TRY_BLOCK
    if (_bus_door3 == newBus_door3)
        return;
    _bus_door3 = newBus_door3;
    emit bus_door3_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtTelltales::get_bus_door4() const
{
    TRY_BLOCK
    return _bus_door4;
    CATCH_BLOCK
}

void QtTelltales::set_bus_door4(const QList<QStringList>& newBus_door4)
{
    TRY_BLOCK
    if (_bus_door4 == newBus_door4)
        return;
    _bus_door4 = newBus_door4;
    emit bus_door4_changed();
    CATCH_BLOCK
}

void QtTelltales::init_subscribe()
{
    TRY_BLOCK
    auto ptrnotifer = subscribe_notifer::get_instance();
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_A_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_B_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_C_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_D_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_E_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_F_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_G_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_H_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_I_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_K_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_P_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_M_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_TT_GRP_J_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_DC2_ID, this);
    CATCH_BLOCK
}
