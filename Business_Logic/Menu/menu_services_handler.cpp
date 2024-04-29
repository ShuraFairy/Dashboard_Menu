#include "menu_services_handler.h"

using namespace std;

shared_ptr<MenuServicesHandler> MenuServicesHandler::m_ptr_instance(nullptr);
mutex MenuServicesHandler::m_build_mutex;

MenuServicesHandler::MenuServicesHandler(newMenuItems* _services)
    : menu_services_data(_services)
{
    j1939_data_handler = J1939DataHandler::getInstance();
    m_ptr_cached_msgs = HmiHandler::getInstance();
    json_configure_data_services = QtJsonConfigureData::get_instance();
    init_door_management();
    init_wipers();
    init_diagnostic_trouble_code();
    init_additional_functionality();
    init_steering_angle_sensor();
    init_data_source();
    init_change_passowrd();
    init_software_version();
    init_subscribe();
}

MenuServicesHandler* MenuServicesHandler::get_instance(newMenuItems* _services)
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = shared_ptr<MenuServicesHandler>(new MenuServicesHandler{_services});
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

void MenuServicesHandler::update_services_data()
{
    TRY_BLOCK
    update_diagnostic_trouble_code();
    //update_additional_functionality();
    update_steering_angle_sensor();
    update_software_version();
    CATCH_BLOCK
}

void MenuServicesHandler::init_door_management()
{
    TRY_BLOCK
    //TODO: 1 struct returned value from JSON
    string _receive_config_value;

    if (menu_services_data->submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].item_name == "")
        menu_services_data->submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].item_name = DOOR_MANAGEMENT;

    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string.reserve(6);

    string _send_key = AUTOMATIC_OPENING_CONFIG;
    _receive_config_value = get_config_file_data(_send_key);
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = "pics/Menu/Automatic opening.png", .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{_receive_config_value == STATUS_ON}}));

    _send_key = AUTOMATIC_DOOR_CLOSING_BY_SENSORS_CONFIG;
    _receive_config_value = get_config_file_data(_send_key);
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = "pics/Menu/Automatic door closing by sensors.png", .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{_receive_config_value == STATUS_ON}}));

    _send_key = AUTOMATIC_DOOR_CLOSING_WHEN_LEAVING_BUS_CONFIG;
    _receive_config_value = get_config_file_data(_send_key);
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = "pics/Menu/Automatic door closing by sensors.png", .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{_receive_config_value == STATUS_ON}}));

    _send_key = AUTOMATIC_KNEELING_CONFIG;
    _receive_config_value = get_config_file_data(_send_key);
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = "pics/Menu/Automatic Kneeling.png", .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{_receive_config_value == STATUS_ON}}));

    _send_key = AUTOMATIC_ON_OF_ALARM_SYSTEM_CONFIG;
    _receive_config_value = get_config_file_data(_send_key);
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = "pics/Menu/Automatic on the alarm system.png", .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{_receive_config_value == STATUS_ON}}));

    _send_key = DOORWAY_PASSENGER_SENSOR_CONFIG;
    _receive_config_value = get_config_file_data(_send_key);
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = "pics/Menu/Doorway passenger sensor.png", .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{_receive_config_value == STATUS_ON}}));

    CATCH_BLOCK
}

void MenuServicesHandler::init_wipers()
{
    TRY_BLOCK
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[WIPERS].item_name = WIPERS;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[WIPERS].opt_submenu_string.reserve(2);
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[WIPERS].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{false}}));
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[WIPERS].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{false}}));
    CATCH_BLOCK
}

