#include "qtcentraldashboard.h"
#include "qglobal.h"

static QString language_menu = LANGUAGE_ENGLISH;
static QString prev_language = LANGUAGE_ENGLISH;


void QtCentralDashboard::init_main_data_container()
{
    TRY_BLOCK
    if(!g_main_data_container.empty())
        g_main_data_container.clear();

    g_main_data_container.reserve(15);
    g_main_data_container.emplace_back(MILEAGE, tr("Mileage"), NA_VALUE, tr("km"), &QtCentralDashboard::set_mileage);
    g_main_data_container.emplace_back(DAILY_FUEL_CONSUMPTION, tr("Daily fuel consumption"), NA_VALUE, tr("l/100km"), &QtCentralDashboard::set_daily_fuel_consumption);
    g_main_data_container.emplace_back(TRIP_DISTANCE, tr("Trip Distance"), NA_VALUE, tr("km"), &QtCentralDashboard::set_trip_distance);
    g_main_data_container.emplace_back(PRESSURE_UOM, tr("Pressure UOM"), NA_VALUE, tr("bar"), &QtCentralDashboard::set_pressure_uom);
    g_main_data_container.emplace_back(ENGINE_UOM, tr("Engine UOM"), NA_VALUE, tr("x100 min"), &QtCentralDashboard::set_engine_uom);
    g_main_data_container.emplace_back(SPEED_UOM, tr("Speed UOM"), NA_VALUE, tr("km/hr"), &QtCentralDashboard::set_speed_uom);
    g_main_data_container.emplace_back(FUEL_CONSUMPTION, tr("Fuel Consumption"), NA_VALUE, UOM_PERCENTAGE, &QtCentralDashboard::set_fuel_consumption);

    g_main_data_container.emplace_back(ENGINE_COOLANT_TEMPERATURE, tr("Engine Coolant temperature"), NA_VALUE, UOM_DEGREE_CELCIUS, &QtCentralDashboard::set_engine_coolant_temperature);
    g_main_data_container.emplace_back(BATTERY_AMPERE, tr("Battery Ampere"), NA_VALUE, UOM_AMPERE, &QtCentralDashboard::set_battery_ampere);
    g_main_data_container.emplace_back(BATTERY_VOLTAGE, tr("Battery Voltage"), NA_VALUE, tr("V"), &QtCentralDashboard::set_battery_voltage);

    CATCH_BLOCK
}

mutex QtCentralDashboard::m_build_mutex;
QtCentralDashboard* QtCentralDashboard::m_ptr_instance(nullptr);

QtCentralDashboard::QtCentralDashboard(QObject* parent)
    : QObject{ parent }
    , _temperature(INVALID_VALUE)
    , _cabin_temperature1(INVALID_VALUE)
    , _cabin_temperature2(INVALID_VALUE)
    , map_main_data()
    ,_fuel_level(INVALID_VALUE)
{
    if (!m_ptr_instance)
        m_ptr_instance = this;
    m_ptr_cached_msgs = HmiHandler::getInstance();
    m_ptr_menu_handler = MenuHandler::get_instance();
    init_main_data_container();
    initialize_central_dashboard_data();
    init_subscribe();
}

QtCentralDashboard::~QtCentralDashboard()
{
    qDebug() << "QtCentralDashboard Destructor called!!!" << Qt::endl;
}

QtCentralDashboard* QtCentralDashboard::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = new QtCentralDashboard;
    }
    return m_ptr_instance;
    CATCH_BLOCK
}

