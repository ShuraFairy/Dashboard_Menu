#include "menu_handler.h"
#include <QMutexLocker>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

#define STR(x) #x

using namespace std;

static uint8_t vehicle_type = 0;
static TireDetails tyre_static_data[TIRE_POSITION_TOTAL];
mutex MenuHandler::build_lock_mutex;
shared_ptr<MenuHandler> MenuHandler::m_ptr_instance(nullptr);
static const map<uint8_t, TirePosition> g_tire_position_details
{
    {0x00, TIRE_POSITION_1}, {0x01, TIRE_POSITION_2},
    {0x11, TIRE_POSITION_3}, {0x10, TIRE_POSITION_4},
    {0x12, TIRE_POSITION_5}, {0x13, TIRE_POSITION_6},
    {0x20, TIRE_POSITION_7}, {0x21, TIRE_POSITION_8},
    {0x22, TIRE_POSITION_9}, {0x23, TIRE_POSITION_10}
};

static vector<tuple<VehicleName, float, float, float, float, float, float>> g_tyre_warnings_data;
void init_tyre_warnings()
{
    TRY_BLOCK
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ429260_79, (float)7.75, (float)7.40, (float)7.00, (float)8.75, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ529265_79, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ621365_79, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ529265_80, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ621365_80, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ529271_79_CNG, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ621371_79_CNG, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ529271_80_CNG, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ621371_80_CNG, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ529265_79_Diesel, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ621365_79_Diesel, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ529265_80_Diesel, (float)8.75, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.40));
    g_tyre_warnings_data.push_back(make_tuple(VEHICLE_NAME_LIAZ62174_79_ELECTRIC, (float)8.70, (float)8.30, (float)7.90, (float)10.00, (float)0.30, (float)0.80));
    CATCH_BLOCK
};

MenuHandler::MenuHandler()
    : _menu_data()
    , _prev_avrg_inst()
    , _pavrg_100km()
    , _nvm()
{
    _vehicle_details.clear();
    json_menu_handler = QtJsonMenuHandler::get_instance();
    json_menu_handler->init();
    // QMutexLocker locker(&MenuItemsMutexUtility::shared_mutex);
    init_menu_parameter_data();
    init_menu_diagnostics_data();
    init_menu_settings_data();
    init_menu_services_data();
    init_add_data_to_map();
    menu_diagnostic_handler = MenuDiagnosticsHandler::get_instance(&_menu_data);
    menu_settings_handler = MenuSettingsHandler::get_instance(&_menu_data);
    menu_services_handler = MenuServicesHandler::get_instance(&_menu_data);

    DD_INFO3_t dd_info3;    
    dd_info3.data  = std::strtoull(QtJsonConfigureData::get_instance()->get_config_data("subitem_menu_visibility").toLocal8Bit(),NULL, 16);
    _menu_data.set_subitem_visibility(dd_info3);

    _update_data = HmiHandler::getInstance();
    init_subscribe();
}

MenuHandler::~MenuHandler()
{
}

MenuHandler* MenuHandler::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard<mutex> build_lock(build_lock_mutex);
        m_ptr_instance = shared_ptr<MenuHandler>(new MenuHandler);
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

void MenuHandler::update_all_menu_data()
{
    TRY_BLOCK
    update_parameterdata();
    menu_diagnostic_handler->update_diagnostics_data();
    menu_services_handler->update_services_data();
    menu_settings_handler->update_settings_data();
    CATCH_BLOCK
}

void MenuHandler::update_parameterdata()
{
    TRY_BLOCK
    // QMutexLocker locker(&MenuItemsMutexUtility::shared_mutex);
    update_engine_data();
    update_transmission_data();
    update_battery_data();
    update_pneumatic_data();
    update_wipers_data();
    update_reagentadblue_data();
    update_tyre_temperature_pressure_data();
    update_brakepads_data();
//    update_vehicle_type_data();
    CATCH_BLOCK
}

void MenuHandler::init_menu_parameter_data()
{
    TRY_BLOCK
    // QMutexLocker locker(&MenuItemsMutexUtility::shared_mutex);
    _menu_data.submenus[E_MT_PARAMETERS].item_name = PARAMETERS;
    init_engine_data();
    init_transmission_data();
    init_battery_data();
    init_pneumatic_data();
    init_tirepress_temp_data();
    init_brakepads_data();
    init_wipers_data();
    init_reagentadblue_data();
    CATCH_BLOCK
}

void MenuHandler::init_menu_diagnostics_data()
{
    TRY_BLOCK
    _menu_data.submenus[E_MT_DIAGNOSTICS].item_name = DIAGNOSTICS;
    CATCH_BLOCK
}

void MenuHandler::init_menu_settings_data()
{
    TRY_BLOCK
    _menu_data.submenus[E_MT_SETTINGS].item_name = SETTINGS;
    CATCH_BLOCK
}

void MenuHandler::init_menu_services_data()
{
    TRY_BLOCK
    _menu_data.submenus[E_MT_SERVICES].item_name = SERVICES;
    CATCH_BLOCK
}

QtJsonMenuHandler::JsonMenuData* MenuHandler::init_any(int _number, QString _module)
{
    TRY_BLOCK
    string counter = to_string(_number);
    return json_menu_handler->get_menu_data(PARAMETERS, _module, QString::fromStdString(counter));
    CATCH_BLOCK
}

void MenuHandler::init_any_data(string _submenu_page_key, uint8_t _parameters_count)
{
    TRY_BLOCK
    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[_submenu_page_key].item_name = _submenu_page_key;
    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[_submenu_page_key].opt_submenu_string.reserve(_parameters_count);
    for (int i = 1; i <= _parameters_count; i++)
    {
        auto tempItem = init_any(i, QString::fromStdString(_submenu_page_key));
        menu_string _temp_string;
        _temp_string.img_path = tempItem->image_path.toStdString();
        _temp_string.param_name = tempItem->parameter_name;
        _temp_string.max_value = tempItem->max_value.toInt();
        _temp_string.mid_value = tempItem->mid_value.toFloat();
        _temp_string.min_value = tempItem->min_value.toInt();
        _temp_string.value_type = E_PT_DIAPASONE;
        _temp_string.visibility = false;
        _temp_string.submenu_string = string(INIT_VALUE);
        _menu_data.submenus[E_MT_PARAMETERS].submenu_page[_submenu_page_key].opt_submenu_string.push_back(_temp_string);
    }
    CATCH_BLOCK

}
void MenuHandler::init_engine_data()
{
    TRY_BLOCK
    init_any_data(ENGINE, ENGINE_PARAMETERS_COUNT);
    CATCH_BLOCK
}

void MenuHandler::init_transmission_data()
{
    TRY_BLOCK
    init_any_data(TRANSMISSION, TRANSMISSION_PARAMETERS_COUNT);
    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[TRANSMISSION].opt_submenu_string.push_back(
        menu_string{.param_name = "", .uom = "", .min_value = nullopt,
                    .max_value = nullopt, .mid_value = nullopt, .img_path = nullopt,
                    .value_type = E_PT_CONSTVALUE, .visibility = true, .submenu_string = string(INIT_VALUE)});
    CATCH_BLOCK
}