void MenuServicesHandler::init_diagnostic_trouble_code()
{
    TRY_BLOCK
    uint8_t i;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].item_name = DIAGNOSTICS_TROUBLE_CODE;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string.reserve(6);

    DtcModule temp;
    temp.group_name_status = false;

    DtcGroupErrorCode temp_struct = {.trouble_code_status = false, .trouble_code_spn = 0, .trouble_code_fmi = 0,
                        .trouble_code_recommendations = DTC_RECOMMENDATIONS, .trouble_code_repetations = 0};
    temp.trouble_code.reserve(MAX_DIAGNOSTIC_TROUBLE_CODE + 1);

    for (i = 0; i < MAX_DIAGNOSTIC_TROUBLE_CODE; i++)
        temp.trouble_code.emplace_back(temp_struct);

    temp.group_name = PROPULSION_SYSTEM;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string.emplace_back(
        menu_string({ .param_name = PROPULSION_SYSTEM, .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DTC_CODE, .visibility = true,
                     .submenu_string = temp}));

    temp.group_name = TRANSMISSION;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string.emplace_back(
        menu_string({ .param_name = TRANSMISSION, .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DTC_CODE, .visibility = true,
                     .submenu_string = temp}));
    temp.group_name = BRAKE_SYSTEM;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string.emplace_back(
        menu_string({ .param_name = BRAKE_SYSTEM, .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DTC_CODE, .visibility = true,
                     .submenu_string = temp}));
    temp.group_name = PNEUMATIC_SYSTEM;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string.emplace_back(
        menu_string({ .param_name = PNEUMATIC_SYSTEM, .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DTC_CODE, .visibility = true,
                     .submenu_string = temp}));
    temp.group_name = TACHOGRAPH;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string.emplace_back(
        menu_string({ .param_name = TACHOGRAPH, .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DTC_CODE, .visibility = true,
                     .submenu_string = temp}));
    temp.group_name = TYRE_PRESSURE_MONITORING_SYSTEM;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string.emplace_back(
        menu_string({ .param_name = TYRE_PRESSURE_MONITORING_SYSTEM, .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DTC_CODE, .visibility = true,
                     .submenu_string = temp}));

//    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].submenu_string.emplace_back(uint8_t(0));
    CATCH_BLOCK
}

void MenuServicesHandler::init_additional_functionality()
{
    TRY_BLOCK
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[ADDITIONAL_FUNCTIONALITY].item_name = ADDITIONAL_FUNCTIONALITY;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[ADDITIONAL_FUNCTIONALITY].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{false}}));

    string _receive_config_value = get_config_file_data("turbo_timer");
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[ADDITIONAL_FUNCTIONALITY].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{_receive_config_value == STATUS_ON}}));
    CATCH_BLOCK
}

void MenuServicesHandler::init_steering_angle_sensor()
{
    TRY_BLOCK
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[STEERING_ANGLE_SENSOR].item_name = STEERING_ANGLE_SENSOR;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[STEERING_ANGLE_SENSOR].submenu_string.reserve(4);
    for (int i = 0; i < 4; i++)
        menu_services_data->submenus[E_MT_SERVICES].submenu_page[STEERING_ANGLE_SENSOR].submenu_string.emplace_back("");
    CATCH_BLOCK
}

void MenuServicesHandler::init_data_source()
{
    TRY_BLOCK
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DATA_SOURCE].item_name = DATA_SOURCE;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[DATA_SOURCE].submenu_string.reserve(6);
    for (int i = 0; i < 6; i++)
        menu_services_data->submenus[E_MT_SERVICES].submenu_page[DATA_SOURCE].submenu_string.emplace_back("");
    CATCH_BLOCK
}

void MenuServicesHandler::init_change_passowrd()
{
    TRY_BLOCK
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[CHANGE_PASSWORD].item_name = CHANGE_PASSWORD;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[CHANGE_PASSWORD].submenu_string.reserve(3);
    for (int i = 0; i < 3; i++)
        menu_services_data->submenus[E_MT_SERVICES].submenu_page[CHANGE_PASSWORD].submenu_string.emplace_back("");
    CATCH_BLOCK
}

