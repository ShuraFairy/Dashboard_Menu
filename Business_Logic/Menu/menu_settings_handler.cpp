#include "menu_settings_handler.h"

shared_ptr<MenuSettingsHandler> MenuSettingsHandler::m_ptr_instance(nullptr);
mutex MenuSettingsHandler::m_build_mutex;

MenuSettingsHandler::MenuSettingsHandler(newMenuItems* _settings)
    : menu_settings_data(_settings)
{
    json_configure_data = QtJsonConfigureData::get_instance();
    m_ptr_cached_msgs = HmiHandler::getInstance();
    //    std::lock_guard<std::mutex> lock(menu_items_mutex);
    // QMutexLocker locker(&MenuItemsMutexUtility::shared_mutex);
    init_heating_system();
    init_dashboard();
    init_light_rain_sensor();
    init_climate_control_driver_cab();
    init_subscribe();
}

MenuSettingsHandler* MenuSettingsHandler::get_instance(newMenuItems* _settings)
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = shared_ptr<MenuSettingsHandler>(new MenuSettingsHandler{_settings});
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

void MenuSettingsHandler::update_settings_data()
{
    TRY_BLOCK
    //update_dashboard();
    update_climate_control_driver_cab();
    CATCH_BLOCK
}

bool MenuSettingsHandler::update_info(uint32_t _id)
{
    TRY_BLOCK
    if (_id == HMIHANDLER_DC2_ID)
        update_climate_control_driver_cab();

    return true;
    CATCH_BLOCK
}

void MenuSettingsHandler::init_heating_system()
{
    TRY_BLOCK
    uint8_t install_temperature_config;
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[HEATING_SYSTEM].item_name = HEATING_SYSTEM;
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[HEATING_SYSTEM].opt_submenu_string.reserve(3);
    send_key = "installation_temperature";
    receive_config_value = get_config_file_data(send_key);
    install_temperature_config = stoi(receive_config_value);
    install_temperature_config = (install_temperature_config < MINIMUM_INSTALLATION_TEMPERATURE) ? MINIMUM_INSTALLATION_TEMPERATURE : (install_temperature_config > MAXIMUM_INSTALLATION_TEMPERATURE) ? MAXIMUM_INSTALLATION_TEMPERATURE : install_temperature_config;
    update_config_data(send_key, to_string(install_temperature_config));
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[HEATING_SYSTEM].opt_submenu_string.emplace_back(
        menu_string({.param_name = "", .uom = nullopt, .min_value = MINIMUM_INSTALLATION_TEMPERATURE,
                     .max_value = MAXIMUM_INSTALLATION_TEMPERATURE, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DIAPASONE, .visibility = true,
                     .submenu_string = to_string(install_temperature_config)}));
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[HEATING_SYSTEM].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                      .max_value = nullopt, .mid_value = nullopt,
                      .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{false}}));
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[HEATING_SYSTEM].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                      .max_value = nullopt, .mid_value = nullopt,
                      .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{false}}));
    CATCH_BLOCK
}

void MenuSettingsHandler::init_dashboard()
{
    TRY_BLOCK
    uint8_t brightness_value_config;
    //uint8_t volume_value_config;
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].item_name = DASH_BOARD;
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string.reserve(3);
    //    send_key = "volume";
    //    receive_config_value = get_config_file_data(send_key);
    //    volume_value_config = stoi(receive_config_value);

    //    volume_value_config = (volume_value_config < MINIMUM_VALUE_VOLUME) ? MINIMUM_VALUE_VOLUME : (volume_value_config > MAXIMUM_VALUE_VOLUME) ? MAXIMUM_VALUE_VOLUME : ROUND_OFF_VOLUME(volume_value_config);
    //    update_config_data(send_key, to_string(volume_value_config));
    //    menu_settings_data->settings.dashboard.volume = to_string(volume_value_config);

    send_key = "automatic_adjustment_brightness";
    receive_config_value = get_config_file_data(send_key);
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{receive_config_value == "ON"}}));

    send_key = "brightness";
    receive_config_value = get_config_file_data(send_key);
    brightness_value_config = stoi(receive_config_value);

    brightness_value_config = (brightness_value_config < MINIMUM_VALUE_BRIGHTNESS) ? MINIMUM_VALUE_BRIGHTNESS : (brightness_value_config > MAXIMUM_VALUE_BRIGHTNESS) ? MAXIMUM_VALUE_BRIGHTNESS : ROUND_OFF_BRIGHTNESS(brightness_value_config);

    update_config_data(send_key, to_string(brightness_value_config));
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string.emplace_back(
        menu_string({.param_name = "", .uom = nullopt, .min_value = MINIMUM_VALUE_BRIGHTNESS,
                     .max_value = MAXIMUM_VALUE_BRIGHTNESS, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DIAPASONE, .visibility = true,
                     .submenu_string = to_string(brightness_value_config)}));

    send_key = "language_change";
    receive_config_value = get_config_file_data(send_key);
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{receive_config_value == "RUSSIAN"}}));
    CATCH_BLOCK
}