void MenuHandler::init_battery_data()
{
    TRY_BLOCK
    init_any_data(BATTERY, BATTERY_PARAMETERS_COUNT);
    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[BATTERY].opt_submenu_string[1].visibility = false;
    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[BATTERY].opt_submenu_string[2].visibility = false;
    CATCH_BLOCK
}

void MenuHandler::init_pneumatic_data()
{
    TRY_BLOCK
    init_any_data(PNEUMATIC_SYSTEM, PNEUMATIC_SYSTEM_PARAMETERS_COUNT);
    CATCH_BLOCK
}

void MenuHandler::init_tirepress_temp_data()
{
    TRY_BLOCK
    uint8_t i = 0;
    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[TIRE_PRESSURE_AND_TEMPERATURE].item_name = TIRE_PRESSURE_AND_TEMPERATURE;
    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[TIRE_PRESSURE_AND_TEMPERATURE].opt_submenu_string.reserve(TIRE_POSITION_TOTAL);

    for (i = 0; i < TIRE_POSITION_TOTAL; i++) {
        _menu_data.submenus[E_MT_PARAMETERS].submenu_page[TIRE_PRESSURE_AND_TEMPERATURE].opt_submenu_string.emplace_back
            (menu_string{.param_name = INIT_TYRE_TEMPERATURE, .uom = "", .min_value = _menu_data.vehicle_type, .max_value = 0, .mid_value = nullopt, .img_path = TYRE_INIT_COLOR,
            .value_type = E_PT_TIRES, .visibility = true, .submenu_string = string{"0.00"}});
    }

    for (i = 0; i < TIRE_POSITION_TOTAL; i++) {
        tyre_static_data[i].tire_temperature_data = 0;
        tyre_static_data[i].tire_pressure_data = 0;
        tyre_static_data[i].tire_status = 0;
        tyre_static_data[i].tire_sensor_elect_fault = 0;
    }
    CATCH_BLOCK
}

void MenuHandler::init_brakepads_data()
{
    TRY_BLOCK
    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[BRAKE_PADS_WEAR].item_name = BRAKE_PADS_WEAR;
//    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[BRAKE_PADS_WEAR].visibility = false;
    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[BRAKE_PADS_WEAR].opt_submenu_string.reserve(6);
    for (auto i = 0; i < 6; i++)
        _menu_data.submenus[E_MT_PARAMETERS].submenu_page[BRAKE_PADS_WEAR].opt_submenu_string.emplace_back(
            menu_string{.param_name = "", .uom = "", .min_value = nullopt,
                        .max_value = nullopt, .mid_value = nullopt, .img_path = nullopt,
                        .value_type = E_PT_BRAKEPADS, .visibility = true, .submenu_string = string(INVALID_SIGNAL)});
    CATCH_BLOCK
}

void MenuHandler::init_wipers_data()
{
    TRY_BLOCK
    init_any_data(WIPERS, 1);
    _menu_data.submenus[E_MT_PARAMETERS].submenu_page[WIPERS].opt_submenu_string.push_back(
        menu_string{.param_name = "", .uom = "", .min_value = nullopt,
                    .max_value = nullopt, .mid_value = nullopt, .img_path = nullopt,
                    .value_type = E_PT_CONSTVALUE, .visibility = true, .submenu_string = string(INIT_VALUE)});
    CATCH_BLOCK
}

void MenuHandler::init_reagentadblue_data()
{
    TRY_BLOCK
    init_any_data(REAGENT_ADBLUE, 2);
    CATCH_BLOCK
}

void MenuHandler::init_add_data_to_map()
{
    TRY_BLOCK
    /* Adding Vehicle Details to the map */
    _vehicle_details[VEHICLE_NAME_LIAZ429260_79] = 2;
    _vehicle_details[VEHICLE_NAME_LIAZ529265_79] = 2;
    _vehicle_details[VEHICLE_NAME_LIAZ621365_79] = 3;
    _vehicle_details[VEHICLE_NAME_LIAZ529265_80] = 2;
    _vehicle_details[VEHICLE_NAME_LIAZ621365_80] = 3;
    _vehicle_details[VEHICLE_NAME_LIAZ62174_79_ELECTRIC] = 2;
    _vehicle_details[VEHICLE_NAME_LIAZ529271_79_CNG] = 2;
    _vehicle_details[VEHICLE_NAME_LIAZ621371_79_CNG] = 3;
    _vehicle_details[VEHICLE_NAME_LIAZ529271_80_CNG] = 2;
    _vehicle_details[VEHICLE_NAME_LIAZ621371_80_CNG] = 3;
    _vehicle_details[VEHICLE_NAME_LIAZ529265_79_Diesel] = 2;
    _vehicle_details[VEHICLE_NAME_LIAZ621365_79_Diesel] = 3;
    _vehicle_details[VEHICLE_NAME_LIAZ529265_80_Diesel] = 2;
    _vehicle_details[VEHICLE_NAME_LIAZ621365_80_Diesel] = 3;

    /* Tyre Pressure Warining Details */
    init_tyre_warnings();
    CATCH_BLOCK
}
void MenuHandler::init_subscribe()
{
    TRY_BLOCK
    auto ptr_notifer = subscribe_notifer::get_instance();
    ptr_notifer->subscribe(HMIHANDLER_ET1_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_EFL_P1_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_LFE1_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_VDHR_EE_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_TRF1_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_RF_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_ETC1_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_CBCU2_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DYN_BB_CURRENT_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_TIRE_CONDITION_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_EBC4_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_AIR1_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_LS_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_D1_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_AT1T1I_ID, this);
    CATCH_BLOCK
}

bool MenuHandler::update_info(uint32_t _id)
{
    TRY_BLOCK
    switch(_id)
    {
    case HMIHANDLER_ET1_ID:
    case HMIHANDLER_EFL_P1_ID:
    case HMIHANDLER_LFE1_ID:
    case HMIHANDLER_VDHR_EE_ID:
        update_engine_data();
        break;
    case HMIHANDLER_TRF1_ID:
    case HMIHANDLER_RF_ID:
    case HMIHANDLER_ETC1_ID:
        update_transmission_data();
        break;
    case HMIHANDLER_CBCU2_ID:
    case HMIHANDLER_DYN_BB_CURRENT_ID:
        update_battery_data();
        break;
    case HMIHANDLER_TIRE_CONDITION_ID:
        update_tyre_temperature_pressure_data();
        break;
    case HMIHANDLER_EBC4_ID:
        update_brakepads_data();
        break;
    case HMIHANDLER_AIR1_ID:
        update_pneumatic_data();
        break;
    case HMIHANDLER_LS_ID:
    case HMIHANDLER_D1_ID:
        update_wipers_data();
        break;
    case HMIHANDLER_AT1T1I_ID:
        update_reagentadblue_data();
    }
    return true;
    CATCH_BLOCK
}