void MenuServicesHandler::init_software_version()
{
    TRY_BLOCK
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[SOFTWARE_VERSION].item_name = SOFTWARE_VERSION;
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[SOFTWARE_VERSION].opt_submenu_string.reserve(4);
    menu_services_data->submenus[E_MT_SERVICES].submenu_page[SOFTWARE_VERSION].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_CONSTVALUE, .visibility = true,
                     .submenu_string = string(_software_version_details_ec12)}));
    for (int i = 1; i < 4; i++)
        menu_services_data->submenus[E_MT_SERVICES].submenu_page[SOFTWARE_VERSION].opt_submenu_string.emplace_back(
            menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                    .max_value = nullopt, .mid_value = nullopt,
                    .img_path = nullopt, .value_type = E_PT_CONSTVALUE, .visibility = true,
                    .submenu_string = string("")}));

    CATCH_BLOCK
}

void MenuServicesHandler::init_subscribe()
{
    TRY_BLOCK
    auto ptr_notifer = subscribe_notifer::get_instance();
    ptr_notifer->subscribe(HMIHANDLER_DM1_00_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_03_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_0B_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_2F_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_EE_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_DM1_33_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_SAS_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_EEC1_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_SOFT_ZR_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_SOFT_ZKSH_ID, this);
    ptr_notifer->subscribe(HMIHANDLER_SOFT_PV_ID, this);
    CATCH_BLOCK
}

bool MenuServicesHandler::update_info(uint32_t _id)
{
    TRY_BLOCK
    switch (_id)
    {
    case HMIHANDLER_DM1_00_ID:
    case HMIHANDLER_DM1_03_ID:
    case HMIHANDLER_DM1_0B_ID:
    case HMIHANDLER_DM1_2F_ID:
    case HMIHANDLER_DM1_EE_ID:
    case HMIHANDLER_DM1_33_ID:
        update_diagnostic_trouble_code();
        break;
    case HMIHANDLER_SAS_ID:
    case HMIHANDLER_EEC1_ID:
        update_steering_angle_sensor();
        break;
    case HMIHANDLER_SOFT_ZR_ID:
        update_software_version();
        break;
    case HMIHANDLER_SOFT_ZKSH_ID:
        update_software_version();
        break;
    case HMIHANDLER_SOFT_PV_ID:
        update_software_version();
        break;
    }
    return true;
    CATCH_BLOCK
}

