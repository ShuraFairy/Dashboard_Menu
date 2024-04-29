#include "menu_diagnostics_handler.h"
//#define LIGHTING_EQUIPEMENTS "Lighting Equipments"

mutex MenuDiagnosticsHandler::m_build_mutex;
shared_ptr<MenuDiagnosticsHandler> MenuDiagnosticsHandler::m_ptr_instance(nullptr);
static vector<string> g_error_codes;

void init_error_codes_array()
{
    TRY_BLOCK
    g_error_codes.reserve(FAILURE_ERROR_CODE_TOTAL);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_1002);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_1003);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_1004);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_1005);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_1006);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_1007);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_1008);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_1009);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_1010);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_1011);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_3001);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_3002);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_3003);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_4001);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_4002);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_4003);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_5001);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_5002);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_5003);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_6001);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_6002);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_6003);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_7001);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_7003);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_10001);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_10002);
    g_error_codes.emplace_back(FAILURE_ERROR_CODE_13001);
    CATCH_BLOCK
}

MenuDiagnosticsHandler::MenuDiagnosticsHandler(newMenuItems* _diagnostic)
    : map_repetation_count()
    , menu_diagnostic_data(_diagnostic)
{
    j1939_data = J1939DataHandler::getInstance();
    m_ptr_cached_msg = HmiHandler::getInstance();
    // QMutexLocker locker(&MenuItemsMutexUtility::shared_mutex);
    init_diagnostics_emergency_cranes();
    init_diagnostic_door_valves();
    init_diagnostic_door_sensors();
    init_diagnostic_emergency_hammers();
    init_diagnostic_fire_extinguishers();
    init_diagnostic_heaters();
    init_diagnostic_heating_system_valves();
    init_diagnostic_lighting_equipments();
    init_diagnostic_failures_error_code();
    initialize_map_repetation_error_count();
    init_subscribe();
}