void MenuHandler::update_engine_data()
{
    TRY_BLOCK
    ET1_t* et1_msg = nullptr;
    string* ptr_coolant_temperature = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[ENGINE].opt_submenu_string[0].submenu_string));
    string* ptr_oil_temperature = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[ENGINE].opt_submenu_string[1].submenu_string));
    qDebug("coolant_temp");
    if (_update_data->get_ptr_to_msg(HMIHANDLER_ET1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        et1_msg = reinterpret_cast<ET1_t*>(_update_data->get_data_from_msg(HMIHANDLER_ET1_ID));
    /* Coolant temperature */
        int16_t _can_value_int16 = (int16_t)(et1_msg->engine_coolant_temperature + ENGINE_COOLANT_OFFSET);
        if ((_can_value_int16 >= MIN_COOLANT_TEMP) && (_can_value_int16 <= MAX_COOLANT_TEMP)) {
            *ptr_coolant_temperature = to_string(_can_value_int16);
        } else {
            *ptr_coolant_temperature = INVALID_SIGNAL;
        }

        /* Oil Temperature */
        int32_t _can_value_int32 = (int32_t)(et1_msg->SPN175_engine_oil_temperature);
        _can_value_int32 = (_can_value_int32 * ET1_CANID_SPN175_ENGINEOILTEMPERATURE_FACTOR) + ET1_CANID_SPN175_ENGINEOILTEMPERATURE_OFFSET;
        if ((_can_value_int32 >= MIN_ENGINE_OIL_TEMPERATURE) && (_can_value_int32 <= MAX_ENGINE_OIL_TEMPERATURE)) {
            *ptr_oil_temperature = to_string(_can_value_int32);
        } else {
            *ptr_oil_temperature = INVALID_SIGNAL;
        }
    }
    else
    {
        *ptr_coolant_temperature = INVALID_SIGNAL;
        *ptr_oil_temperature = INVALID_SIGNAL;
    }
    /* Oil Pressure */
    //    _can_value_uint8 = (uint8_t)(_update_data->handle_efl_p1_msg_get()->engine_oilpressure);

    //    if ((((_can_value_uint8 * EFL_P1_ENGINEOILPRESSUREFACTOR) / EFL_P1_ENGINEOILPRESSURE_VALUE_CONVERTOR) >= MIN_PRESSURE_BAR) && (((_can_value_uint8 * EFL_P1_ENGINEOILPRESSUREFACTOR) / EFL_P1_ENGINEOILPRESSURE_VALUE_CONVERTOR) <= MAX_PRESSURE_BAR)) {
    //        _menu_data.parameters.engine.oil_pressure.value = to_string((_can_value_uint8 * EFL_P1_ENGINEOILPRESSUREFACTOR) / EFL_P1_ENGINEOILPRESSURE_VALUE_CONVERTOR);
    //    } else {
    //        _menu_data.parameters.engine.oil_pressure.value = INVALID_SIGNAL;
    //    }
    qDebug("pressure");

    string* ptr_oil_pressure = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[ENGINE].opt_submenu_string[2].submenu_string));
    EFL_P1_t* efl_msg = nullptr;
    if (_update_data->get_ptr_to_msg(HMIHANDLER_EFL_P1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        efl_msg = reinterpret_cast<EFL_P1_t*>(_update_data->get_data_from_msg(HMIHANDLER_EFL_P1_ID));
        float _can_value_float = (float)(efl_msg->engine_oilpressure);
        float _can_compare = static_cast<float>((_can_value_float * EFL_P1_ENGINEOILPRESSUREFACTOR) / EFL_P1_ENGINEOILPRESSURE_VALUE_CONVERTOR);
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << _can_compare << " ";

        if ((_can_compare >= MIN_PRESSURE_BAR) && (_can_compare <= MAX_PRESSURE_BAR)) {
            *ptr_oil_pressure = oss.str();
        } else {
            *ptr_oil_pressure = INVALID_SIGNAL;
        }
    }
    else
    {
        *ptr_oil_pressure = INVALID_SIGNAL;
    }
    /* Instant Fuel Consumption */
    qDebug("instant");

    string* ptr_instant_fuel_consumption = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[ENGINE].opt_submenu_string[3].submenu_string));
    LFE1_t* lfe1_msg = nullptr;
    if (_update_data->get_ptr_to_msg(HMIHANDLER_LFE1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        lfe1_msg = reinterpret_cast<LFE1_t*>(_update_data->get_data_from_msg(HMIHANDLER_LFE1_ID));
        uint16_t _can_value_uint16 = (uint16_t)(lfe1_msg->engine_flue_rate);

        if (((_can_value_uint16 * LFE1_SPN183_ENGINEFLUERATEFACTOR) >= MIN_FUEL_CONSUMPTION)
                && ((_can_value_uint16 * LFE1_SPN183_ENGINEFLUERATEFACTOR) <= MAX_FUEL_CONSUMPTION))
        {
            QString _float_value = QString::number((_can_value_uint16 * LFE1_SPN183_ENGINEFLUERATEFACTOR), 'f', 1);
            *ptr_instant_fuel_consumption = (_float_value).toStdString();
        } else {
            *ptr_instant_fuel_consumption = INVALID_SIGNAL;
        }
    }
    else
    {
        *ptr_instant_fuel_consumption = INVALID_SIGNAL;
    }
    /* Average Fuel Consumption */
    VDHR_EE_t* vdhr_msg = nullptr;
    string* ptr_average_fuel_consumption = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[ENGINE].opt_submenu_string[4].submenu_string));
    if (_update_data->get_ptr_to_msg(HMIHANDLER_VDHR_EE_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        vdhr_msg = reinterpret_cast<VDHR_EE_t*>(_update_data->get_data_from_msg(HMIHANDLER_VDHR_EE_ID));
        qreal _trip_distance = (vdhr_msg->spn918_high_resolution_trip_di * VDHR_EE_SPN918_HIGHRESOLUTIONTRIPDIFACTOR) / METER_TO_KM_CONVERTOR;
        qreal _pres_avrg_inst = 0;
        if (lfe1_msg)
            _pres_avrg_inst = lfe1_msg->engine_flue_rate * LFE1_SPN183_ENGINEFLUERATEFACTOR;

        _nvm += ((_prev_avrg_inst + _pres_avrg_inst) / (AVERAGE_FUEL_CONSUMPTION * AVERAGE_SECONDS));

        _pavrg_100km = (_nvm * TWO_SECONDS * 10.f) / _trip_distance;
        if ((_pavrg_100km >= MIN_LETER_PER_100KM) && (_pavrg_100km <= MAX_LETER_PER_100KM)) {
            QString _float_value = QString::number(_pavrg_100km, 'f', 1);
            *ptr_average_fuel_consumption = (_float_value).toStdString();
        } else {
            *ptr_average_fuel_consumption = INVALID_SIGNAL;
        }
        _prev_avrg_inst = _pres_avrg_inst;
    }
    else
    {
        *ptr_average_fuel_consumption = INVALID_SIGNAL;
    }
    _menu_data.check_active_list(&_menu_data.submenus[E_MT_PARAMETERS].submenu_page[ENGINE]);
    CATCH_BLOCK
}