void QtCentralDashboard::initialize_central_dashboard_data()
{
    TRY_BLOCK
    auto prevstate = _state;
    _state = QMLSTATE_REFRESH;
    init_main_data_container();
    QString main_text_lang;
    QString main_uom;

    QDate _current_date = QDate::currentDate();
    QString _current_date_time = _current_date.toString("dd.MM.yy");
    set_present_date(_current_date_time);

    QTime _current_time = QTime::currentTime();
    _current_date_time = _current_time.toString("hh:mm");
    set_present_time(_current_date_time);

    set_gear_shift(0);

    for (auto iterator : g_main_data_container)
    {
        QList<QStringList> _temp_main_data{};
        auto name = get<0>(iterator);
        update_map_main_data(name, get<1>(iterator), get<2>(iterator), get<3>(iterator));
        _temp_main_data.append(map_main_data[name]);
        main_slot _temp_operation = get<4>(iterator);
        (((QtCentralDashboard*)this)->*_temp_operation)(_temp_main_data); //call method using ptr on itself method
        map_main_slots.insert(name, get<4>(iterator));
    }
    _state = prevstate;
    CATCH_BLOCK
}

void QtCentralDashboard::update_gui()
{
    TRY_BLOCK
    CATCH_BLOCK
}

bool QtCentralDashboard::update_info(uint32_t _id)
{
    TRY_BLOCK
/*    if (_state != QmlState::QMLSTATE_NORMAL)
        return false;*/
    QString key_data;
    switch (_id)
    {
    case HMIHANDLER_TD_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TD_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            TD_t* ptr_data = reinterpret_cast<TD_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TD_ID));
            char string_buf[20]{};
            uint16_t year_with_offset = ptr_data->year + TD_YEAR_OFFSET;
            uint16_t year = year_with_offset % 100;
            sprintf(string_buf, "%02d.%02d.%02d", (uint32_t)round(ptr_data->day * TD_DAY_FACTOR), ptr_data->month, year);
            string _temp_str(string_buf);
            set_present_date(_temp_str.c_str());

            char temp_buff[20]{};
            int hours = (static_cast<int>(ptr_data->hours) + (ptr_data->local_hour_offset + TD_HOURS_OFFSET)) % 24;
            int minutes = (static_cast<int>(ptr_data->minutes) + (ptr_data->local_minute_offset + TD_HOURS_OFFSET)) % 60;
            sprintf(temp_buff, "%02d:%02d", hours, minutes);
            string temp_str(temp_buff);
            set_present_time(temp_str.c_str());
        }
        break;
    case HMIHANDLER_VDHR_EE_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_VDHR_EE_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            VDHR_EE_t* ptr_msg = reinterpret_cast<VDHR_EE_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_VDHR_EE_ID));
            float milage = ((static_cast<float>(ptr_msg->spn917_high_resolution_total) * TRIP_DISTANCE_FACTOR) / METER_TO_KM_CONVERTOR);
            std::ostringstream milage_oss{};
            milage_oss << std::fixed << std::setprecision(1) << milage << " ";
            key_data = MILEAGE;
            if(update_maindata(milage_oss.str(), key_data))
                emit mileage_changed();

            float trip_distance = ptr_msg->spn918_high_resolution_trip_di * TRIP_DISTANCE_FACTOR;
            trip_distance /= METER_TO_KM_CONVERTOR;
            std::ostringstream trip_oss{};
            trip_oss << std::fixed << std::setprecision(1) << trip_distance << " ";
            string strTrip = trip_oss.str();
            key_data = TRIP_DISTANCE;
            if(update_maindata(strTrip, key_data))
                emit trip_distance_changed();

            m_ptr_menu_handler->update_engine_data();

            qreal avg_fuel_consumption = *(m_ptr_menu_handler->get_daily_fuel_consumption());
            std::ostringstream fuel{};
            fuel << std::fixed << std::setprecision(1) << avg_fuel_consumption << " ";
            string element_value = fuel.str();
            key_data = DAILY_FUEL_CONSUMPTION;
            if(update_maindata(element_value, key_data))
                emit daily_fuel_consumption_changed();
        }
        break;
    case HMIHANDLER_DD_INFO1_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_DD_INFO1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            DD_INFO1_t* ptr_msg = reinterpret_cast<DD_INFO1_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_DD_INFO1_ID));
            uint8_t fuel = round(static_cast<float>(ptr_msg->fuel_level1) * DD_INFO1_FUELLEVEL1FACTOR);
            string str_fuel = (fuel <= 0xFA) ? to_string(fuel) : INVALID_VALUE;
            set_fuel_level(str_fuel.c_str());