void MenuSettingsHandler::init_light_rain_sensor()
{
    TRY_BLOCK
    //uint8_t senitivity_value;
    string sensitivity_sensors;
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].item_name = LIGHT_RAIN_SENSOR;
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string.reserve(4);
    send_key = "automatic_low_beam";
    receive_config_value = get_config_file_data(send_key);
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{receive_config_value == STATUS_ON}}));
    send_key = "automatic_wiper_operation";
    receive_config_value = get_config_file_data(send_key);
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{receive_config_value == STATUS_ON}}));

    send_key = "sensor_sensitivity_to_rain";
    receive_config_value = get_config_file_data(send_key);
    auto senitivity_value = stoi(receive_config_value);
    senitivity_value = (senitivity_value < MINIMUM_VALUE_SENSITIVITY_RAIN) ? MINIMUM_VALUE_SENSITIVITY_RAIN : (senitivity_value > MAXIMUM_VALUE_SENSITIVITY_RAIN) ? MAXIMUM_VALUE_SENSITIVITY_RAIN : senitivity_value;
    update_config_data(send_key, to_string(senitivity_value));

    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string.emplace_back(
        menu_string({.param_name = "", .uom = nullopt, .min_value = MINIMUM_VALUE_SENSITIVITY_RAIN,
                     .max_value = MAXIMUM_VALUE_SENSITIVITY_RAIN, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DIAPASONE, .visibility = true,
                     .submenu_string = to_string(senitivity_value)}));

    send_key = "sensor_sensitivity_to_light";
    receive_config_value = get_config_file_data(send_key);
    senitivity_value = stoi(receive_config_value);
    senitivity_value = (senitivity_value > MAXIMUM_VALUE_SENSITIVITY_LIGHT) ? MAXIMUM_VALUE_SENSITIVITY_LIGHT : (senitivity_value < MINIMUM_VALUE_SENSITIVITY_LIGHT) ? MINIMUM_VALUE_SENSITIVITY_LIGHT : senitivity_value;
    update_config_data(send_key, to_string(senitivity_value));
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string.emplace_back(
        menu_string({.param_name = "", .uom = nullopt, .min_value = MINIMUM_VALUE_SENSITIVITY_LIGHT,
                     .max_value = MAXIMUM_VALUE_SENSITIVITY_LIGHT, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DIAPASONE, .visibility = true,
                     .submenu_string = to_string(senitivity_value)}));
    CATCH_BLOCK
}

void MenuSettingsHandler::init_climate_control_driver_cab()
{
    TRY_BLOCK
    uint8_t install_temperature_config;
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].item_name = CLIMATE_CONTROL_DRIVER_CAB;
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].opt_submenu_string.reserve(3);

    send_key = "installation_temperature_DC";
    receive_config_value = get_config_file_data(send_key);
    install_temperature_config = stoi(receive_config_value);
    install_temperature_config = (install_temperature_config < MINIMUM_INSTALLATION_TEMPERATURE) ? MINIMUM_INSTALLATION_TEMPERATURE : (install_temperature_config > MAXIMUM_INSTALLATION_TEMPERATURE) ? MAXIMUM_INSTALLATION_TEMPERATURE : install_temperature_config;
    update_config_data(send_key, to_string(install_temperature_config));
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].opt_submenu_string.emplace_back(
        menu_string({.param_name = "", .uom = nullopt, .min_value = MINIMUM_INSTALLATION_TEMPERATURE,
                     .max_value = MAXIMUM_INSTALLATION_TEMPERATURE, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_DIAPASONE, .visibility = true,
                     .submenu_string = to_string(install_temperature_config)}));
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = nullopt, .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = nullopt, .value_type = E_PT_BOOLPARAM, .visibility = true,
                     .submenu_string = bool{false}}));
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].opt_submenu_string.emplace_back(
        menu_string({ .param_name = "", .uom = "white", .min_value = nullopt,
                     .max_value = nullopt, .mid_value = nullopt,
                     .img_path = "pics/Menu/Bus1w.png", .value_type = E_PT_IMAGE_VALUE, .visibility = true,
                     .submenu_string = bool{false}}));
    CATCH_BLOCK
}