void MenuHandler::update_transmission_data()
{
    TRY_BLOCK
    /* Oil Temperature */
    TRF1_t* trf1_msg = nullptr;
    string* ptr_oil_temperature = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[TRANSMISSION].opt_submenu_string[E_MTP_TRANS_OIL_TEMP].submenu_string));
    if (_update_data->get_ptr_to_msg(HMIHANDLER_TRF1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        trf1_msg = reinterpret_cast<TRF1_t*>(_update_data->get_data_from_msg(HMIHANDLER_TRF1_ID));
        int32_t _can_value_int32 = (int32_t)(trf1_msg->trans_oil_temp1 * ET1_CANID_SPN175_ENGINEOILTEMPERATURE_FACTOR + MIN_TRANSMISSION_OIL_TEMPERATURE);
        if ((_can_value_int32 >= MIN_TRANSMISSION_OIL_TEMPERATURE)
                && (_can_value_int32 <= MAX_TRANSMISSION_OIL_TEMPERATURE))
            *ptr_oil_temperature = to_string(_can_value_int32);
        else
            *ptr_oil_temperature = INVALID_SIGNAL;
    }
    else
    {
        *ptr_oil_temperature = INVALID_SIGNAL;
    }
    /* Oil Temperature in Hydraulic Retarder */
    RF_t* rf_msg = nullptr;
    string* ptr_oil_temp_hydraulic_retarder = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[TRANSMISSION].opt_submenu_string[E_MTP_TRANS_OIL_TEMP_HYDR].submenu_string));
    if (_update_data->get_ptr_to_msg(HMIHANDLER_RF_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        rf_msg = reinterpret_cast<RF_t*>(_update_data->get_data_from_msg(HMIHANDLER_RF_ID));
        int16_t _can_value_int16 = (((int16_t)(rf_msg->hyd_retarder_oil_temp)) + OFFSET_MINUS_40);
        if ((_can_value_int16 >= MIN_TRANSMISSION_OIL_TEMPERATURE_HYDRAULIC_RETARDER) && (_can_value_int16 <= MAX_TRANSMISSION_OIL_TEMPERATURE_HYDRAULIC_RETARDER)) {
            *ptr_oil_temp_hydraulic_retarder = to_string(_can_value_int16);
        } else {
            *ptr_oil_temp_hydraulic_retarder = INVALID_SIGNAL;
        }
    }
    else
    {
        *ptr_oil_temp_hydraulic_retarder = INVALID_SIGNAL;
    }
    /* Output Shaft Speed */
    ETC1_t* etc1_msg = nullptr;
    string* ptr_output_shaft_rpm = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[TRANSMISSION].opt_submenu_string[E_MTP_TRANS_OUT_SHAFT_SPEED].submenu_string));
    if (_update_data->get_ptr_to_msg(HMIHANDLER_ETC1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        etc1_msg = reinterpret_cast<ETC1_t*>(_update_data->get_data_from_msg(HMIHANDLER_ETC1_ID));
        uint16_t _can_value_uint16 = ((uint16_t)(etc1_msg->output_speed_TCU)) * TRANSMISSION_OUTPUT_SHAFT_SPEED_FACTOR;
        if (_can_value_uint16 <= MAX_OUTPUT_SHAFT_SPEED) {
            *ptr_output_shaft_rpm = to_string(_can_value_uint16);
        } else {
            *ptr_output_shaft_rpm = INVALID_SIGNAL;
        }
    }
    else
    {
        *ptr_output_shaft_rpm = INVALID_SIGNAL;
    }
    _menu_data.check_active_list(&_menu_data.submenus[E_MT_PARAMETERS].submenu_page[TRANSMISSION]);
    CATCH_BLOCK
}

void MenuHandler::update_battery_data()
{
    TRY_BLOCK
    CBCU2_t* cbcu2_msg = nullptr;
    string* ptr_voltage = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[BATTERY].opt_submenu_string[0].submenu_string));
    if (_update_data->get_ptr_to_msg(HMIHANDLER_CBCU2_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        cbcu2_msg = reinterpret_cast<CBCU2_t*>(_update_data->get_data_from_msg(HMIHANDLER_CBCU2_ID));
        uint16_t _can_value_uint16 = (uint16_t)(cbcu2_msg->cbcu_mainpwr);
        if (((_can_value_uint16 * CBCU2_CBCU_MAINPWRFACTOR) >= MIN_VOLTAGE) && ((_can_value_uint16 * CBCU2_CBCU_MAINPWRFACTOR) <= MAX_VOLTAGE)) {
            QString _float_value = QString::number((_can_value_uint16 * CBCU2_CBCU_MAINPWRFACTOR), 'f', 1);
            *ptr_voltage = (_float_value).toStdString();
        } else {
            *ptr_voltage = INVALID_SIGNAL;
        }
    }
    else
    {
        *ptr_voltage = INVALID_SIGNAL;
    }

    DYN_BB_CURRENT_t* dynbb_msg = nullptr;
    string* ptr_current1 = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[BATTERY].opt_submenu_string[1].submenu_string));
    string* ptr_current2 = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[BATTERY].opt_submenu_string[2].submenu_string));
    if (_update_data->get_ptr_to_msg(HMIHANDLER_DYN_BB_CURRENT_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        dynbb_msg = reinterpret_cast<DYN_BB_CURRENT_t*>(_update_data->get_data_from_msg(HMIHANDLER_DYN_BB_CURRENT_ID));
        int16_t _can_value_int16 = (int16_t)(dynbb_msg->current_1);
        if (((_can_value_int16 * DYN_BB_CURRENT_CURRENT_1FACTOR) >= MIN_CURRENT) && ((_can_value_int16 * DYN_BB_CURRENT_CURRENT_1FACTOR) <= MAX_CURRENT)) {
            QString _float_value = QString::number((_can_value_int16 * DYN_BB_CURRENT_CURRENT_1FACTOR), 'f', 1);
            *ptr_current1 = (_float_value).toStdString();
        } else {
            *ptr_current1 = INVALID_SIGNAL;
        }

        _can_value_int16 = (int16_t)(dynbb_msg->current_2);
        if (((_can_value_int16 * DYN_BB_CURRENT_CURRENT_2FACTOR) >= MIN_CURRENT) && ((_can_value_int16 * DYN_BB_CURRENT_CURRENT_2FACTOR) <= MAX_CURRENT)) {
            QString _float_value = QString::number((_can_value_int16 * DYN_BB_CURRENT_CURRENT_1FACTOR), 'f', 1);
            *ptr_current2 = (_float_value).toStdString();
        } else {
            *ptr_current2 = INVALID_SIGNAL;
        }
    }
    else
    {
        *ptr_current1 = INVALID_SIGNAL;
        *ptr_current2 = INVALID_SIGNAL;
    }
    _menu_data.check_active_list(&_menu_data.submenus[E_MT_PARAMETERS].submenu_page[BATTERY]);
    CATCH_BLOCK
}