//            std::ostringstream oss_fuel;
//            oss_fuel << std::fixed << std::setprecision(1) << ((ptr_msg->fuel_level1 == 0xFF) ? "--" : (to_string(fuel)).c_str()) << " ";
            key_data = FUEL_CONSUMPTION;
//            if(update_maindata(oss_fuel.str(), key_data))
//                emit fuel_consumption_changed();


        }
        break;
    case HMIHANDLER_ET1_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_ET1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            ET1_t* ptr_msg = reinterpret_cast<ET1_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_ET1_ID));
            int16_t temp_raw = ptr_msg->engine_coolant_temperature + ENGINE_COOLANT_OFFSET;
            std::string value_str = std::to_string(temp_raw);
            key_data = ENGINE_COOLANT_TEMPERATURE;
            if(update_maindata(value_str, key_data))
                emit engine_coolant_temperature_changed();
            m_ptr_menu_handler->update_engine_data();
        }
        break;
    case HMIHANDLER_DYN_BB_CURRENT_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_DYN_BB_CURRENT_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            DYN_BB_CURRENT_t* ptr_msg = reinterpret_cast<DYN_BB_CURRENT_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_DYN_BB_CURRENT_ID));
            int16_t current_1 = ptr_msg->current_1 * DYN_BB_CURRENT_CURRENT_1FACTOR;
            int16_t current_2 = ptr_msg->current_2 * DYN_BB_CURRENT_CURRENT_2FACTOR;
            string element_value = to_string((current_1 + current_2) / AVERAGE_OF_CUR1_CUR2);
//            m_ptr_menu_handler->update_battery_data();
            key_data = BATTERY_AMPERE;
            if(update_maindata(element_value, key_data))
                emit battery_ampere_changed();
        }
        break;
    case HMIHANDLER_CBCU2_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_CBCU2_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            CBCU2_t* ptr_msg = reinterpret_cast<CBCU2_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_CBCU2_ID));
            float voltage = static_cast<float>(ptr_msg->cbcu_mainpwr) * CBCU2_CBCU_MAINPWRFACTOR;
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(1) << voltage << " ";
            key_data = BATTERY_VOLTAGE;
            if(update_maindata(oss.str(), key_data))
                emit battery_voltage_changed();
//            m_ptr_menu_handler->update_battery_data();
        }
        break;
    case HMIHANDLER_D1_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_D1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            D1_t* ptr_msg = reinterpret_cast<D1_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_D1_ID));
            int32_t temp_sensor_passenger_compartment = ptr_msg->temp_sens_passenger_compt + D1_CANID_TEMPSENSPASSENGERCOMPARTMENT_OFFSET;
            int32_t temp_sens_cabin = ptr_msg->temp_sens_cabin + D1_CANID_TEMPSENSCABIN_OFFSET;
            string str_temp = (temp_sens_cabin <= D1_CANID_TEMPSENSCABIN_MAXIMUM)
                    ? to_string(temp_sens_cabin)
                    : INVALID_VALUE;
            set_cabin_temperature1(str_temp.c_str());

            str_temp = (temp_sensor_passenger_compartment <= D1_CANID_TEMPSENSPASSENGERCOMPARTMENT_MAXIMUM)
                    ? to_string(temp_sensor_passenger_compartment)
                    : INVALID_VALUE;
            set_cabin_temperature2(str_temp.c_str());
        }
        break;
    case HMIHANDLER_AMB_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_AMB_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            AMB_t* ptr_msg = reinterpret_cast<AMB_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_AMB_ID));
            int32_t ambient_air_temperature = ((ptr_msg->ambient_air_temperature * AMB_AMBIENTAIRTEMPERATUREFACTOR) + AMB_CANID_AMBIENTAIRTEMPERATURE_OFFSET);
            string str_temp = (ambient_air_temperature <= AMB_CANID_AMBIENTAIRTEMPERATURE_MAXIMUM)
                    ? to_string(ambient_air_temperature)
                    : INVALID_VALUE;
            set_temperature(str_temp.c_str());
        }
        break;
    case HMIHANDLER_ETC2_ID:
        if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_ETC2_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            ETC2_t* ptr_msg = reinterpret_cast<ETC2_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_ETC2_ID));
            int transmission_current_gear = static_cast<uint8_t>(ptr_msg->current_gear) + ETC2_CANID_CURRENT_GEAR_OFFSET;
            set_gear_shift(transmission_current_gear);
        }
        break;
    default:
        break;
    }
    return true;
    CATCH_BLOCK
}