void MenuServicesHandler::update_diagnostic_trouble_code()
{
    TRY_BLOCK
    uint8_t i;
    uint8_t dtc_module_visibility_count = 0;
    can_msg_state_e timeout_status;
    dm_fault_data* dm1_data;
    initialize_trouble_code_dtc_data();

    //Propulsion System
    DtcModule* ptr_module = get_if<DtcModule>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string[0].submenu_string));
    if (j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_00_ID))
    {
        timeout_status = j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_00_ID)->get_state();
        dm1_data = j1939_data_handler->handle_dm1_get(HMIHANDLER_DM1_00_ID);

        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm1_data != NULL)
        {
            for (i = 0; i < MAX_DIAGNOSTIC_TROUBLE_CODE; i++)
            {
                if (dm1_data->dtc_data[i].SPN_no > 0)
                {
                    ptr_module->group_name_status = true;
                    ptr_module->trouble_code[i].trouble_code_status = true;
                    ptr_module->trouble_code[i].trouble_code_source = dm1_data->dtc_data[i].source_message;
                    ptr_module->trouble_code[i].trouble_code_spn = dm1_data->dtc_data[i].SPN_no;
                    ptr_module->trouble_code[i].trouble_code_fmi = dm1_data->dtc_data[i].FMI_no;
                    ptr_module->trouble_code[i].trouble_code_repetations = dm1_data->dtc_data[i].no_of_repetations;

                    if (ptr_module->trouble_code[i].trouble_code_spn > 0)
                        dtc_module_visibility_count++;
                }
            }
        } else if (timeout_status == CAN_MESSAGE_STATE_TIMEOUT)
            ptr_module->group_name_status = false;
    }
    ptr_module->module_error_count = dtc_module_visibility_count;
    dtc_module_visibility_count = 0;

    //Transmission
    ptr_module = get_if<DtcModule>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string[1].submenu_string));
    if (j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_03_ID))
    {
        timeout_status = j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_03_ID)->get_state();
        dm1_data = j1939_data_handler->handle_dm1_get(HMIHANDLER_DM1_03_ID);

        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm1_data != NULL)
        {
            for (i = 0; i < MAX_DIAGNOSTIC_TROUBLE_CODE; i++)
            {
                if (dm1_data->dtc_data[i].SPN_no > 0)
                {
                    ptr_module->group_name_status = true;
                    ptr_module->trouble_code[i].trouble_code_status = true;
                    ptr_module->trouble_code[i].trouble_code_source = dm1_data->dtc_data[i].source_message;
                    ptr_module->trouble_code[i].trouble_code_spn = dm1_data->dtc_data[i].SPN_no;
                    ptr_module->trouble_code[i].trouble_code_fmi = dm1_data->dtc_data[i].FMI_no;
                    ptr_module->trouble_code[i].trouble_code_repetations = dm1_data->dtc_data[i].no_of_repetations;
                    if (ptr_module->trouble_code[i].trouble_code_spn > 0)
                        dtc_module_visibility_count++;
                }
            }
        } else if (timeout_status == CAN_MESSAGE_STATE_TIMEOUT)
            ptr_module->group_name_status = false;
    }
    ptr_module->module_error_count = dtc_module_visibility_count;
    dtc_module_visibility_count = 0;

    //Brake System
    ptr_module = get_if<DtcModule>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string[2].submenu_string));
    if (j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_0B_ID))
    {
    timeout_status = j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_0B_ID)->get_state();
    dm1_data = j1939_data_handler->handle_dm1_get(HMIHANDLER_DM1_0B_ID);
    if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm1_data != NULL)
    {
            for (i = 0; i < MAX_DIAGNOSTIC_TROUBLE_CODE; i++)
            {
                if (dm1_data->dtc_data[i].SPN_no > 0)
                {
                    ptr_module->group_name_status = true;
                    ptr_module->trouble_code[i].trouble_code_status = true;
                    ptr_module->trouble_code[i].trouble_code_source = dm1_data->dtc_data[i].source_message;
                    ptr_module->trouble_code[i].trouble_code_spn = dm1_data->dtc_data[i].SPN_no;
                    ptr_module->trouble_code[i].trouble_code_fmi = dm1_data->dtc_data[i].FMI_no;
                    ptr_module->trouble_code[i].trouble_code_repetations = dm1_data->dtc_data[i].no_of_repetations;
                    if (ptr_module->trouble_code[i].trouble_code_spn > 0)
                        dtc_module_visibility_count++;
                }
            }
        } else if (timeout_status == CAN_MESSAGE_STATE_TIMEOUT)
            ptr_module->group_name_status = false;
    }
    ptr_module->module_error_count = dtc_module_visibility_count;
    dtc_module_visibility_count = 0;

    //Pneumatic System
    ptr_module = get_if<DtcModule>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string[3].submenu_string));
    if (j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_2F_ID))
    {
        timeout_status = j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_2F_ID)->get_state();
        dm1_data = j1939_data_handler->handle_dm1_get(HMIHANDLER_DM1_2F_ID);
        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm1_data != NULL)
        {
            for (i = 0; i < MAX_DIAGNOSTIC_TROUBLE_CODE; i++)
            {
                if (dm1_data->dtc_data[i].SPN_no > 0) {
                    ptr_module->group_name_status = true;
                    ptr_module->trouble_code[i].trouble_code_status = true;
                    ptr_module->trouble_code[i].trouble_code_source = dm1_data->dtc_data[i].source_message;
                    ptr_module->trouble_code[i].trouble_code_spn = dm1_data->dtc_data[i].SPN_no;
                    ptr_module->trouble_code[i].trouble_code_fmi = dm1_data->dtc_data[i].FMI_no;
                    ptr_module->trouble_code[i].trouble_code_repetations = dm1_data->dtc_data[i].no_of_repetations;
                    if (ptr_module->trouble_code[i].trouble_code_spn > 0)
                        dtc_module_visibility_count++;
                }
            }
        } else if (timeout_status == CAN_MESSAGE_STATE_TIMEOUT)
            ptr_module->group_name_status = false;
    }
    ptr_module->module_error_count = dtc_module_visibility_count;
    dtc_module_visibility_count = 0;

    // Tachograph
    ptr_module = get_if<DtcModule>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string[4].submenu_string));
    if (j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_EE_ID))
    {
        timeout_status = j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_EE_ID)->get_state();
        dm1_data = j1939_data_handler->handle_dm1_get(HMIHANDLER_DM1_EE_ID);
        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm1_data != NULL)
        {
            for (i = 0; i < MAX_DIAGNOSTIC_TROUBLE_CODE; i++)
            {
                if (dm1_data->dtc_data[i].SPN_no > 0)
                {
                    ptr_module->group_name_status = true;
                    ptr_module->trouble_code[i].trouble_code_status = true;
                    ptr_module->trouble_code[i].trouble_code_source = dm1_data->dtc_data[i].source_message;
                    ptr_module->trouble_code[i].trouble_code_spn = dm1_data->dtc_data[i].SPN_no;
                    ptr_module->trouble_code[i].trouble_code_fmi = dm1_data->dtc_data[i].FMI_no;
                    ptr_module->trouble_code[i].trouble_code_repetations = dm1_data->dtc_data[i].no_of_repetations;
                    if (ptr_module->trouble_code[i].trouble_code_spn > 0)
                        dtc_module_visibility_count++;
                }
            }
        } else if (timeout_status == CAN_MESSAGE_STATE_TIMEOUT)
            ptr_module->group_name_status = false;
    }
    ptr_module->module_error_count = dtc_module_visibility_count;
    dtc_module_visibility_count = 0;

    //Tire Pressure Monitoring System
    ptr_module = get_if<DtcModule>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string[5].submenu_string));
    if (j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_33_ID))
    {
        timeout_status = j1939_data_handler->get_ptr_to_msg(HMIHANDLER_DM1_33_ID)->get_state();
        dm1_data = j1939_data_handler->handle_dm1_get(HMIHANDLER_DM1_33_ID);
        if (timeout_status != CAN_MESSAGE_STATE_TIMEOUT && dm1_data != NULL) {
            for (i = 0; i < MAX_DIAGNOSTIC_TROUBLE_CODE; i++)
            {
                if (dm1_data->dtc_data[i].SPN_no > 0)
                {
                    ptr_module->group_name_status = true;
                    ptr_module->trouble_code[i].trouble_code_status = true;
                    ptr_module->trouble_code[i].trouble_code_source = dm1_data->dtc_data[i].source_message;
                    ptr_module->trouble_code[i].trouble_code_spn = dm1_data->dtc_data[i].SPN_no;
                    ptr_module->trouble_code[i].trouble_code_fmi = dm1_data->dtc_data[i].FMI_no;
                    ptr_module->trouble_code[i].trouble_code_repetations = dm1_data->dtc_data[i].no_of_repetations;
                    if (ptr_module->trouble_code[i].trouble_code_spn > 0)
                        dtc_module_visibility_count++;
                }
            }
        } else if (timeout_status == CAN_MESSAGE_STATE_TIMEOUT)
            ptr_module->group_name_status = false;
    }
    ptr_module->module_error_count = dtc_module_visibility_count;
    CATCH_BLOCK
}