//void MenuSettingsHandler::update_dashboard()
//{
    //TRY_BLOCK
    //    uint8_t brightness_value = 0;
    //    check_ddsettings_value = false;
    //    int current_brightness;

    //    if ((menu_settings_data->services.door_managament.automatic_opening == "ON") && (check_ddsettings_value == false)) {
    //        try {
    //            current_brightness = stoi(menu_settings_data->settings.dashboard.brightness);
    //            brightness_value = static_cast<uint8_t>(current_brightness * brightness_factor);
    //            if (brightness_value < 10) {
    //                brightness_value = 10;
    //            }
    //            menu_settings_data->settings.dashboard.brightness = to_string(brightness_value);
    //            check_ddsettings_value = true;
    //        } catch (const std::invalid_argument& e) {
    //            std::cerr << "Error: Invalid brightness value." << std::endl;
    //        }
    //    } else if ((menu_settings_data->services.door_managament.automatic_opening == "OFF") && (check_ddsettings_value == true)) {
    //        try {
    //            current_brightness = stoi(menu_settings_data->settings.dashboard.brightness);
    //            brightness_value = static_cast<uint8_t>(current_brightness / brightness_factor);
    //            if (brightness_value < 10) {
    //                brightness_value = 10;
    //            }
    //            menu_settings_data->settings.dashboard.brightness = to_string(brightness_value);
    //            check_ddsettings_value = false;
    //        } catch (const std::invalid_argument& e) {
    //            std::cerr << "Error: Invalid brightness value." << std::endl;
    //        }
    //    }
    //CATCH_BLOCK
//}

//string MenuSettingsHandler::update_light_rain_sensor(string sensitivity_type, uint8_t sensitivity_level)
//{
//    TRY_BLOCK
//    QString return_value;
//    if (sensitivity_type == RAIN_SENSOR )
//    {
//        return_value = tr(SENSITIVITY_LEVEL_) + " ";
//        if (sensitivity_level == 0 || sensitivity_level == 5)
//            return_value += (sensitivity_level == 0) ? 0 : 5;
//        else
//            return_value += QString::number(sensitivity_level);
//    }
//    else
//        return_value = tr(SENSITIVITY_) + " " + QString::number(sensitivity_level);

//    return return_value.toStdString();

//    string return_sensitivity;
//    if (sensitivity_type == "RAIN_SENSOR") {
//        switch (sensitivity_level) {
//        case 1:
//            return_sensitivity = SENSITIVITY_LEVEL_1;
//            break;
//        case 2:
//            return_sensitivity = SENSITIVITY_LEVEL_2;
//            break;
//        case 3:
//            return_sensitivity = SENSITIVITY_LEVEL_3;
//            break;
//        case 4:
//            return_sensitivity = SENSITIVITY_LEVEL_4;
//            break;
//        default:
//            return_sensitivity = INVALID_VALUE;
//            break;
//        }
//    }

//    if (sensitivity_type == "LIGHT_SENSOR") {
//        switch (sensitivity_level) {
//        case 0:
//            return_sensitivity = SENSITIVITY_0;
//            break;
//        case 1:
//            return_sensitivity = SENSITIVITY_1;
//            break;
//        case 2:
//            return_sensitivity = SENSITIVITY_2;
//            break;
//        case 3:
//            return_sensitivity = SENSITIVITY_3;
//            break;
//        case 4:
//            return_sensitivity = SENSITIVITY_4;
//            break;
//        case 5:
//            return_sensitivity = SENSITIVITY_5;
//            break;
//        default:
//            return_sensitivity = INVALID_VALUE;
//            break;
//        }
//    }
//    return return_sensitivity;
//    CATCH_BLOCK
//}

void MenuSettingsHandler::update_climate_control_driver_cab()
{
    TRY_BLOCK
    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_DC2_ID)->get_state() != CAN_MESSAGE_STATE_OK)
        return;

    DC2_t* msg_dc2 = reinterpret_cast<DC2_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_DC2_ID));
    uint8_t result;

    result = msg_dc2->frontalac_coolant_damper;
    bool* coolant_damper = get_if<bool>(&(menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].opt_submenu_string[1].submenu_string));
    *coolant_damper = (result == 1) ? true : false;

    result = msg_dc2->frontalac_recirculation_damper;
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].opt_submenu_string[2].img_path = (result == 1) ?  "pics/Menu/Bus1w.png" : "pics/Menu/Bus2w.png";
    menu_settings_data->submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].opt_submenu_string[2].uom = (result == 3) ? "yellow" : "white";
    CATCH_BLOCK
}

string MenuSettingsHandler::get_config_file_data(string key_data)
{
    TRY_BLOCK
    QString text = "NULL";
    string return_value;
    text = json_configure_data->get_config_data(QString::fromStdString(key_data));
    if ((text == "NULL") || (text == "")) {
        text = "0";
    }
    return_value = text.toStdString();
    return return_value;
    CATCH_BLOCK
}

bool MenuSettingsHandler::update_config_data(string config_data_str, string config_value_str)
{
    TRY_BLOCK
    bool return_status = false;
    QString key_data;
    QString config_value;
    key_data = QString::fromStdString(config_data_str);
    config_value = QString::fromStdString(config_value_str);
    return_status = json_configure_data->write_json_file(key_data, config_value);
    return return_status;
    CATCH_BLOCK
}

void MenuSettingsHandler::init_subscribe()
{
    TRY_BLOCK
    auto _ptr = subscribe_notifer::get_instance();
    _ptr->subscribe(HMIHANDLER_DC2_ID, this);
    CATCH_BLOCK
}