void QtCentralDashboard::update_map_main_data(QString key_map, QString lang_text, QString init_value, QString uom)
{
    TRY_BLOCK
    QList<QStringList> menu_value_list{};
    QStringList menu_value_data{};

    menu_value_data.append(lang_text);
    menu_value_data.append(init_value);
    menu_value_data.append(uom);
    menu_value_list << menu_value_data;
    if (map_main_data.contains(key_map))
        map_main_data.remove(key_map);

    map_main_data.insert(key_map, menu_value_list);
    CATCH_BLOCK
}

bool QtCentralDashboard::update_maindata(string element_value, QString key_data)
{
    TRY_BLOCK
    if (map_main_data.contains(key_data))
    {
        QList<QStringList>*value_data = &map_main_data[key_data];
        QStringList* second_element = &value_data[0][0];
        QString str_temp = QString::fromStdString(element_value);
        if (QString::compare(second_element[0][1], str_temp))
        {
            second_element[0][1] = str_temp;
            return true;
        }
    }
    return false;
    CATCH_BLOCK
}

QString QtCentralDashboard::get_temperature() const
{
    TRY_BLOCK
    return _temperature;
    CATCH_BLOCK
}

void QtCentralDashboard::set_temperature(QString temperature)
{
    TRY_BLOCK
    if (_temperature == temperature) {
        return;
    }
    _temperature = temperature;
    emit temperature_changed();
    CATCH_BLOCK
}

QString QtCentralDashboard::get_cabin_temperature1() const
{
    TRY_BLOCK
    return _cabin_temperature1;
    CATCH_BLOCK
}

void QtCentralDashboard::set_cabin_temperature1(QString cabin_temperature1)
{
    TRY_BLOCK
    if (_cabin_temperature1 == cabin_temperature1) {
        return;
    }
    _cabin_temperature1 = cabin_temperature1;
    emit cabin_temperature1_changed();
    CATCH_BLOCK
}

QString QtCentralDashboard::get_cabin_temperature2() const
{
    TRY_BLOCK
    return _cabin_temperature2;
    CATCH_BLOCK
}

void QtCentralDashboard::set_cabin_temperature2(QString cabin_temperature2)
{
    TRY_BLOCK
    if (_cabin_temperature2 == cabin_temperature2) {
        return;
    }
    _cabin_temperature2 = cabin_temperature2;
    emit cabin_temperature2_changed();
    CATCH_BLOCK
}

const QString& QtCentralDashboard::get_present_date() const
{
    TRY_BLOCK
    return _present_date;
    CATCH_BLOCK
}

void QtCentralDashboard::set_present_date(const QString& new_present_date)
{
    TRY_BLOCK
    if (_present_date == new_present_date) {
        return;
    }
    _present_date = new_present_date;
    emit present_date_changed();
    CATCH_BLOCK
}

const QString& QtCentralDashboard::get_present_time() const
{
    TRY_BLOCK
    return _present_time;
    CATCH_BLOCK
}