MenuDiagnosticsHandler* MenuDiagnosticsHandler::get_instance(newMenuItems* _diagnostic)
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = shared_ptr<MenuDiagnosticsHandler>(new MenuDiagnosticsHandler{_diagnostic});
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::update_diagnostics_data()
{
    TRY_BLOCK
    // QMutexLocker locker(&MenuItemsMutexUtility::shared_mutex);
    update_diagnostics_emergency_cranes();
    update_diagnostic_door_valves();
    update_diagnostic_door_sensors();
    update_diagnostic_emergency_hammers();
    update_diagnostic_fire_extinguishers();
    update_diagnostic_heaters();
    update_diagnostic_heating_system_valves();
    update_diagnostic_failures();
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::init_diagnostics_emergency_cranes()
{
    TRY_BLOCK
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[EMERGENCY_CRANES].item_name = EMERGENCY_CRANES;
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[EMERGENCY_CRANES].opt_submenu_string.reserve(EMERGENCE_CRANE_COUNT);
    for (auto i = 0; i < EMERGENCE_CRANE_COUNT; i++)
    {
        string emergence_crane_name = "EMERGENCY_CRANE_";
        emergence_crane_name.append(std::to_string(i + 1));
        menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[EMERGENCY_CRANES].opt_submenu_string.emplace_back(
            menu_string{.param_name = QString::fromStdString(emergence_crane_name), .img_path = COLOR_WHITE, .value_type = E_PT_CRANE, .visibility = true});
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::init_diagnostic_door_valves()
{
    TRY_BLOCK
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[DOOR_VALVES].item_name = DOOR_VALVES;
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[DOOR_VALVES].opt_submenu_string.reserve(DOOR_VALVES_COUNT);
    for (auto i = 0; i < DOOR_VALVES_COUNT; i++)
    {
        string door_valves_name = "DOOR_VALVE_";
        door_valves_name.append(std::to_string(i + 1));
        menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[DOOR_VALVES].opt_submenu_string.emplace_back(
            menu_string{.param_name = QString::fromStdString(door_valves_name), .img_path = COLOR_WHITE, .value_type = E_PT_VALVE, .visibility = true});
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::init_diagnostic_door_sensors()
{
    TRY_BLOCK
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[DOOR_SENSORS].item_name = DOOR_SENSORS;
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[DOOR_SENSORS].opt_submenu_string.reserve(DOOR_SENSOR_COUNT);
    for (auto i = 0; i < DOOR_SENSOR_COUNT; i++)
    {
        string door_sensor_name = "DOOR_SENSOR_";
        door_sensor_name.append(std::to_string(i + 1));
        menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[DOOR_SENSORS].opt_submenu_string.emplace_back(
            menu_string{.param_name = QString::fromStdString(door_sensor_name), .img_path = COLOR_WHITE, .value_type = E_PT_SENSOR, .visibility = true});
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::init_diagnostic_emergency_hammers()
{
    TRY_BLOCK
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[EMERGENCY_HAMMERS].item_name = EMERGENCY_HAMMERS;
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[EMERGENCY_HAMMERS].opt_submenu_string.reserve(EMERGENCE_HAMMERS_COUNT);
    for (auto i = 0; i < EMERGENCE_HAMMERS_COUNT; i++)
    {
        string emergency_hammer_name = "EMERGENCY_HAMMER_";
        emergency_hammer_name.append(std::to_string(i + 1));
        menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[EMERGENCY_HAMMERS].opt_submenu_string.emplace_back(
            menu_string{.param_name = QString::fromStdString(emergency_hammer_name), .img_path = COLOR_WHITE, .value_type = E_PT_HAMMER, .visibility = true});
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::init_diagnostic_fire_extinguishers()
{
    TRY_BLOCK
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FIRE_EXTINGUISHERS].item_name = FIRE_EXTINGUISHERS;
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FIRE_EXTINGUISHERS].opt_submenu_string.reserve(FIRE_EXTINGUISHER_COUNT);
    for (auto i = 0; i < FIRE_EXTINGUISHER_COUNT; i++)
    {
        string fire_extinguisher_name = "FIRE_EXTINGUISHER_";
        fire_extinguisher_name.append(std::to_string(i + 1));
        menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FIRE_EXTINGUISHERS].opt_submenu_string.emplace_back(
            menu_string{.param_name = QString::fromStdString(fire_extinguisher_name), .img_path = COLOR_WHITE, .value_type = E_PT_FIRE, .visibility = true});
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::init_diagnostic_heaters()
{
    TRY_BLOCK
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[HEATERS].item_name = HEATERS;
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[HEATERS].opt_submenu_string.reserve(HEATERS_COUNT);
    for (auto i = 0; i < HEATERS_COUNT; i++)
    {
        string heater_name = "HEATER_";
        heater_name.append(std::to_string(i + 1));
        menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[HEATERS].opt_submenu_string.emplace_back(
            menu_string{.param_name = QString::fromStdString(heater_name), .img_path = COLOR_WHITE, .value_type = E_PT_HEATER, .visibility = true});
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::init_diagnostic_heating_system_valves()
{
    TRY_BLOCK
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[HEATING_SYSTEM_VALVES].item_name = HEATING_SYSTEM_VALVES;
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[HEATING_SYSTEM_VALVES].opt_submenu_string.reserve(HEATING_SYSTEM_VALVES_COUNT);
    for (auto i = 0; i < HEATING_SYSTEM_VALVES_COUNT; i++)
    {
        string heating_system_valves_name = "HEATING_SYSTEM_VALVE_";
        heating_system_valves_name.append(std::to_string(i + 1));
        menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[HEATING_SYSTEM_VALVES].opt_submenu_string.emplace_back(
            menu_string{.param_name = QString::fromStdString(heating_system_valves_name), .img_path = COLOR_WHITE, .value_type = E_PT_SYSTEM_HEATER, .visibility = true});
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::init_diagnostic_lighting_equipments()
{
    TRY_BLOCK
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[LIGHTING_EQUIPEMENTS].item_name = LIGHTING_EQUIPEMENTS;
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[LIGHTING_EQUIPEMENTS].opt_submenu_string.reserve(10);
    for (int i = 0; i < 10; i++)
        menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[LIGHTING_EQUIPEMENTS].opt_submenu_string.emplace_back(
            menu_string{.param_name = "", .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true, .submenu_string = bool(false)});
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::init_diagnostic_failures_error_code()
{
    TRY_BLOCK
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].item_name = FAILURES;
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string.reserve(8);
    FailureModule temp;
    menu_string _temp_string;
    temp.group_name = "Fire Extinguisher System";
    temp.group_name_status = false;
    temp.error_code.reserve(10);
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "1002", .error_code_status = false, .error_code_description = "FIRE DETECTOR IN E-PANEL DISABLED", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "1003", .error_code_status = false, .error_code_description = "NO COMMMUNICATION WITH FIRE DETECTOR IN E-PANEL ", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "1004", .error_code_status = false, .error_code_description = "FIRE DETECTOR SHORT CIRCUIT IN E-PANEL", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{ .error_code = "1005", .error_code_status = false, .error_code_description = "THE FIRE DETECTOR IN THE MOTOR COMPARTMENT IS DISABLED", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "1006", .error_code_status = false, .error_code_description = "NO COMMUNICATION WITH THE FIRE DETECTOR IN THE MOTOR COMPARTMENT", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "1007", .error_code_status = false, .error_code_description = "SHORT CIRCUIT OF THE FIRE DETECTOR IN THE MOTOR COMPARTMENT", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "1008", .error_code_status = false, .error_code_description = "THE FIRE EXTINGUISHER IN THE E-PANEL IS OFF", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "1009", .error_code_status = false, .error_code_description = "THERE IS NO COMMUNICATION WITH THE FIRE EXTINGUISHER IN THE E-PANEL", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "1010", .error_code_status = false, .error_code_description = "FIRE EXTINGUISHER IN MOTOR COMPARTMENT IS OFF", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "1011", .error_code_status = false, .error_code_description = "NO COMMUNICATION WITH THE FIRE EXTINGUISHER IN THE MOTOR COMPARTMENT", .error_repetation = "0"});
    _temp_string.visibility = true;
    _temp_string.value_type = E_PT_GROUP;
    _temp_string.param_name = QString::fromStdString(temp.group_name);
    _temp_string.submenu_string = FailureModule(temp);
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string.emplace_back(_temp_string);
    temp.error_code.clear();
    //Brake System
    temp.group_name = "Brake System";
    temp.group_name_status = false;
    temp.error_code.reserve(3);
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "3001", .error_code_status = false, .error_code_description = "NO COMMUNICATION WITH THE BREAK ECU", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "3002", .error_code_status = false, .error_code_description = "THERE ARE ACTIVE BRAKE SYSTEM ERRORS", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "3003", .error_code_status = false, .error_code_description = "BRAKE SYSYEM MALFUNCTION", .error_repetation = "0"});
    _temp_string.visibility = true;
    _temp_string.value_type = E_PT_GROUP;
    _temp_string.param_name = QString::fromStdString(temp.group_name);
    _temp_string.submenu_string = FailureModule(temp);
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string.emplace_back(_temp_string);
    temp.error_code.clear();

    //Pneumatic System
    temp.group_name = "Pneumatic System";
    temp.group_name_status = false;
    temp.error_code.reserve(3);
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "4001", .error_code_status = false, .error_code_description = "THERE IS NO COMMUNICATION WITH THE PNEUMATIC SYSTEM ECU", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "4002", .error_code_status = false, .error_code_description = "THERE ARE ACTIVE ERRORS IN THE PNEUMATIC SYSTEM", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "4003", .error_code_status = false, .error_code_description = "AIR SUSPENSION FAILURE", .error_repetation = "0"});
    _temp_string.visibility = true;
    _temp_string.value_type = E_PT_GROUP;
    _temp_string.param_name = QString::fromStdString(temp.group_name);
    _temp_string.submenu_string = FailureModule(temp);
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string.emplace_back(_temp_string);
    temp.error_code.clear();

    //Propulsion System
    temp.group_name = "Propulsion System";
    temp.group_name_status = false;
    temp.error_code.reserve(3);
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "5001", .error_code_status = false, .error_code_description = "THERE IS NO COMMUNICATION WITH THE ECU OF THE POWER PLANT", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "5002", .error_code_status = false, .error_code_description = "THERE ARE ACTIVE ERRORS ON THE POWER PLANT", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "5003", .error_code_status = false, .error_code_description = "ENGINE PROTECTION COMMAND", .error_repetation = "0"});
    _temp_string.visibility = true;
    _temp_string.value_type = E_PT_GROUP;
    _temp_string.param_name = QString::fromStdString(temp.group_name);
    _temp_string.submenu_string = FailureModule(temp);
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string.emplace_back(_temp_string);
    temp.error_code.clear();

    //Transmission
    temp.group_name = "Transmission";
    temp.group_name_status = false;
    temp.error_code.reserve(3);
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "6001", .error_code_status = false, .error_code_description = "NO COMMUNICATION WITH THE TRANSMISSION ECU", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "6002", .error_code_status = false, .error_code_description = "THERE ARE ACTIVE ERRORS IN THE TRANSMISSION", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "6003", .error_code_status = false, .error_code_description = "AUTOMATIC TRANSMISSION MALFUNCTION", .error_repetation = "0"});
    _temp_string.visibility = true;
    _temp_string.value_type = E_PT_GROUP;
    _temp_string.param_name = QString::fromStdString(temp.group_name);
    _temp_string.submenu_string = FailureModule(temp);
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string.emplace_back(_temp_string);
    temp.error_code.clear();

    //Tachograph
    temp.group_name = "Tachograph";
    temp.group_name_status = false;
    temp.error_code.reserve(3);
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "7001", .error_code_status = false, .error_code_description = "NO CONNECTION TO TACHOGRAPH", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "7003", .error_code_status = false, .error_code_description = "CRITICAL TACHOGRAPH ERROR", .error_repetation = "0"});
    _temp_string.visibility = true;
    _temp_string.value_type = E_PT_GROUP;
    _temp_string.param_name = QString::fromStdString(temp.group_name);
    _temp_string.submenu_string = FailureModule(temp);
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string.emplace_back(_temp_string);
    temp.error_code.clear();

    //Tire Pressure and temperature monitoring system
    temp.group_name = "Tire Pressure and Temperature Monitoring";
    temp.group_name_status = false;
    temp.error_code.reserve(2);
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "10001", .error_code_status = false, .error_code_description = "NO COOMUNICATION WITH TIRE PRESSURE AND TEMPERATURE MONITORING SYSTEM", .error_repetation = "0"});
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "10002", .error_code_status = false, .error_code_description = "THERE ARE ACTIVE ERRORS IN TIRE PRESSURE AND TEMPERATURE MONITORING SYSTEM", .error_repetation = "0"});
    _temp_string.visibility = true;
    _temp_string.value_type = E_PT_GROUP;
    _temp_string.param_name = QString::fromStdString(temp.group_name);
    _temp_string.submenu_string = FailureModule(temp);
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string.emplace_back(_temp_string);
    temp.error_code.clear();

    // ADAS Driver Assistance System
    temp.group_name = "ADAS Driver System group";
    temp.group_name_status = false;
    temp.error_code.emplace_back(FailureErrorCode{.error_code = "13001", .error_code_status = false, .error_code_description = "NO COMMUNICATION WITH ADAS DRIVER ASSISTANCE ECU", .error_repetation = "0"});
    _temp_string.visibility = true;
    _temp_string.value_type = E_PT_GROUP;
    _temp_string.param_name = QString::fromStdString(temp.group_name);
    _temp_string.submenu_string = FailureModule(temp);
    menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string.emplace_back(_temp_string);
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::initialize_error_data_failures()
{
    TRY_BLOCK
    for (auto& error_grp : menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string)
    {
        FailureModule* ptr_module = get_if<FailureModule>(&(error_grp.submenu_string));
        if (ptr_module && ptr_module->group_name_status)
        {
            ptr_module->group_name_status = false;
            for (auto& it : ptr_module->error_code)
            {
                it.error_code_status = false;
                it.error_repetation = "0";
            }
        }
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::initialize_map_repetation_error_count()
{
    TRY_BLOCK
    init_error_codes_array();
    for (auto it : g_error_codes)
         map_repetation_count.insert({it, {.error_code = it, .error_status = false, .repetation_count = 0}});
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::init_subscribe()
{
    TRY_BLOCK
    auto ptr_notifer = subscribe_notifer::get_instance();
    ptr_notifer->subscribe(HMIHANDLER_DC1_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DC2_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_FB3_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_RELAY_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_EBC1_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_0B_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_TT_GRP_B_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_TT_GRP_E_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_2F_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_TT_GRP_F_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_00_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_TT_GRP_H_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_03_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_EE_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_33_ID, this);
    CATCH_BLOCK

}

bool MenuDiagnosticsHandler::update_info(uint32_t _id)
{
    TRY_BLOCK
    switch (_id)
    {
    case HMIHANDLER_DC1_ID:
        update_diagnostics_emergency_cranes();
        update_diagnostic_door_valves();
        update_diagnostic_emergency_hammers();
        break;
    case HMIHANDLER_DC2_ID:
        update_diagnostic_door_sensors();
        update_diagnostic_heating_system_valves();
        break;
    case HMIHANDLER_FB3_ID:
        update_diagnostic_fire_extinguishers();
        update_diagnostic_heating_system_valves();
        update_diagnostic_heaters();
        break;
    case HMIHANDLER_RELAY_ID:
    case HMIHANDLER_EBC1_ID:
    case HMIHANDLER_DM1_0B_ID:
    case HMIHANDLER_TT_GRP_B_ID:
    case HMIHANDLER_TT_GRP_E_ID:
    case HMIHANDLER_DM1_2F_ID:
    case HMIHANDLER_TT_GRP_F_ID:
    case HMIHANDLER_DM1_00_ID:
    case HMIHANDLER_TT_GRP_H_ID:
    case HMIHANDLER_DM1_03_ID:
    case HMIHANDLER_DM1_EE_ID:
    case HMIHANDLER_DM1_33_ID:
        update_diagnostic_failures();
        break;
    }
    return true;
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::update_diagnostics_emergency_cranes()
{
    TRY_BLOCK
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_DC1_ID)->get_state() != CAN_MESSAGE_STATE_OK)
        return;

    DC1_t* ptr_msg = reinterpret_cast<DC1_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_DC1_ID));
    uint8_t emergence_crane_count_loop = 0;

    for (auto i = 0; i < EMERGENCE_CRANE_COUNT; i++)
    {
        if (i == 0)
            emergence_crane_count_loop = ptr_msg->doorcrane1_2;
        else if (i == 4)
            emergence_crane_count_loop = ptr_msg->doorcrane3_4;

        uint8_t result = emergence_crane_count_loop & 3;

        auto ptr_crane = &(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[EMERGENCY_CRANES].opt_submenu_string[i]);
        if (result == 0x01)
            ptr_crane->img_path = COLOR_YELLOW;
        else if (result >= 0x02)
            ptr_crane->img_path = COLOR_RED;
        else if (result == 0x00)
            ptr_crane->img_path = COLOR_WHITE;

        emergence_crane_count_loop >>= 2;
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::update_diagnostic_door_valves()
{
    TRY_BLOCK
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_DC1_ID)->get_state() != CAN_MESSAGE_STATE_OK)
        return;

    DC1_t* ptr_msg = reinterpret_cast<DC1_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_DC1_ID));
    uint8_t door_valve_count_loop = 0;

    for (auto i = 0; i < DOOR_VALVES_COUNT; i++)
    {
        if (i == 0)
            door_valve_count_loop = ptr_msg->doorvalvest1_2;
        else if (i == 6)
            door_valve_count_loop = ptr_msg->doorvalvest3_4;

        uint8_t result = door_valve_count_loop & 1;
        auto ptr_valves = &(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[DOOR_VALVES].opt_submenu_string[i]);
        ptr_valves->img_path = (result) ? COLOR_RED : COLOR_WHITE;

        door_valve_count_loop >>= 1;
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::update_diagnostic_door_sensors()
{
    TRY_BLOCK
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_DC2_ID)->get_state() != CAN_MESSAGE_STATE_OK)
        return;

    DC2_t* ptr_msg = reinterpret_cast<DC2_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_DC2_ID));
    uint8_t mask = 1;
    uint8_t result = 0;
    uint8_t door_sensor_state_1_2 = 0;
    uint8_t door_sensor_state_3_4 = 0;
    uint8_t door_sensor_count_loop = 0;

    door_sensor_state_1_2 = ptr_msg->door_sensorst_1_2;
    door_sensor_state_3_4 = ptr_msg->door_sensorst_3_4;

    door_sensor_count_loop = door_sensor_state_1_2;
    //TODO: make nicer
    result = door_sensor_count_loop & mask;
    auto ptr_sensor_data = &(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[DOOR_SENSORS].opt_submenu_string[0]);
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 2) & mask;
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 1) & mask;
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 3) & mask;
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 4) & mask;
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 6) & mask;
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 5) & mask;
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 7) & mask;
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    door_sensor_count_loop = door_sensor_state_3_4;

    result = (door_sensor_count_loop)&mask; //56
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 2) & mask; //58
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 1) & mask; //57
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 3) & mask; //59
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 4) & mask; //60
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 6) & mask; //62
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 5) & mask; //61
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;

    result = (door_sensor_count_loop >> 7) & mask; //63
    ptr_sensor_data++;
    ptr_sensor_data->img_path = (result) ? COLOR_YELLOW : COLOR_WHITE;
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::update_diagnostic_emergency_hammers()
{
    TRY_BLOCK
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_D1_ID)->get_state() != CAN_MESSAGE_STATE_OK)
        return;

    D1_t* ptr_msg = reinterpret_cast<D1_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_D1_ID));
    auto ptr_hammers = &(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[EMERGENCY_HAMMERS].opt_submenu_string[0]);
    ptr_hammers->img_path = (ptr_msg->hammer_1) ? COLOR_RED : COLOR_WHITE;

    ptr_hammers++;
    ptr_hammers->img_path = (ptr_msg->hammer_2) ? COLOR_RED : COLOR_WHITE;
    ptr_hammers++;
    ptr_hammers->img_path = (ptr_msg->hammer_3) ? COLOR_RED : COLOR_WHITE;
    ptr_hammers++;
    ptr_hammers->img_path = (ptr_msg->hammer_4) ? COLOR_RED : COLOR_WHITE;
    ptr_hammers++;
    ptr_hammers->img_path = (ptr_msg->hammer_5) ? COLOR_RED : COLOR_WHITE;
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::update_diagnostic_fire_extinguishers()
{
    TRY_BLOCK
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_FB3_ID)->get_state() != CAN_MESSAGE_STATE_OK)
        return;

    FB3_t* ptr_msg = reinterpret_cast<FB3_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_FB3_ID));
    auto ptr_fire = &(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FIRE_EXTINGUISHERS].opt_submenu_string[0]);
    ptr_fire->img_path = (ptr_msg->fire1) ? COLOR_RED : COLOR_WHITE;
    ptr_fire++;
    ptr_fire->img_path = (ptr_msg->fire2) ? COLOR_RED : COLOR_WHITE;
    ptr_fire++;
    ptr_fire->img_path = (ptr_msg->fire3) ? COLOR_RED : COLOR_WHITE;
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::update_diagnostic_heating_system_valves()
{
    TRY_BLOCK
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_FB3_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        FB3_t* fb3_msg = reinterpret_cast<FB3_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_FB3_ID));
        auto ptr_data = &(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[HEATING_SYSTEM_VALVES].opt_submenu_string[0]);
        ptr_data->img_path = (fb3_msg->heater_valve1) ? COLOR_RED : COLOR_WHITE;
        ptr_data++;
        ptr_data->img_path = (fb3_msg->heater_valve2) ? COLOR_RED : COLOR_WHITE;
        ptr_data++;
        ptr_data->img_path = (fb3_msg->heater_valve3) ? COLOR_RED : COLOR_WHITE;
        ptr_data++;
        ptr_data->img_path = (fb3_msg->heater_valve4) ? COLOR_RED : COLOR_WHITE;
        ptr_data++;
        ptr_data->img_path = (fb3_msg->heater_valve5) ? COLOR_RED : COLOR_WHITE;
        ptr_data++;
        ptr_data->img_path = (fb3_msg->heater_valve6) ? COLOR_RED : COLOR_WHITE;
        ptr_data++;
        ptr_data->img_path = (fb3_msg->heater_valve7) ? COLOR_RED : COLOR_WHITE;
        ptr_data++;
        ptr_data->img_path = (fb3_msg->heater_valve8) ? COLOR_RED : COLOR_WHITE;
    }
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_DC2_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        DC2_t* dc2_msg = reinterpret_cast<DC2_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_DC2_ID));
        auto ptr_data = &(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[HEATING_SYSTEM_VALVES].opt_submenu_string[8]);
        ptr_data->img_path = (dc2_msg->heater_valve_9) ? COLOR_RED : COLOR_WHITE;
    /* Could Not handle Heating system Valve 9, As DC2_31 CAN Message is not available */
    }
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::update_diagnostic_heaters()
{
    TRY_BLOCK
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_FB3_ID)->get_state() != CAN_MESSAGE_STATE_OK)
        return;

    FB3_t* fb3_msg = reinterpret_cast<FB3_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_FB3_ID));
    string colors[]{
        COLOR_GREEN,
        COLOR_YELLOW,
        COLOR_RED
    };
    for (auto& it : menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[HEATERS].opt_submenu_string)
        it.img_path = COLOR_WHITE;

    auto ptr_data = &(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[HEATERS].opt_submenu_string[0]);
    if(fb3_msg->heater_ag)
        ptr_data->img_path = COLOR_GREEN;
    if(fb3_msg->heater_ar)
        ptr_data->img_path = COLOR_RED;
    if(fb3_msg->heater_ay)
        ptr_data->img_path = COLOR_YELLOW;

    ptr_data++;
    if(fb3_msg->heater_bg)
        ptr_data->img_path = COLOR_GREEN;
    if(fb3_msg->heater_br)
        ptr_data->img_path = COLOR_RED;
    if(fb3_msg->heater_by)
        ptr_data->img_path = COLOR_YELLOW;

    ptr_data++;
    if(fb3_msg->heater_cg)
        ptr_data->img_path = COLOR_GREEN;
    if(fb3_msg->heater_cr)
        ptr_data->img_path = COLOR_RED;
    if(fb3_msg->heater_cy)
        ptr_data->img_path = COLOR_YELLOW;

    ptr_data++;
    if(fb3_msg->heater_dg)
        ptr_data->img_path = COLOR_GREEN;
    if(fb3_msg->heater_dr)
        ptr_data->img_path = COLOR_RED;
    if(fb3_msg->heater_dy)
        ptr_data->img_path = COLOR_YELLOW;

    ptr_data++;
    if(fb3_msg->heater_eg)
        ptr_data->img_path = COLOR_GREEN;
    if(fb3_msg->heater_er)
        ptr_data->img_path = COLOR_RED;
    if(fb3_msg->heater_ey)
        ptr_data->img_path = COLOR_YELLOW;

    ptr_data++;
    if(fb3_msg->heater_fg)
        ptr_data->img_path = COLOR_GREEN;
    if(fb3_msg->heater_fr)
        ptr_data->img_path = COLOR_RED;
    if(fb3_msg->heater_fy)
        ptr_data->img_path = COLOR_YELLOW;

    ptr_data++;
    if(fb3_msg->heater_gg)
        ptr_data->img_path = COLOR_GREEN;
    if(fb3_msg->heater_gr)
        ptr_data->img_path = COLOR_RED;
    if(fb3_msg->heater_gy)
        ptr_data->img_path = COLOR_YELLOW;

    ptr_data++;
    if(fb3_msg->heater_hg)
        ptr_data->img_path = COLOR_GREEN;
    if(fb3_msg->heater_hr)
        ptr_data->img_path = COLOR_RED;
    if(fb3_msg->heater_hy)
        ptr_data->img_path = COLOR_YELLOW;

    ptr_data++;
    if(fb3_msg->heater_sg)
        ptr_data->img_path = COLOR_GREEN;
    if(fb3_msg->heater_sr)
        ptr_data->img_path = COLOR_RED;
    if(fb3_msg->heater_sy)
        ptr_data->img_path = COLOR_YELLOW;