void MenuHandler::update_tyre_temperature_pressure_data()
{
    TRY_BLOCK
    TyreWarningPressureDetails tyre_pressure_details;
    for (auto iterator : g_tyre_warnings_data)
        if (get<0>(iterator) == _menu_data.vehicle_name)
            tyre_pressure_details.fill(iterator);

    vector<uint8_t> twin_wheel_indices = { 2, 3, 4, 5, 6, 7, 8, 9 };
    float twin_wheel_pressure_difference_3_and_4 = 0;
/*
    float twin_wheel_pressure_difference_5_and_6 = 0;
    float twin_wheel_pressure_difference_7_and_8 = 0;
    float twin_wheel_pressure_difference_9_and_10 = 0;
*/
    TIRE_t* tire_msg = nullptr;
    if (_update_data->get_ptr_to_msg(HMIHANDLER_TIRE_CONDITION_ID)->get_state() != CAN_MESSAGE_STATE_OK)
        return;

    tire_msg = reinterpret_cast<TIRE_t*>(_update_data->get_data_from_msg(HMIHANDLER_TIRE_CONDITION_ID));
    uint8_t _can_value_uint8 = static_cast<uint8_t>(tire_msg->spn929_tire_location);
    int32_t tire_temperature = static_cast<int32_t>(tire_msg->spn242_tire_temperature);
    float tire_pressure = tire_msg->spn241_tire_pressure;

    tire_temperature = tire_temperature * TIRE_TEMPERATURE_FACTOR;
    tire_temperature = tire_temperature + TIRE_TEMPERATURE_OFFSET;
    tire_pressure = tire_pressure * TIRE_PRESSURE_FACTOR;
    tire_pressure /= 100;

    TirePosition tire_position = (TirePosition)(g_tire_position_details.find(_can_value_uint8)->second);
    uint8_t tire_status = (uint8_t)(tire_msg->spn1698_cti_tire_status);
    uint8_t tire_sensor_elec_fault = (uint8_t)(tire_msg->spn1697_cti_tire_senselectr_fault);

    if (_menu_data.vehicle_type > 0) {
        string* tyre_data;
        for (uint8_t i = 0; i < TIRE_POSITION_TOTAL; i++)
        {
            auto ptr_data = &_menu_data.submenus[E_MT_PARAMETERS].submenu_page[TIRE_PRESSURE_AND_TEMPERATURE].opt_submenu_string[i];
            tyre_data = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[TIRE_PRESSURE_AND_TEMPERATURE].opt_submenu_string[i].submenu_string));
            ptr_data->uom = TYRE_INIT_COLOR;

            if (i == tire_position)
            {
                ptr_data->min_value = _menu_data.vehicle_type;     //VEHICLE TYPE
                ptr_data->max_value = _can_value_uint8; //TIRE NUMBER
                ptr_data->param_name = QString::number(tire_temperature) + UOM_DEGREE_CELCIUS;
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(2) << tire_pressure;
                *tyre_data = oss.str();

                // Handle Tire Sensor Electrical Fault and Tire Status
                if ((tire_status == 0x01) || (tire_status == 0x10) || (tire_sensor_elec_fault == 0x01) || (tire_sensor_elec_fault == 0x10))
                {
                    ptr_data->img_path = TYRE_WARNING_COLOR;
                }

                tyre_static_data[i].tire_pressure_data = tire_pressure;
                tyre_static_data[i].tire_temperature_data = tire_temperature;
                tyre_static_data[i].tire_sensor_elect_fault = tire_sensor_elec_fault;
                tyre_static_data[i].tire_status = tire_status;
                /* Handling Exceed Twin Wheels */
                auto ptr_to_wheel = find(twin_wheel_indices.begin(), twin_wheel_indices.end(), i);
                if (ptr_to_wheel != twin_wheel_indices.end())
                {
                    if(*ptr_to_wheel && 1 == 1)
                        ptr_to_wheel--;

                    twin_wheel_pressure_difference_3_and_4 = fabs(tyre_static_data[*ptr_to_wheel].tire_pressure_data - tyre_static_data[*ptr_to_wheel+1].tire_pressure_data);
                    // Handle Exceed Permissable pressure between twin Tyres

                    auto temp_tyre_data = &(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[TIRE_PRESSURE_AND_TEMPERATURE].opt_submenu_string[*ptr_to_wheel]);
                    auto temp_tyre_data2 = &(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[TIRE_PRESSURE_AND_TEMPERATURE].opt_submenu_string[*ptr_to_wheel+1]);
                    if (twin_wheel_pressure_difference_3_and_4 > tyre_pressure_details.exceed_permissable_pressure_diff_twin_wheels) {
                        if (temp_tyre_data->img_path != TYRE_CRITICAL_COLOR) {
                            temp_tyre_data->img_path = TYRE_WARNING_COLOR;
                        }
                        if (temp_tyre_data2->img_path != TYRE_CRITICAL_COLOR) {
                            temp_tyre_data2->img_path = TYRE_WARNING_COLOR;
                        }
                    }

                }
            }
            else
            {
                if ((tyre_static_data[i].tire_status >= 0x01) || (tyre_static_data[i].tire_sensor_elect_fault >= 0x01)) {
                    ptr_data->img_path = TYRE_WARNING_COLOR;
                }
            }
            // Handle Low and High Pressure Warnings
            if ((tyre_static_data[i].tire_pressure_data > tyre_pressure_details.second_low_pressure_threshold) && (tyre_static_data[i].tire_pressure_data < tyre_pressure_details.first_low_pressure_threshold)) {
                ptr_data->img_path = TYRE_WARNING_COLOR;
            } else if (tyre_static_data[i].tire_pressure_data <= tyre_pressure_details.second_low_pressure_threshold || tyre_static_data[i].tire_pressure_data >= tyre_pressure_details.high_pressure_threshold) {
                ptr_data->img_path = TYRE_CRITICAL_COLOR;
            }
        }