//void MenuServicesHandler::update_additional_functionality()
//{   //TRY_BLOCK
    //    HmiHandler::DD_Settings_t* additional_functionality_data = NULL;

    //    additional_functionality_data = _update_data->handle_ddsettings_msg_get();
    //    menu_services_data->services.additional_functionality.motion_deblocked = (additional_functionality_data->removing_traffic_blocks == VALID_VALUE) ? STATUS_ON : STATUS_OFF;
   //CATCH_BLOCK
//}

void MenuServicesHandler::update_steering_angle_sensor()
{
    TRY_BLOCK
    qreal _temp_speed = MIN_ENGINESPEED_ANGLE;
    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_SAS_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        SAS_t* steering_angle_sensor_data = reinterpret_cast<SAS_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_SAS_ID));
        int32_t n_degree;

        auto temp  = steering_angle_sensor_data->steering_wheel_angle * STEERING_ANGLE_FACTOR + SAS_CANID_STEERING_WHEEL_ANGLE_OFFSET;
        n_degree = (PI / 180) * temp;

        string* ptr_data = get_if<string>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[STEERING_ANGLE_SENSOR].submenu_string[0]));
        *ptr_data = to_string(n_degree) + UOM_DEGREE_CELCIUS;
        ptr_data = get_if<string>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[STEERING_ANGLE_SENSOR].submenu_string[1]));
        *ptr_data = to_string(steering_angle_sensor_data->steering_wheel_angle) + RAD;
    }
    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_EEC1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        EEC1_t* msg_eec1 = reinterpret_cast<EEC1_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_EEC1_ID));
        _temp_speed = round(msg_eec1->eng_speed * ENGINESPEED_FACTOR);
    }
    string* ptr_data = get_if<string>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[STEERING_ANGLE_SENSOR].submenu_string[3]));
    *ptr_data = to_string(_temp_speed);
    CATCH_BLOCK
}