void QtCentralDashboard::set_present_time(const QString& new_present_time)
{
    TRY_BLOCK
    if (_present_time == new_present_time) {
        return;
    }
    _present_time = new_present_time;
    emit present_time_changed();
    CATCH_BLOCK
}

void QtCentralDashboard::update_central_dashboard_text()
{
    TRY_BLOCK
    this->initialize_central_dashboard_data();
    CATCH_BLOCK
}

void QtCentralDashboard::qml_responses(int value)
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
        connect(timer, &QTimer::timeout, [=] {
            _state = QmlState::QMLSTATE_NORMAL;
            timer->stop();
            delete timer;
        });

        timer->start(2000);
    }
    CATCH_BLOCK
}

const QList<QStringList>& QtCentralDashboard::get_mileage() const
{
    TRY_BLOCK
    return (map_main_data.find(MILEAGE)).value();
    CATCH_BLOCK
}

void QtCentralDashboard::set_mileage(const QList<QStringList>& newMileage)
{
    TRY_BLOCK
    if ((map_main_data[MILEAGE] == newMileage) && (_state != QMLSTATE_REFRESH))
        return;
    map_main_data[MILEAGE] = newMileage;
    emit mileage_changed();
    CATCH_BLOCK
}

QString QtCentralDashboard::get_fuel_level() const
{
    TRY_BLOCK
    return _fuel_level;
    CATCH_BLOCK
}

void QtCentralDashboard::set_fuel_level(const QString& new_fuel_level)
{
    TRY_BLOCK
    if (_fuel_level != new_fuel_level && (_state != QMLSTATE_REFRESH))
    {
        _fuel_level = new_fuel_level;
        emit fuel_level_changed();
    }
    CATCH_BLOCK
}
const QList<QStringList>& QtCentralDashboard::get_daily_fuel_consumption() const
{
    TRY_BLOCK
    return (map_main_data.find(DAILY_FUEL_CONSUMPTION)).value();
    CATCH_BLOCK
}