/*      NOT NEED TO UPDATE STATIC DATA
        //    twin_wheel_pressure_difference_3_and_4 = fabs(tyre_pressure_data[2] - tyre_pressure_data[3]);
        twin_wheel_pressure_difference_3_and_4 = fabs(tyre_static_data[2].tire_pressure_data - tyre_static_data[3].tire_pressure_data);
        twin_wheel_pressure_difference_5_and_6 = fabs(tyre_static_data[4].tire_pressure_data - tyre_static_data[5].tire_pressure_data);
        twin_wheel_pressure_difference_7_and_8 = fabs(tyre_static_data[6].tire_pressure_data - tyre_static_data[7].tire_pressure_data);
        twin_wheel_pressure_difference_9_and_10 = fabs(tyre_static_data[8].tire_pressure_data - tyre_static_data[9].tire_pressure_data);


        float twin_wheel_pressure_differences[] = { twin_wheel_pressure_difference_3_and_4,
            twin_wheel_pressure_difference_5_and_6,
            twin_wheel_pressure_difference_7_and_8,
            twin_wheel_pressure_difference_9_and_10 };
*/
        /* Handle exceed same axle tyres */
        float same_axle_pressure_difference_wheel1_and_wheel2 = 0;
        float same_axle_pressure_difference_wheels34_and_wheels56 = 0;
        float same_axle_pressure_difference_wheels78_and_wheels910 = 0;

        float summation_pressure_twin_wheels_first = 0;
        float summation_pressure_twin_wheels_second = 0;
        same_axle_pressure_difference_wheel1_and_wheel2 = fabs(tyre_static_data[0].tire_pressure_data - tyre_static_data[1].tire_pressure_data);

        summation_pressure_twin_wheels_first = tyre_static_data[2].tire_pressure_data + tyre_static_data[3].tire_pressure_data;
        summation_pressure_twin_wheels_second = tyre_static_data[4].tire_pressure_data + tyre_static_data[5].tire_pressure_data;

        same_axle_pressure_difference_wheels34_and_wheels56 = fabs(summation_pressure_twin_wheels_first - summation_pressure_twin_wheels_second);

        summation_pressure_twin_wheels_first = tyre_static_data[6].tire_pressure_data + tyre_static_data[7].tire_pressure_data;
        summation_pressure_twin_wheels_second = tyre_static_data[8].tire_pressure_data + tyre_static_data[9].tire_pressure_data;
        same_axle_pressure_difference_wheels78_and_wheels910 = fabs(summation_pressure_twin_wheels_first - summation_pressure_twin_wheels_second);

        float same_axle_pressure_differences[] = {
            same_axle_pressure_difference_wheel1_and_wheel2,
            same_axle_pressure_difference_wheels34_and_wheels56,
            same_axle_pressure_difference_wheels78_and_wheels910
        };

        uint8_t start_index = 0;
        uint8_t end_index = 0;
        for (uint8_t i = 0; i < 3; i++) {
            switch (i) {
            case 0:
                start_index = 0;
                end_index = 1;
                break;
            case 1:
                start_index = 2;
                end_index = 5;
                break;
            case 2:
                start_index = 6;
                end_index = 9;
                break;
            default:
                break;
            }
            bool exceed_threshold = (same_axle_pressure_differences[start_index] > tyre_pressure_details.exceed_permissable_pressure_diff_same_axle);
            for (uint8_t j = start_index; j <= end_index; j++) {
                auto temp_tyre_data = &(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[TIRE_PRESSURE_AND_TEMPERATURE].opt_submenu_string[j]);
                if (exceed_threshold && (temp_tyre_data->img_path != TYRE_CRITICAL_COLOR)) {
                    temp_tyre_data->img_path = TYRE_WARNING_COLOR;
                }
            }
        }
    }
    _menu_data.check_active_list(&_menu_data.submenus[E_MT_PARAMETERS].submenu_page[TIRE_PRESSURE_AND_TEMPERATURE]);
    CATCH_BLOCK
}