void MenuServicesHandler::initialize_trouble_code_dtc_data()
{
    TRY_BLOCK
    for (auto& it : menu_services_data->submenus[E_MT_SERVICES].submenu_page[DIAGNOSTICS_TROUBLE_CODE].opt_submenu_string)
    {
        DtcModule* dtc_module = get_if<DtcModule>(&it.submenu_string);
        if (dtc_module)
        {
            dtc_module->group_name_status = false;
            dtc_module->module_error_count = 0;
            for (auto& trouble_code : dtc_module->trouble_code)
            {
                trouble_code.trouble_code_status = false;
                trouble_code.trouble_code_repetations = 0;
                trouble_code.trouble_code_spn = 0;
                trouble_code.trouble_code_fmi = 0;
            }
        }
    }
    CATCH_BLOCK
}

string MenuServicesHandler::get_config_file_data(string key_data)
{
    TRY_BLOCK
    QString text = "NULL";
    string return_value;
    text = json_configure_data_services->get_config_data(QString::fromStdString(key_data));
    if ((text == "NULL") || (text == "")) {
        text = "0";
    }
    return_value = text.toStdString();
    return return_value;
    CATCH_BLOCK
}

void MenuServicesHandler::update_software_version()
{
    TRY_BLOCK
    SOFT_PV_t* software_version_data = nullptr;
    string _software_version_details;
    string client_id;
    string project_id;
    string hardware_id;
    string function_id;
    string platform_id;
    string version_id;
    string* ptr_version = nullptr;

    software_version_data = reinterpret_cast<SOFT_ZR_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_SOFT_ZR_ID));
    if (software_version_data)
    {
        client_id = calculate_prefix_zeroes(software_version_data->customer_id, 2);
        project_id = calculate_prefix_zeroes(software_version_data->project_id, 3);
        hardware_id = calculate_prefix_zeroes(software_version_data->hardware_id, 2);
        platform_id = calculate_prefix_zeroes(software_version_data->platform_id, 2);
        version_id = calculate_prefix_zeroes(software_version_data->version_id, 5);
        function_id = convert_data_hexadecimal(software_version_data->function_id);
        _software_version_details = SOFTWARE_VERSION_INIT
            + client_id
            + DOT_SEPERATOR + project_id
            + DOT_SEPERATOR + hardware_id
            + DOT_SEPERATOR + function_id
            + DOT_SEPERATOR + platform_id
            + DASH_SEPERATOR + version_id;
        ptr_version = get_if<string>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[SOFTWARE_VERSION].opt_submenu_string[1].submenu_string));
        *ptr_version = _software_version_details;
    }
    _software_version_details.clear();

    software_version_data = nullptr;
    software_version_data = reinterpret_cast<SOFT_ZKSH_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_SOFT_ZKSH_ID));
    if (software_version_data)
    {
        client_id = calculate_prefix_zeroes(software_version_data->customer_id, 2);
        project_id = calculate_prefix_zeroes(software_version_data->project_id, 3);
        hardware_id = calculate_prefix_zeroes(software_version_data->hardware_id, 2);
        platform_id = calculate_prefix_zeroes(software_version_data->platform_id, 2);
        version_id = calculate_prefix_zeroes(software_version_data->version_id, 5);
        function_id = convert_data_hexadecimal(software_version_data->function_id);
        _software_version_details = SOFTWARE_VERSION_INIT
            + client_id
            + DOT_SEPERATOR + project_id
            + DOT_SEPERATOR + hardware_id
            + DOT_SEPERATOR + function_id
            + DOT_SEPERATOR + platform_id
            + DASH_SEPERATOR + version_id;
        ptr_version = get_if<string>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[SOFTWARE_VERSION].opt_submenu_string[2].submenu_string));
        *ptr_version = _software_version_details;
    }
    _software_version_details.clear();

    software_version_data = nullptr;
    software_version_data = reinterpret_cast<SOFT_PV_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_SOFT_PV_ID));
    if (software_version_data)
    {
        client_id = calculate_prefix_zeroes(software_version_data->customer_id, 2);
        project_id = calculate_prefix_zeroes(software_version_data->project_id, 3);
        hardware_id = calculate_prefix_zeroes(software_version_data->hardware_id, 2);
        platform_id = calculate_prefix_zeroes(software_version_data->platform_id, 2);
        version_id = calculate_prefix_zeroes(software_version_data->version_id, 5);
        function_id = convert_data_hexadecimal(software_version_data->function_id);
        _software_version_details = SOFTWARE_VERSION_INIT
            + client_id
            + DOT_SEPERATOR + project_id
            + DOT_SEPERATOR + hardware_id
            + DOT_SEPERATOR + function_id
            + DOT_SEPERATOR + platform_id
            + DASH_SEPERATOR + version_id;
        ptr_version = get_if<string>(&(menu_services_data->submenus[E_MT_SERVICES].submenu_page[SOFTWARE_VERSION].opt_submenu_string[3].submenu_string));
        *ptr_version = _software_version_details;
    }
    CATCH_BLOCK
}

string MenuServicesHandler::calculate_prefix_zeroes(uint16_t software_id, uint8_t length)
{
    TRY_BLOCK
    string return_str;
    char buffer[length + 1]; // length digits + null terminator
    memset(buffer, 0, length);
    snprintf(buffer, sizeof(buffer), "%0*u", length, software_id);
    return_str = std::string(buffer);
    return return_str;
    CATCH_BLOCK
}

string MenuServicesHandler::convert_data_hexadecimal(uint8_t function_id)
{
    TRY_BLOCK
    string return_functionid;
    std::stringstream hex_stream;
    hex_stream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(function_id);
    return_functionid = hex_stream.str();
    // Ensure there are two characters in the string (pad with zero if needed)
    if (return_functionid.length() == 1) {
        return_functionid = "0" + return_functionid;
    }
    // Use std::transform to convert the entire string to uppercase
    std::transform(return_functionid.begin(), return_functionid.end(), return_functionid.begin(),
        [](unsigned char c) { return std::toupper(c); });

    return return_functionid;
    CATCH_BLOCK
}