void QtCentralDashboard::set_daily_fuel_consumption(const QList<QStringList>& newDaily_fuel_consumption)
{
    TRY_BLOCK
    if ((map_main_data[DAILY_FUEL_CONSUMPTION] == newDaily_fuel_consumption) && (_state != QMLSTATE_REFRESH))
        return;
    map_main_data[DAILY_FUEL_CONSUMPTION] = newDaily_fuel_consumption;
    emit daily_fuel_consumption_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtCentralDashboard::get_pressure_uom() const
{
    TRY_BLOCK
    return map_main_data.find(PRESSURE_UOM).value();
    CATCH_BLOCK
}

void QtCentralDashboard::set_pressure_uom(const QList<QStringList>& newPressure_uom)
{
    TRY_BLOCK
    if ((map_main_data[PRESSURE_UOM] == newPressure_uom) && (_state != QMLSTATE_REFRESH))
        return;
    map_main_data[PRESSURE_UOM] = newPressure_uom;
    emit pressure_uom_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtCentralDashboard::get_engine_uom() const
{
    TRY_BLOCK
    return map_main_data.find(ENGINE_UOM).value();
    CATCH_BLOCK
}

void QtCentralDashboard::set_engine_uom(const QList<QStringList>& newEngine_uom)
{
    TRY_BLOCK
    if ((map_main_data[ENGINE_UOM] == newEngine_uom) && (_state != QMLSTATE_REFRESH))
        return;
    map_main_data[ENGINE_UOM] = newEngine_uom;
    emit engine_uom_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtCentralDashboard::get_speed_uom() const
{
    TRY_BLOCK
    return map_main_data.find(SPEED_UOM).value();
    CATCH_BLOCK
}

void QtCentralDashboard::set_speed_uom(const QList<QStringList>& newSpeed_uom)
{
    TRY_BLOCK
    if ((map_main_data[SPEED_UOM] == newSpeed_uom) && (_state != QMLSTATE_REFRESH))
        return;
    map_main_data[SPEED_UOM] = newSpeed_uom;
    emit speed_uom_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtCentralDashboard::get_fuel_consumption() const
{
    TRY_BLOCK
    return map_main_data.find(FUEL_CONSUMPTION).value();
    CATCH_BLOCK
}

void QtCentralDashboard::set_fuel_consumption(const QList<QStringList>& newFuel_consumption)
{
    TRY_BLOCK
    if ((map_main_data[FUEL_CONSUMPTION] == newFuel_consumption) && (_state != QMLSTATE_REFRESH))
        return;
    map_main_data[FUEL_CONSUMPTION] = newFuel_consumption;
    emit fuel_consumption_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtCentralDashboard::get_engine_coolant_temperature() const
{
    TRY_BLOCK
    return map_main_data.find(ENGINE_COOLANT_TEMPERATURE).value();
    CATCH_BLOCK
}

void QtCentralDashboard::set_engine_coolant_temperature(const QList<QStringList>& newEngine_coolant_temperature)
{
    TRY_BLOCK
    if ((map_main_data[ENGINE_COOLANT_TEMPERATURE] == newEngine_coolant_temperature) && (_state != QMLSTATE_REFRESH))
        return;
    map_main_data[ENGINE_COOLANT_TEMPERATURE] = newEngine_coolant_temperature;
    emit engine_coolant_temperature_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtCentralDashboard::get_battery_ampere() const
{
    TRY_BLOCK
    return map_main_data.find(BATTERY_AMPERE).value();
    CATCH_BLOCK
}

void QtCentralDashboard::set_battery_ampere(const QList<QStringList>& newBattery_ampere)
{
    TRY_BLOCK
    if ((map_main_data[BATTERY_AMPERE] == newBattery_ampere) && (_state != QMLSTATE_REFRESH))
        return;
    map_main_data[BATTERY_AMPERE] = newBattery_ampere;
    emit battery_ampere_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtCentralDashboard::get_battery_voltage() const
{
    TRY_BLOCK
    return map_main_data.find(BATTERY_VOLTAGE).value();
    CATCH_BLOCK
}

void QtCentralDashboard::set_battery_voltage(const QList<QStringList>& newBattery_voltage)
{
    TRY_BLOCK
    if ((map_main_data[BATTERY_VOLTAGE] == newBattery_voltage) && (_state != QMLSTATE_REFRESH))
        return;
    map_main_data[BATTERY_VOLTAGE] = newBattery_voltage;
    emit battery_voltage_changed();
    CATCH_BLOCK
}

const QList<QStringList>& QtCentralDashboard::get_trip_distance() const
{
    TRY_BLOCK
    return map_main_data.find(TRIP_DISTANCE).value();
    CATCH_BLOCK
}

void QtCentralDashboard::set_trip_distance(const QList<QStringList>& newTrip_distance)
{
    TRY_BLOCK
    if ((map_main_data[TRIP_DISTANCE] == newTrip_distance) && (_state != QMLSTATE_REFRESH))
        return;
    map_main_data[TRIP_DISTANCE] = newTrip_distance;
    emit trip_distance_changed();
    CATCH_BLOCK
}

const int& QtCentralDashboard::get_gear_shift() const
{
    TRY_BLOCK
    return m_shift;
    CATCH_BLOCK
}

void QtCentralDashboard::set_gear_shift(const int& newGear)
{
    TRY_BLOCK
    if ((m_shift == newGear) && (_state != QMLSTATE_REFRESH))
        return;
    m_shift = newGear;
    emit gear_shift_changed();
    CATCH_BLOCK
}

void QtCentralDashboard::init_subscribe()
{
    TRY_BLOCK
    auto ptrnotifer = subscribe_notifer::get_instance();
    ptrnotifer->subscribe(HMIHANDLER_TD_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_VDHR_EE_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_DD_INFO1_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_ET1_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_DYN_BB_CURRENT_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_CBCU2_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_D1_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_AMB_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_ETC2_ID, this);
    CATCH_BLOCK
}