void MenuHandler::update_brakepads_data()
{
    TRY_BLOCK
    uint8_t brake_lining = 0;
    string brakepads_color;
    string brake_lining_str;
    string* ptr_data = nullptr;
    EBC4_t* ebc4_msg = nullptr;
    if (_update_data->get_ptr_to_msg(HMIHANDLER_EBC4_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        ebc4_msg = reinterpret_cast<EBC4_t*>(_update_data->get_data_from_msg(HMIHANDLER_EBC4_ID));
        brake_lining = ((uint8_t)ebc4_msg->brk_lnng_rmining_front_axle_left_wheel * BRAKEPADS_FACTOR);
        brakepads_color = (brake_lining <= 10) ? TYRE_WARNING_COLOR : TYRE_INIT_COLOR;
        if (brake_lining > BRAKE_PADS_MAX_PERCENTAGE) {
            brake_lining_str = INVALID_SIGNAL;
        } else {
            brake_lining_str = to_string(brake_lining);
        }

        auto* ptr_brake_pad = &_menu_data.submenus[E_MT_PARAMETERS].submenu_page[BRAKE_PADS_WEAR].opt_submenu_string[0];
        ptr_data = get_if<string>(&(ptr_brake_pad->submenu_string));
        *ptr_data = brake_lining_str + UOM_PERCENTAGE + BRAKE_PADS_SEPERATOR + brakepads_color;
        ptr_brake_pad->uom = UOM_PERCENTAGE;
        ptr_brake_pad->param_name = QString::fromStdString(brakepads_color);
        ptr_brake_pad++;

        brake_lining = ((uint8_t)ebc4_msg->brk_lnng_rmining_front_axle_right_wheel * BRAKEPADS_FACTOR);
        brakepads_color = (brake_lining <= 10) ? TYRE_WARNING_COLOR : TYRE_INIT_COLOR;
        if (brake_lining > BRAKE_PADS_MAX_PERCENTAGE) {
            brake_lining_str = INVALID_SIGNAL;
        } else {
            brake_lining_str = to_string(brake_lining);
        }
        ptr_data = get_if<string>(&(ptr_brake_pad->submenu_string));
        *ptr_data = brake_lining_str + UOM_PERCENTAGE + BRAKE_PADS_SEPERATOR + brakepads_color;
        ptr_brake_pad->uom = UOM_PERCENTAGE;
        ptr_brake_pad->param_name = QString::fromStdString(brakepads_color);
        ptr_brake_pad++;

        brake_lining = ((uint8_t)ebc4_msg->brk_lnng_rmining_rear_axle1_left_wheel * BRAKEPADS_FACTOR);
        brakepads_color = (brake_lining <= 10) ? TYRE_WARNING_COLOR : TYRE_INIT_COLOR;
        if (brake_lining > BRAKE_PADS_MAX_PERCENTAGE) {
            brake_lining_str = INVALID_SIGNAL;
        } else {
            brake_lining_str = to_string(brake_lining);
        }
        ptr_data = get_if<string>(&(ptr_brake_pad->submenu_string));
        *ptr_data = brake_lining_str + UOM_PERCENTAGE + BRAKE_PADS_SEPERATOR + brakepads_color;
        ptr_brake_pad->uom = UOM_PERCENTAGE;
        ptr_brake_pad->param_name = QString::fromStdString(brakepads_color);
        ptr_brake_pad++;

        brake_lining = ((uint8_t)ebc4_msg->brk_lnng_rmining_rear_axle1_right_wheel * BRAKEPADS_FACTOR);
        brakepads_color = (brake_lining <= 10) ? TYRE_WARNING_COLOR : TYRE_INIT_COLOR;
        if (brake_lining > BRAKE_PADS_MAX_PERCENTAGE) {
            brake_lining_str = INVALID_SIGNAL;
        } else {
            brake_lining_str = to_string(brake_lining);
        }
        ptr_data = get_if<string>(&(ptr_brake_pad->submenu_string));
        *ptr_data = brake_lining_str + UOM_PERCENTAGE + BRAKE_PADS_SEPERATOR + brakepads_color;
        ptr_brake_pad->uom = UOM_PERCENTAGE;
        ptr_brake_pad->param_name = QString::fromStdString(brakepads_color);
        ptr_brake_pad++;

        brake_lining = ((uint8_t)ebc4_msg->brk_lnng_rmining_rear_axle2_left_wheel * BRAKEPADS_FACTOR);
        brakepads_color = (brake_lining <= 10) ? TYRE_WARNING_COLOR : TYRE_INIT_COLOR;
        if (brake_lining > BRAKE_PADS_MAX_PERCENTAGE) {
            brake_lining_str = INVALID_SIGNAL;
        } else {
            brake_lining_str = to_string(brake_lining);
        }
        ptr_data = get_if<string>(&(ptr_brake_pad->submenu_string));
        *ptr_data = brake_lining_str + UOM_PERCENTAGE + BRAKE_PADS_SEPERATOR + brakepads_color;
        ptr_brake_pad->uom = UOM_PERCENTAGE;
        ptr_brake_pad->param_name = QString::fromStdString(brakepads_color);
        ptr_brake_pad++;

        brake_lining = ((uint8_t)ebc4_msg->brk_lnng_rmining_rear_axle2_right_wheel * BRAKEPADS_FACTOR);
        brakepads_color = (brake_lining <= 10) ? TYRE_WARNING_COLOR : TYRE_INIT_COLOR;
        if (brake_lining > BRAKE_PADS_MAX_PERCENTAGE) {
            brake_lining_str = INVALID_SIGNAL;
        } else {
            brake_lining_str = to_string(brake_lining);
        }
        ptr_data = get_if<string>(&(ptr_brake_pad->submenu_string));
        *ptr_data = brake_lining_str + UOM_PERCENTAGE + BRAKE_PADS_SEPERATOR + brakepads_color;
        ptr_brake_pad->uom = UOM_PERCENTAGE;
        ptr_brake_pad->param_name = QString::fromStdString(brakepads_color);
        ptr_brake_pad++;
    }
    else
    {
        brake_lining_str = INVALID_SIGNAL;
        for (int i = 0; i < 6; i++)
        {
            auto* ptr_brake_pad = &_menu_data.submenus[E_MT_PARAMETERS].submenu_page[BRAKE_PADS_WEAR].opt_submenu_string[i];
            ptr_data = get_if<string>(&ptr_brake_pad->submenu_string);
            *ptr_data = brake_lining_str + UOM_PERCENTAGE + BRAKE_PADS_SEPERATOR + brakepads_color;
            ptr_brake_pad->uom = UOM_PERCENTAGE;
            ptr_brake_pad->param_name = QString::fromStdString(brakepads_color);
            ptr_brake_pad++;

        }
    }
    _menu_data.check_active_list(&_menu_data.submenus[E_MT_PARAMETERS].submenu_page[BRAKE_PADS_WEAR]);

    CATCH_BLOCK
}

//void MenuHandler::update_vehicle_type_data()
//{
//    TRY_BLOCK
//    FB1_t* fb1_msg = nullptr;
//    uint8_t _can_value_uint8 = 0;
//    if (_update_data->get_ptr_to_msg(HMIHANDLER_FB1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
//    {
//        fb1_msg = reinterpret_cast<FB1_t*>(_update_data->get_data_from_msg(HMIHANDLER_FB1_ID));
//        _can_value_uint8 = (uint8_t)(fb1_msg->EEPROM_par_bus_model);
//    }

//    _menu_data.vehicle_type = _vehicle_details[(VehicleName)_can_value_uint8];
//    _menu_data.vehicle_name = (VehicleName)_can_value_uint8;
//    CATCH_BLOCK
//}

void MenuHandler::update_pneumatic_data()
{
    TRY_BLOCK
    AIR1_t* air1_msg = nullptr;
    string intermediate_value = INVALID_SIGNAL;
    if (_update_data->get_ptr_to_msg(HMIHANDLER_AIR1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        string* rear_axle_breaking_circuit = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[PNEUMATIC_SYSTEM].opt_submenu_string[0].submenu_string));
        air1_msg = reinterpret_cast<AIR1_t*>(_update_data->get_data_from_msg(HMIHANDLER_AIR1_ID));
        float _can_value_uint8 = (uint8_t)(air1_msg->service_brake_airpressure_circuit2);
        if ((((_can_value_uint8 * AIR1_SERVICEBRAKEAIRPRESSURECIRCUIT1FACTOR) / AIR1_VALUE_CONVERTOR) >= MIN_PNEUMATICSYSTEM_PRESSURE) && (((_can_value_uint8 * AIR1_SERVICEBRAKEAIRPRESSURECIRCUIT1FACTOR) / AIR1_VALUE_CONVERTOR) <= MAX_PNEUMATICSYSTEM_PRESSURE)) {
//            *rear_axle_breaking_circuit = to_string((_can_value_uint8 * AIR1_SERVICEBRAKEAIRPRESSURECIRCUIT1FACTOR) / AIR1_VALUE_CONVERTOR);
            std::ostringstream oss;
            float f_value = (_can_value_uint8 * AIR1_SERVICEBRAKEAIRPRESSURECIRCUIT1FACTOR) / AIR1_VALUE_CONVERTOR;
            oss << std::fixed << std::setprecision(1) << f_value << " ";
            *rear_axle_breaking_circuit = oss.str();
            intermediate_value = *rear_axle_breaking_circuit;
        } else {
            *rear_axle_breaking_circuit = INVALID_SIGNAL;
        }

        string* front_axle_breaking_circuit = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[PNEUMATIC_SYSTEM].opt_submenu_string[1].submenu_string));
        _can_value_uint8 = (uint8_t)(air1_msg->service_brake_airpressure_circuit1);
        if ((((_can_value_uint8 * AIR1_SERVICEBRAKEAIRPRESSURECIRCUIT2FACTOR) / AIR1_VALUE_CONVERTOR) >= MIN_PNEUMATICSYSTEM_PRESSURE) && (((_can_value_uint8 * AIR1_SERVICEBRAKEAIRPRESSURECIRCUIT2FACTOR) / AIR1_VALUE_CONVERTOR) <= MAX_PNEUMATICSYSTEM_PRESSURE)) {
//            *front_axle_breaking_circuit = to_string((_can_value_uint8 * AIR1_SERVICEBRAKEAIRPRESSURECIRCUIT2FACTOR) / AIR1_VALUE_CONVERTOR);
            std::ostringstream oss;
            float f_value = (_can_value_uint8 * AIR1_SERVICEBRAKEAIRPRESSURECIRCUIT2FACTOR) / AIR1_VALUE_CONVERTOR;
            oss << std::fixed << std::setprecision(1) << f_value << " ";
            *front_axle_breaking_circuit = oss.str();
        } else {
            *front_axle_breaking_circuit = INVALID_SIGNAL;
        }

        string* parking_brake = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[PNEUMATIC_SYSTEM].opt_submenu_string[2].submenu_string));
        _can_value_uint8 = (uint8_t)(air1_msg->parking_airpressure);
        if ((((_can_value_uint8 * AIR1_PARKINGAIRPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR) >= MIN_PNEUMATICSYSTEM_PRESSURE) && (((_can_value_uint8 * AIR1_PARKINGAIRPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR) <= MAX_PNEUMATICSYSTEM_PRESSURE)) {
//            *parking_brake = to_string(((_can_value_uint8 * AIR1_PARKINGAIRPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR));
            std::ostringstream oss;
            float f_value = (_can_value_uint8 * AIR1_PARKINGAIRPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR;
            oss << std::fixed << std::setprecision(1) << f_value << " ";
            *parking_brake = oss.str();
        } else {
            *parking_brake = INVALID_SIGNAL;
        }

        string* auxiliary_equipement = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[PNEUMATIC_SYSTEM].opt_submenu_string[3].submenu_string));
        _can_value_uint8 = (uint8_t)(air1_msg->auxilary_equipment_supplypressure);
        if ((((_can_value_uint8 * AIR1_AUXILARYEQUIPMENTSUPPLYPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR) >= MIN_PNEUMATICSYSTEM_PRESSURE) && (((_can_value_uint8 * AIR1_AUXILARYEQUIPMENTSUPPLYPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR) <= MAX_PNEUMATICSYSTEM_PRESSURE)) {
//            *auxiliary_equipement = to_string((_can_value_uint8 * AIR1_AUXILARYEQUIPMENTSUPPLYPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR);
            std::ostringstream oss;
            float f_value = (_can_value_uint8 * AIR1_AUXILARYEQUIPMENTSUPPLYPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR;
            oss << std::fixed << std::setprecision(1) << f_value << " ";
            *auxiliary_equipement = oss.str();
        } else {
            *auxiliary_equipement = INVALID_SIGNAL;
        }

        _can_value_uint8 = (uint8_t)(air1_msg->air_suspension_supply_press);
        string* temp_data = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[PNEUMATIC_SYSTEM].opt_submenu_string[4].submenu_string));
        if ((((_can_value_uint8 * AIR1_AUXILARYEQUIPMENTSUPPLYPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR) >= MIN_PNEUMATICSYSTEM_PRESSURE) && (((_can_value_uint8 * AIR1_AUXILARYEQUIPMENTSUPPLYPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR) <= MAX_PNEUMATICSYSTEM_PRESSURE)) {
            //            *auxiliary_equipement = to_string((_can_value_uint8 * AIR1_AUXILARYEQUIPMENTSUPPLYPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR);
            std::ostringstream oss;
            float f_value = (_can_value_uint8 * AIR1_AUXILARYEQUIPMENTSUPPLYPRESSUREFACTOR) / AIR1_VALUE_CONVERTOR;
            oss << std::fixed << std::setprecision(1) << f_value << " ";
            *temp_data = oss.str();
        } else {
            *temp_data = INVALID_SIGNAL;
        }
//        *temp_data = intermediate_value;
    }
    else
    {
        for (auto& it : _menu_data.submenus[E_MT_PARAMETERS].submenu_page[PNEUMATIC_SYSTEM].opt_submenu_string)
        {
            string* temp_data = get_if<string>(&(it.submenu_string));
            *temp_data = INVALID_SIGNAL;
        }
    }
    _menu_data.check_active_list(&_menu_data.submenus[E_MT_PARAMETERS].submenu_page[PNEUMATIC_SYSTEM]);
    CATCH_BLOCK
}

void MenuHandler::update_wipers_data()
{
    TRY_BLOCK
    LS_t* ls_msg = nullptr;
    string* washer_fluid_level = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[WIPERS].opt_submenu_string[0].submenu_string));
    if (_update_data->get_ptr_to_msg(HMIHANDLER_LS_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        ls_msg = reinterpret_cast<LS_t*>(_update_data->get_data_from_msg(HMIHANDLER_LS_ID));
        uint8_t _can_value_uint8 = (uint8_t)(ls_msg->washer_level);
        if ((_can_value_uint8 * LS_WASHER_LEVELFACTOR >= MIN_PERCENTAGE) && ((_can_value_uint8 * LS_WASHER_LEVELFACTOR) <= MAX_PERCENTAGE)) {
            *washer_fluid_level = to_string(_can_value_uint8);

        } else {
            *washer_fluid_level = INVALID_SIGNAL;
        }
    }
    else
    {
        *washer_fluid_level = INVALID_SIGNAL;
    }

    D1_t* d1_msg = nullptr;
    string* no_of_operations = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[WIPERS].opt_submenu_string[1].submenu_string));
    if (_update_data->get_ptr_to_msg(HMIHANDLER_D1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        d1_msg = reinterpret_cast<D1_t*>(_update_data->get_data_from_msg(HMIHANDLER_D1_ID));
        uint16_t _can_value_uint16 = (uint16_t)(d1_msg->wipers_count);
        if (_can_value_uint16 <= MAX_WIPERS_NO_OF_OPERATIONS) {
            *no_of_operations = to_string(_can_value_uint16);
        } else {
            *no_of_operations = INVALID_SIGNAL;
        }
    }
    else
    {
            *no_of_operations = INVALID_SIGNAL;
    }
    _menu_data.check_active_list(&_menu_data.submenus[E_MT_PARAMETERS].submenu_page[WIPERS]);
    CATCH_BLOCK
}