CATCH_BLOCK
}

void MenuDiagnosticsHandler::update_diagnostic_failures()
{
    TRY_BLOCK
    uint8_t mask = 3;
    uint8_t result;
    uint8_t failure_module_visibility_count = 0;

    FailureErrorCode* failure_error_code;
    FailureModule* failure_module;


    initialize_error_data_failures();

    failure_module = get_if<FailureModule>(&(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string[0].submenu_string));
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_RELAY_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        Relay_t* ptr_msg = reinterpret_cast<Relay_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_RELAY_ID));
        uint8_t fire_extinguisher_1002_1003_1004 = ptr_msg->asotpin1;
        uint8_t fire_extinguisher_1005_1006_1007 = ptr_msg->asotpin2;
        uint8_t fire_extinguisher_1008_1009 = ptr_msg->asotpout1;
        uint8_t fire_extinguisher_1010_1011 = ptr_msg->asotpout2;

        failure_error_code = &failure_module->error_code[0];
        result = fire_extinguisher_1002_1003_1004 & mask;
        if (result != 2)
        {
            failure_module->group_name_status = true;
            if (result == 0)
            {
                failure_module_visibility_count++;
                update_map_repetation_error_count(true, FAILURE_ERROR_CODE_1002);
                failure_error_code[0].error_code_status = true;
                failure_error_code[0].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_1002));
            }
            else if (result == 1)
            {
                failure_module_visibility_count++;
                update_map_repetation_error_count(true, FAILURE_ERROR_CODE_1003);
                failure_error_code[1].error_code_status = true;
                failure_error_code[1].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_1003));
            }
            else if (result == 3)
            {
                failure_module_visibility_count++;
                update_map_repetation_error_count(true, FAILURE_ERROR_CODE_1004);
                failure_error_code[2].error_code_status = true;
                failure_error_code[2].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_1004));
            }

        }
        result = fire_extinguisher_1005_1006_1007 & mask;
        if (result != 2)
        {
            failure_module->group_name_status = true;
            if (result == 0)
            {
                failure_module_visibility_count++;
                update_map_repetation_error_count(true, FAILURE_ERROR_CODE_1005);
                failure_error_code[3].error_code_status = true;
                failure_error_code[3].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_1005));
            }
            else if (result == 1)
            {
                failure_module_visibility_count++;
                update_map_repetation_error_count(true, FAILURE_ERROR_CODE_1006);
                failure_error_code[4].error_code_status = true;
                failure_error_code[4].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_1006));
            }
            else if (result == 3)
            {
                failure_module_visibility_count++;
                update_map_repetation_error_count(true, FAILURE_ERROR_CODE_1007);
                failure_error_code[5].error_code_status = true;
                failure_error_code[5].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_1007));
            }
        }
        result = fire_extinguisher_1008_1009 & mask;
        if(result != 2)
        {
            failure_module->group_name_status = true;
            if (result == 0)
            {
                update_map_repetation_error_count(true, FAILURE_ERROR_CODE_1008);
                failure_module_visibility_count++;
                failure_error_code[6].error_code_status = true;
                failure_error_code[6].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_1008));
            }
            else if (result == 1)
            {
                failure_module_visibility_count++;
                update_map_repetation_error_count(true, FAILURE_ERROR_CODE_1009);
                failure_error_code[7].error_code_status = true;
                failure_error_code[7].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_1009));
            }
        }
        result = fire_extinguisher_1010_1011 & mask;
        if (result != 2)
        {
                failure_module->group_name_status = true;
                if (result == 1)
                {
                    update_map_repetation_error_count(true, FAILURE_ERROR_CODE_1010);
                    failure_module_visibility_count++;
                    failure_error_code[8].error_code_status = true;
                    failure_error_code[8].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_1010));
                }
                else if (result == 0)
                {
                    failure_module_visibility_count++;
                    update_map_repetation_error_count(true, FAILURE_ERROR_CODE_1011);
                    failure_error_code[9].error_code_status = true;
                    failure_error_code[9].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_1011));
                }        
        }
    }
    else
    {
        failure_module->group_name_status = false;
        for (auto& it : failure_module->error_code)
            it.error_code_status = false;
    }

    failure_module->module_error_count = failure_module_visibility_count;
    failure_module_visibility_count = 0;

    // Brake System

    failure_module = get_if<FailureModule>(&(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string[1].submenu_string));
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_EBC1_ID)->get_state() == CAN_MESSAGE_STATE_TIMEOUT)
    {
        failure_module->error_code[0].error_code_status = true;
        failure_module->group_name_status = true;
        failure_module_visibility_count++;
        update_map_repetation_error_count(true, FAILURE_ERROR_CODE_3001);
    }
    else
    {
        update_map_repetation_error_count(false, FAILURE_ERROR_CODE_3001);
    }
    failure_module->error_code[0].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_3001));
    dm_fault_data*  dm01_fault_data;
    //TODO: J1939 Subscribe
    if (j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_0B_ID))
    {
        auto timeout_status = j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_0B_ID)->get_state();
        dm01_fault_data = j1939_data->handle_dm1_get(HMIHANDLER_DM1_0B_ID);

        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm01_fault_data->protect_lamp_status == 0x01)
        {
            failure_module->error_code[1].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;

            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_3002);
        }
        else
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_3002);
        }
    }
    failure_module->error_code[1].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_3002));
    uint8_t tt_grp_status;
    uint8_t tt_grp_mask = 3;

    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_TT_GRP_B_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        TT_GRP_B_t* grpb_msg = reinterpret_cast<TT_GRP_B_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_TT_GRP_B_ID));
        tt_grp_status = grpb_msg->B01;
        result = tt_grp_status && tt_grp_mask;
        if (result == 0x01)
        {
            failure_module->error_code[2].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;

            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_3003);
        }
        else if (result == 0x00)
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_3003);
        }
    }
    failure_module->error_code[2].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_3003));

    // Trigerred during Timeout //

    failure_module->module_error_count = failure_module_visibility_count;
    failure_module_visibility_count = 0;

    /* End Brake System */

    /*  Pneumatic System */
    failure_module = get_if<FailureModule>(&(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string[2].submenu_string));
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_TT_GRP_E_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        TT_GRP_E_t* grpe_msg = reinterpret_cast<TT_GRP_E_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_TT_GRP_E_ID));
        tt_grp_status = grpe_msg->E20;
        if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_ASC1_ID)->get_state() == CAN_MESSAGE_STATE_TIMEOUT)
        {
            failure_module->error_code[0].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_4001);
        } else
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_4001);
        }
        result = tt_grp_status && tt_grp_mask;
        if (result == 0x01)
        {
            failure_module->error_code[2].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_4003);
        } else if (result == 0x00)
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_4003);
        }
    }
    failure_module->error_code[0].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_4001));

    if (j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_2F_ID))
    {
        auto timeout_status = j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_2F_ID)->get_state();
        dm01_fault_data = j1939_data->handle_dm1_get(HMIHANDLER_DM1_2F_ID);
        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm01_fault_data->protect_lamp_status == 0x01)
        {
            failure_module->error_code[1].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_4002);
        }
        else
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_4002);
        }
    }
    failure_module->error_code[1].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_4002));
    failure_module->error_code[2].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_4003));

    failure_module->module_error_count = failure_module_visibility_count;
    failure_module_visibility_count = 0;

    /* Propulsion System */
    failure_module = get_if<FailureModule>(&(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string[3].submenu_string));
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_TT_GRP_F_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        TT_GRP_F_t* grpf_msg = reinterpret_cast<TT_GRP_F_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_TT_GRP_F_ID));
        tt_grp_status = grpf_msg->F02;
        if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_EEC1_ID)->get_state() == CAN_MESSAGE_STATE_TIMEOUT)
        {
            failure_module->error_code[0].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_5001);
        }
        else
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_5001);
        }

        result = tt_grp_status && tt_grp_mask;
        if (result == 0x01) {
            failure_module->error_code[2].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_5003);
        }
        else if (result == 0x00)
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_5003);
        }
    }
    failure_module->error_code[0].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_5001));

    if (j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_00_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        auto timeout_status = m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_DM1_00_ID)->get_state();
        dm01_fault_data = j1939_data->handle_dm1_get(HMIHANDLER_DM1_00_ID);
        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm01_fault_data->protect_lamp_status == 0x01)
        {
            failure_module->error_code[1].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_5002);
        }
        else
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_5002);
        }
    }
    failure_module->error_code[1].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_5002));
    failure_module->error_code[2].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_5003));

    failure_module->module_error_count = failure_module_visibility_count;
    failure_module_visibility_count = 0;

    /* Transmission System */
    failure_module = get_if<FailureModule>(&(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string[4].submenu_string));
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_TT_GRP_H_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        TT_GRP_H_t* grph_msg = reinterpret_cast<TT_GRP_H_t*>(m_ptr_cached_msg->get_data_from_msg(HMIHANDLER_TT_GRP_H_ID));
        tt_grp_status = grph_msg->H05;
        auto timeout_status = m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_ETC1_ID)->get_state();
        if (timeout_status == CAN_MESSAGE_STATE_TIMEOUT)
        {
            failure_module->error_code[0].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_6001);
        }
        else
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_6001);
        }

        result = tt_grp_status && tt_grp_mask;
        if (result == 0x01)
        {
            failure_module->error_code[2].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_6003);
        }
        else if (result == 0x00)
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_6003);
        }
    }
    failure_module->error_code[0].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_6001));

    if (j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_03_ID))
    {
        auto timeout_status = j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_03_ID)->get_state();
        dm01_fault_data = j1939_data->handle_dm1_get(HMIHANDLER_DM1_03_ID);
        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm01_fault_data->protect_lamp_status == 0x01)
        {
            failure_module->error_code[1].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_6002);
        }
        else
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_6002);
        }
    }
    failure_module->error_code[1].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_6002));
    failure_module->error_code[2].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_6003));

    failure_module->module_error_count = failure_module_visibility_count;
    failure_module_visibility_count = 0;

    /* Tachograph */
    failure_module = get_if<FailureModule>(&(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string[5].submenu_string));
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_EEC1_ID)->get_state() == CAN_MESSAGE_STATE_TIMEOUT)
    {
        failure_module->error_code[0].error_code_status = true;
        failure_module->group_name_status = true;
        failure_module_visibility_count++;
        update_map_repetation_error_count(true, FAILURE_ERROR_CODE_7001);
    }
    else
    {
        update_map_repetation_error_count(false, FAILURE_ERROR_CODE_7001);
    }
    failure_module->error_code[0].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_7001));

    if (j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_EE_ID))
    {
        auto timeout_status = j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_EE_ID)->get_state();
        dm01_fault_data = j1939_data->handle_dm1_get(HMIHANDLER_DM1_EE_ID);
        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm01_fault_data->protect_lamp_status == 0x01)
        {
            failure_module->error_code[1].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_7003);
        }
        else
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_7003);
        }
    }
    failure_module->error_code[1].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_7003));

    failure_module->module_error_count = failure_module_visibility_count;
    failure_module_visibility_count = 0;

    /* Tire Pressure and Temperature */
    failure_module = get_if<FailureModule>(&(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string[6].submenu_string));
    if (m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_TIRE_CONDITION_ID)->get_state() == CAN_MESSAGE_STATE_TIMEOUT)
    {
        failure_module->error_code[0].error_code_status = true;
        failure_module->group_name_status = true;
        failure_module_visibility_count++;
        update_map_repetation_error_count(true, FAILURE_ERROR_CODE_10001);
    }
    else
    {
        update_map_repetation_error_count(false, FAILURE_ERROR_CODE_10001);
    }
    failure_module->error_code[0].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_10001));

    if (j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_33_ID))
    {
        auto timeout_status = j1939_data->get_ptr_to_msg(HMIHANDLER_DM1_33_ID)->get_state();
        dm01_fault_data = j1939_data->handle_dm1_get(HMIHANDLER_DM1_33_ID);
        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm01_fault_data->protect_lamp_status == 0x01)
        {
            failure_module->error_code[1].error_code_status = true;
            failure_module->group_name_status = true;
            failure_module_visibility_count++;
            update_map_repetation_error_count(true, FAILURE_ERROR_CODE_10002);
        }
        else
        {
            update_map_repetation_error_count(false, FAILURE_ERROR_CODE_10002);
        }
    }
    failure_module->error_code[1].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_10002));

    failure_module->module_error_count = failure_module_visibility_count;
    failure_module_visibility_count = 0;

    /* ADAS Driver Assistance */
    failure_module = get_if<FailureModule>(&(menu_diagnostic_data->submenus[E_MT_DIAGNOSTICS].submenu_page[FAILURES].opt_submenu_string[7].submenu_string));
    auto timeout_status = m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_ADAS_600_ID)->get_state();
    if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT)
        timeout_status = m_ptr_cached_msg->get_ptr_to_msg(HMIHANDLER_VEHICLEDATA_620_ID)->get_state();

    if (timeout_status == CAN_MESSAGE_STATE_TIMEOUT) {
        failure_module->error_code[0].error_code_status = true;
        failure_module->group_name_status = true;
        failure_module_visibility_count++;
        update_map_repetation_error_count(true, FAILURE_ERROR_CODE_13001);
    }
    else
    {
        update_map_repetation_error_count(false, FAILURE_ERROR_CODE_13001);
    }
    failure_module->error_code[0].error_repetation = to_string(get_map_repetation_error_count(FAILURE_ERROR_CODE_13001));

    failure_module->module_error_count = failure_module_visibility_count;

    /*End of ADAS   */
    CATCH_BLOCK
}

void MenuDiagnosticsHandler::update_map_repetation_error_count(bool error_code_status, string key_value)
{
    TRY_BLOCK
    if (map_repetation_count.find(key_value) != map_repetation_count.end())
    {
        if (error_code_status)
            map_repetation_count[key_value].repetation_count++;

        map_repetation_count[key_value].error_status = error_code_status;
    }
    CATCH_BLOCK
}

uint8_t MenuDiagnosticsHandler::get_map_repetation_error_count(string key_value)
{
    TRY_BLOCK
    return map_repetation_count.find(key_value)->second.repetation_count;
    CATCH_BLOCK
}