void MenuHandler::update_reagentadblue_data()
{
    TRY_BLOCK
    AT1T1I_t* AT1T1I_msg = nullptr;
    string* ad_blue_level = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[REAGENT_ADBLUE].opt_submenu_string[0].submenu_string));
    string* ad_blue_temperature = get_if<string>(&(_menu_data.submenus[E_MT_PARAMETERS].submenu_page[REAGENT_ADBLUE].opt_submenu_string[1].submenu_string));
    if (_update_data->get_ptr_to_msg(HMIHANDLER_AT1T1I_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        AT1T1I_msg = reinterpret_cast<AT1T1I_t*>(_update_data->get_data_from_msg(HMIHANDLER_AT1T1I_ID));
        uint8_t _can_value_uint8 = (uint8_t)(AT1T1I_msg->aftr_trtmnt1dsl_exhst_fluid_tank_level);

        if ((_can_value_uint8 >= MIN_PERCENTAGE) && (_can_value_uint8 <= UPPER_LIMIT_VALID_SIGNAL_1_BYTE)) {
            _can_value_uint8 *= AT1T1I_AFTRTRTMNT1DSLEXHSTFLIDTANKLEVELFACTOR;
            *ad_blue_level = to_string(_can_value_uint8);
        } else {
            *ad_blue_level = INVALID_SIGNAL;
        }

        int16_t _can_value_int16 = (((int16_t)(AT1T1I_msg->aftr_trtmnt1dsl_exhst_fluid_tank_emp)) + OFFSET_MINUS_40);
        if ((_can_value_int16 >= MIN_TEMPERATURE) && (_can_value_int16 <= MAX_TEMPERATURE)) {
            *ad_blue_temperature = to_string(_can_value_int16);
        } else {
            *ad_blue_temperature = INVALID_SIGNAL;
        }
    }
    else
    {
        *ad_blue_level = INVALID_SIGNAL;
        *ad_blue_temperature = INVALID_SIGNAL;
    }
    _menu_data.check_active_list(&_menu_data.submenus[E_MT_PARAMETERS].submenu_page[REAGENT_ADBLUE]);

    CATCH_BLOCK
}

qreal* MenuHandler::get_daily_fuel_consumption()
{
    TRY_BLOCK
    return &_pavrg_100km;
    CATCH_BLOCK
}

newMenuItems* MenuHandler::init_menu_item_data()
{
    TRY_BLOCK
    return &_menu_data;
    CATCH_BLOCK
}

newMenuItems* MenuHandler::get_menu_item_data()
{
    TRY_BLOCK
    return &_menu_data;
    CATCH_BLOCK
}
