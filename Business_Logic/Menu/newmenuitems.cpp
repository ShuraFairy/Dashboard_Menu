#include "newmenuitems.h"
#include "Business_Logic/Common/menu_defines.h"

static const vector<string> sc_str_submenu_names
{
    ENGINE,
    TRANSMISSION,
    BATTERY,
    PNEUMATIC_SYSTEM,
    TIRE_PRESSURE_AND_TEMPERATURE,
    REAGENT_ADBLUE,
    WIPERS,
    BRAKE_PADS_WEAR
};

newMenuItems::newMenuItems()
    : vehicle_type(2)
    , str_rus("РУССКИЙ")
    , str_eng("ENGLISH")
    , m_esl_current(E_SL_DASH)
    , m_cached_main_pos()
    , m_cached_list_pos()
    , m_list_limit()
    , m_cached_param_pos()
    , m_paramlist_limit()
    , m_cached_subparam_pos()
    , m_subparamlist_limit()
    , m_cached_pass_letter()
    , m_str_trypass("0000")
{
    m_ptr_msgs_handler = HmiHandler::getInstance();
    init_subscribe();
}

bool newMenuItems::update_info(uint32_t _id)
{
    TRY_BLOCK
    if(_id == HMIHANDLER_DD_INFO3_ID && m_ptr_msgs_handler->get_ptr_to_msg(HMIHANDLER_DD_INFO3_ID)->get_state() == CAN_MESSAGE_STATE_OK)
    {
        DD_INFO3_t* m_data_msg_dd_info3 = reinterpret_cast<DD_INFO3_t*>(m_ptr_msgs_handler->get_data_from_msg(HMIHANDLER_DD_INFO3_ID));
        set_subitem_visibility(*m_data_msg_dd_info3);
    }
    return true;
    CATCH_BLOCK
}

void newMenuItems::set_subitem_visibility(DD_INFO3_t _data_from_msg_dd_info3)
{
    TRY_BLOCK

    //ENGINE 5
    submenus[E_MT_PARAMETERS].submenu_page.find(ENGINE)->second.visibility= (_data_from_msg_dd_info3.bitfield.parameters_engine_submenu != 0);
    submenus[E_MT_PARAMETERS].submenu_page.find(ENGINE)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.parameters_engine_submenu & (1u));
    submenus[E_MT_PARAMETERS].submenu_page.find(ENGINE)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.parameters_engine_submenu & (2u));
    submenus[E_MT_PARAMETERS].submenu_page.find(ENGINE)->second.opt_submenu_string[2].visibility=(_data_from_msg_dd_info3.bitfield.parameters_engine_submenu & (4u));
    submenus[E_MT_PARAMETERS].submenu_page.find(ENGINE)->second.opt_submenu_string[3].visibility=(_data_from_msg_dd_info3.bitfield.parameters_engine_submenu & (8u));
    submenus[E_MT_PARAMETERS].submenu_page.find(ENGINE)->second.opt_submenu_string[4].visibility=(_data_from_msg_dd_info3.bitfield.parameters_engine_submenu & (16u));

    //TRANSMISSION 2
    submenus[E_MT_PARAMETERS].submenu_page.find(TRANSMISSION)->second.visibility= (_data_from_msg_dd_info3.bitfield.parameters_transmission_submenu != 0);
    submenus[E_MT_PARAMETERS].submenu_page.find(TRANSMISSION)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.parameters_transmission_submenu & (1u));
    submenus[E_MT_PARAMETERS].submenu_page.find(TRANSMISSION)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.parameters_transmission_submenu & (2u));
    submenus[E_MT_PARAMETERS].submenu_page.find(TRANSMISSION)->second.opt_submenu_string[2].visibility=(_data_from_msg_dd_info3.bitfield.parameters_transmission_submenu & (4u));

    //BATTERY 3
    submenus[E_MT_PARAMETERS].submenu_page.find(BATTERY)->second.visibility= (_data_from_msg_dd_info3.bitfield.parameters_battery_submenu != 0);
    submenus[E_MT_PARAMETERS].submenu_page.find(BATTERY)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.parameters_battery_submenu & (1u));
    submenus[E_MT_PARAMETERS].submenu_page.find(BATTERY)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.parameters_battery_submenu & (2u));
    submenus[E_MT_PARAMETERS].submenu_page.find(BATTERY)->second.opt_submenu_string[2].visibility=(_data_from_msg_dd_info3.bitfield.parameters_battery_submenu & (4u));

    //PNEUMATIC_SYSTEM 5
    submenus[E_MT_PARAMETERS].submenu_page.find(PNEUMATIC_SYSTEM)->second.visibility= (_data_from_msg_dd_info3.bitfield.parameters_pneumatic_submenu != 0);
    submenus[E_MT_PARAMETERS].submenu_page.find(PNEUMATIC_SYSTEM)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.parameters_pneumatic_submenu & (1u));
    submenus[E_MT_PARAMETERS].submenu_page.find(PNEUMATIC_SYSTEM)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.parameters_pneumatic_submenu & (2u));
    submenus[E_MT_PARAMETERS].submenu_page.find(PNEUMATIC_SYSTEM)->second.opt_submenu_string[2].visibility=(_data_from_msg_dd_info3.bitfield.parameters_pneumatic_submenu & (4u));
    submenus[E_MT_PARAMETERS].submenu_page.find(PNEUMATIC_SYSTEM)->second.opt_submenu_string[3].visibility=(_data_from_msg_dd_info3.bitfield.parameters_pneumatic_submenu & (8u));
    submenus[E_MT_PARAMETERS].submenu_page.find(PNEUMATIC_SYSTEM)->second.opt_submenu_string[4].visibility=(_data_from_msg_dd_info3.bitfield.parameters_pneumatic_submenu & (16u));

    //REAGENT_ADBLUE 2
    submenus[E_MT_PARAMETERS].submenu_page.find(REAGENT_ADBLUE)->second.visibility= (_data_from_msg_dd_info3.bitfield.parameters_adblue_submenu != 0);
    submenus[E_MT_PARAMETERS].submenu_page.find(REAGENT_ADBLUE)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.parameters_adblue_submenu & (1u));
    submenus[E_MT_PARAMETERS].submenu_page.find(REAGENT_ADBLUE)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.parameters_adblue_submenu & (2u));

    //WIPERS 2
    submenus[E_MT_PARAMETERS].submenu_page.find(WIPERS)->second.visibility = (_data_from_msg_dd_info3.bitfield.parameters_wipers_submenu != 0);
    submenus[E_MT_PARAMETERS].submenu_page.find(WIPERS)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.parameters_wipers_submenu & (1u));
    submenus[E_MT_PARAMETERS].submenu_page.find(WIPERS)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.parameters_wipers_submenu & (2u));

    //CLIMATE_CONTROL_DRIVER_CAB 3

    submenus[E_MT_SETTINGS].submenu_page.find(CLIMATE_CONTROL_DRIVER_CAB)->second.visibility= (_data_from_msg_dd_info3.bitfield.settings_climate_ctrl_driver_submenu != 0);
    submenus[E_MT_SETTINGS].submenu_page.find(CLIMATE_CONTROL_DRIVER_CAB)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.settings_climate_ctrl_driver_submenu & (1u));
    submenus[E_MT_SETTINGS].submenu_page.find(CLIMATE_CONTROL_DRIVER_CAB)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.settings_climate_ctrl_driver_submenu & (2u));
    submenus[E_MT_SETTINGS].submenu_page.find(CLIMATE_CONTROL_DRIVER_CAB)->second.opt_submenu_string[2].visibility=(_data_from_msg_dd_info3.bitfield.settings_climate_ctrl_driver_submenu & (4u));

    //LIGHT_RAIN_SENSOR 4
    submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second.visibility= (_data_from_msg_dd_info3.bitfield.settings_light_rain_sensor_submenu != 0);
    submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.settings_light_rain_sensor_submenu & (1u));
    submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.settings_light_rain_sensor_submenu & (2u));
    submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second.opt_submenu_string[2].visibility=(_data_from_msg_dd_info3.bitfield.settings_light_rain_sensor_submenu & (4u));
    submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second.opt_submenu_string[3].visibility=(_data_from_msg_dd_info3.bitfield.settings_light_rain_sensor_submenu & (8u));

    //HEATING_SYSTEM 3
    submenus[E_MT_SETTINGS].submenu_page.find(HEATING_SYSTEM)->second.visibility= (_data_from_msg_dd_info3.bitfield.settings_heating_system_submenu != 0);
    submenus[E_MT_SETTINGS].submenu_page.find(HEATING_SYSTEM)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.settings_heating_system_submenu & (1u));
    submenus[E_MT_SETTINGS].submenu_page.find(HEATING_SYSTEM)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.settings_heating_system_submenu & (2u));
    submenus[E_MT_SETTINGS].submenu_page.find(HEATING_SYSTEM)->second.opt_submenu_string[2].visibility=(_data_from_msg_dd_info3.bitfield.settings_heating_system_submenu & (4u));

    //DASH_BOARD 2
    submenus[E_MT_SETTINGS].submenu_page.find(DASH_BOARD)->second.visibility= (_data_from_msg_dd_info3.bitfield.settings_dash_board_submenu != 0);
    submenus[E_MT_SETTINGS].submenu_page.find(DASH_BOARD)->second.opt_submenu_string[E_MTSET_DASH_AUTO_BRIGHT].visibility=(_data_from_msg_dd_info3.bitfield.settings_dash_board_submenu & (1u));
    submenus[E_MT_SETTINGS].submenu_page.find(DASH_BOARD)->second.opt_submenu_string[E_MTSET_DASH_BRIGHT].visibility=(_data_from_msg_dd_info3.bitfield.settings_dash_board_submenu & (2u));
    submenus[E_MT_SETTINGS].submenu_page.find(DASH_BOARD)->second.opt_submenu_string[E_MTSET_DASH_LANG].visibility=(_data_from_msg_dd_info3.bitfield.settings_dash_board_submenu & (4u));

    //SOFTWARE_VERSION 4
    submenus[E_MT_SERVICES].submenu_page.find(SOFTWARE_VERSION)->second.visibility= (_data_from_msg_dd_info3.bitfield.service_software_version_submenu != 0);
    submenus[E_MT_SERVICES].submenu_page.find(SOFTWARE_VERSION)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.service_software_version_submenu & (1u));
    submenus[E_MT_SERVICES].submenu_page.find(SOFTWARE_VERSION)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.service_software_version_submenu & (2u));
    submenus[E_MT_SERVICES].submenu_page.find(SOFTWARE_VERSION)->second.opt_submenu_string[2].visibility=(_data_from_msg_dd_info3.bitfield.service_software_version_submenu & (4u));
    submenus[E_MT_SERVICES].submenu_page.find(SOFTWARE_VERSION)->second.opt_submenu_string[3].visibility=(_data_from_msg_dd_info3.bitfield.service_software_version_submenu & (8u));

    //ADDITIONAL_FUNCTIONALITY 2
    submenus[E_MT_SERVICES].submenu_page.find(ADDITIONAL_FUNCTIONALITY)->second.visibility= (_data_from_msg_dd_info3.bitfield.service_add_func_submenu != 0);
    submenus[E_MT_SERVICES].submenu_page.find(ADDITIONAL_FUNCTIONALITY)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.service_add_func_submenu & (1u));
    submenus[E_MT_SERVICES].submenu_page.find(ADDITIONAL_FUNCTIONALITY)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.service_add_func_submenu & (2u));

    //WIPERS 2
    submenus[E_MT_SERVICES].submenu_page.find(WIPERS)->second.visibility= (_data_from_msg_dd_info3.bitfield.service_wipers_submenu != 0);
    submenus[E_MT_SERVICES].submenu_page.find(WIPERS)->second.opt_submenu_string[0].visibility=(_data_from_msg_dd_info3.bitfield.service_wipers_submenu & (1u));
    submenus[E_MT_SERVICES].submenu_page.find(WIPERS)->second.opt_submenu_string[1].visibility=(_data_from_msg_dd_info3.bitfield.service_wipers_submenu & (2u));

    //SERVICES
    submenus[E_MT_SERVICES].submenu_page.find(STEERING_ANGLE_SENSOR)->second.visibility=_data_from_msg_dd_info3.bitfield.service_steering_angle_sens_submenu;
    submenus[E_MT_SERVICES].submenu_page.find(DATA_SOURCE)->second.visibility=_data_from_msg_dd_info3.bitfield.service_data_source_submenu;
    submenus[E_MT_SERVICES].submenu_page.find("DIAGNOSTICS_TROUBLE_CODE")->second.visibility=_data_from_msg_dd_info3.bitfield.service_dtc_submenu;
    submenus[E_MT_SERVICES].submenu_page.find(DOOR_MANAGEMENT)->second.visibility=_data_from_msg_dd_info3.bitfield.service_door_management_submenu;
    submenus[E_MT_SERVICES].submenu_page.find(CHANGE_PASSWORD)->second.visibility=_data_from_msg_dd_info3.bitfield.service_change_password_submenu;
    submenus[E_MT_DIAGNOSTICS].submenu_page.find(EMERGENCY_HAMMERS)->second.visibility=_data_from_msg_dd_info3.bitfield.diagnostics_emergency_hammers_submenu;
    submenus[E_MT_DIAGNOSTICS].submenu_page.find(DOOR_SENSORS)->second.visibility=_data_from_msg_dd_info3.bitfield.diagnostics_door_sensors_submenu;
    submenus[E_MT_DIAGNOSTICS].submenu_page.find(EMERGENCY_CRANES)->second.visibility=_data_from_msg_dd_info3.bitfield.diagnostics_emergency_cranes_submenu;

    //DIAGNOSTICS
    submenus[E_MT_DIAGNOSTICS].submenu_page.find(HEATERS)->second.visibility=_data_from_msg_dd_info3.bitfield.diagnostics_heaters_submenu;
    submenus[E_MT_DIAGNOSTICS].submenu_page.find(FIRE_EXTINGUISHERS)->second.visibility=_data_from_msg_dd_info3.bitfield.diagnostics_fire_extinguishers_submenu;
    submenus[E_MT_DIAGNOSTICS].submenu_page.find(LIGHTING_EQUIPEMENTS)->second.visibility=_data_from_msg_dd_info3.bitfield.diagnostics_lighting_equipements_submenu;
    submenus[E_MT_DIAGNOSTICS].submenu_page.find(DOOR_VALVES)->second.visibility=_data_from_msg_dd_info3.bitfield.diagnostics_door_valves_submenu;
    submenus[E_MT_DIAGNOSTICS].submenu_page.find(HEATING_SYSTEM_VALVES)->second.visibility=_data_from_msg_dd_info3.bitfield.diagnostics_heating_sys_valves_submenu;
    submenus[E_MT_DIAGNOSTICS].submenu_page.find(FAILURES)->second.visibility=_data_from_msg_dd_info3.bitfield.diagnostics_failures_submenu;

    //PARAMETERS
    submenus[E_MT_PARAMETERS].submenu_page.find(BRAKE_PADS_WEAR)->second.visibility=_data_from_msg_dd_info3.bitfield.parameters_brake_pads_wear_submenu;
    submenus[E_MT_PARAMETERS].submenu_page.find(TIRE_PRESSURE_AND_TEMPERATURE)->second.visibility=_data_from_msg_dd_info3.bitfield.parameters_tire_press_and_temp_submenu;

    if(m_data_from_msg_dd_info3.data!=_data_from_msg_dd_info3.data)
    {
           QtJsonConfigureData::get_instance()->write_json_file("subitem_menu_visibility", QString("0x%1").arg(_data_from_msg_dd_info3.data, 0, 16));
           m_data_from_msg_dd_info3.data =_data_from_msg_dd_info3.data;
    }
    CATCH_BLOCK
}

void newMenuItems::change_level(bool _dir)
{
    TRY_BLOCK
    bool need_to_emit = false;

    switch(m_esl_current)
    {
    case E_SL_DASH:
        if (_dir)
            m_esl_current = E_SL_MAIN;

        need_to_emit = _dir;
        break;
    case E_SL_MAIN:
        if (_dir)
        {
            if (m_cached_main_pos == E_MT_SERVICES)
                m_esl_current = E_SL_PASSLOCK;
            else
                m_esl_current = E_SL_LIST;
        }
        else
        {
            m_cached_main_pos = E_MT_PARAMETERS;
            m_esl_current = E_SL_DASH;
        }
        need_to_emit = true;
        break;
    case E_SL_LIST:
        if (_dir)
        {
            if (m_ptr_right_list[0]->value_type < E_PT_BRAKEPADS || m_ptr_right_list[0]->value_type == E_PT_DTC_CODE)
                m_esl_current = E_SL_PARAMS;
        }
        else
        {
            m_cached_list_pos = 0;
            m_esl_current = E_SL_MAIN;
        }
        need_to_emit = true;
        break;
    case E_SL_PARAMS:
        if (_dir)
        {
            auto current_param_type = get_param_type(m_cached_param_pos);
            if (current_param_type == E_PT_GROUP || current_param_type == E_PT_DTC_CODE)
            {
                m_cached_subparam_pos = m_cached_param_pos;
                m_esl_current = E_SL_SUBPARAMS;
                need_to_emit = true;
            }
            else if (current_param_type == E_PT_BOOLPARAM)
                set_bool_param();
        }
        else
        {
            m_cached_param_pos = 0;
            m_esl_current = E_SL_LIST;
            need_to_emit = true;
        }
        break;
    case E_SL_SUBPARAMS:
        if (!_dir)
        {
            m_esl_current = E_SL_PARAMS;
            m_cached_param_pos = m_cached_subparam_pos;
            m_cached_subparam_pos = 0;
            need_to_emit = true;
        }
        break;
    case E_SL_PASSLOCK:
        if (_dir)
        {
            if (check_pass())
            {
                m_esl_current = E_SL_LIST;
                need_to_emit = true;
            }
            else
                emit wrong_password();
        }
        else
        {
            m_esl_current = E_SL_MAIN;
            need_to_emit = true;
        }
        m_cached_pass_letter = 0;
        m_str_trypass = "0000";
        break;
    default:
        //TODO: THROW EXCEPTION CLASS
        break;
    }
    if (need_to_emit)
    {
        if(!m_ptr_menu_drawer->set_new_screen(m_esl_current))
        {
            m_esl_current = E_SL_MAIN;
            return;
        }

        m_ptr_menu_drawer->set_new_focus(m_cached_main_pos, m_cached_list_pos, m_cached_param_pos);
    }
    CATCH_BLOCK
}

void newMenuItems::change_focus_item(eDirrection _dir)
{
    TRY_BLOCK
    bool need_to_emit = false;

    switch(m_esl_current)
    {
    case E_SL_DASH:
        break;
    case E_SL_MAIN:
        if (_dir == E_D_RIGHT || _dir == E_D_LEFT)
        {
            change_cached_value(&m_cached_main_pos, nullopt, E_MT_SUBMENU_TOTAL - 1, _dir == E_D_RIGHT);
            need_to_emit = true;
        }
        break;
    case E_SL_LIST:
        if (_dir == E_D_DOWN || _dir == E_D_UP)
        {
            change_cached_value(&m_cached_list_pos, nullopt, m_ptr_left_list.size() - 1, _dir == E_D_DOWN);
            need_to_emit = true;
        }
        break;
    case E_SL_PARAMS:
        if (_dir == E_D_DOWN || _dir == E_D_UP)
        {
            change_cached_value(&m_cached_param_pos, nullopt, m_ptr_right_list.size()  - 1, _dir == E_D_DOWN);
            need_to_emit = true;
        }
        else if (get_param_type(m_cached_param_pos) == E_PT_DIAPASONE && (_dir == E_D_RIGHT || _dir == E_D_LEFT))
            set_diap_param(_dir == E_D_RIGHT);
        break;
    case E_SL_SUBPARAMS:
        if (_dir == E_D_DOWN || _dir == E_D_UP)
        {
            change_cached_value(&m_cached_param_pos, nullopt, m_subparamlist_limit - 1, _dir == E_D_DOWN);
            need_to_emit = true;
        }
        break;
    case E_SL_PASSLOCK:
        if (_dir == E_D_RIGHT || _dir == E_D_LEFT)
            change_cached_value(&m_cached_pass_letter, nullopt, 3, _dir == E_D_RIGHT);
        else if(_dir == E_D_DOWN || _dir == E_D_UP)
            change_cached_value(reinterpret_cast<uint8_t*>(&m_str_trypass[m_cached_pass_letter]), '0', '9', _dir == E_D_UP);
        break;
    default:
        //TODO: THROW EXCEPTION CLASS
        break;
    }
    if (need_to_emit)
        m_ptr_menu_drawer->set_new_focus(m_cached_main_pos, m_cached_list_pos, m_cached_param_pos);
    CATCH_BLOCK
}

void newMenuItems::get_left_list(QStringList* _list)
{
    TRY_BLOCK
    m_ptr_left_list.clear();
    if (!_list->empty())
        _list->clear();

    if (m_cached_main_pos != E_MT_PARAMETERS)
    {
        for(auto it = submenus[m_cached_main_pos].submenu_page.begin(); it != submenus[m_cached_main_pos].submenu_page.end(); it++)
        {
            if (!it->second.visibility)
                continue;

            _list->push_back(QString::fromStdString(it->second.item_name));
            m_ptr_left_list.push_back(&it->second);
        }
    }
    else
    {
        for (auto& it : sc_str_submenu_names)
        {
            if (!submenus[E_MT_PARAMETERS].submenu_page[it].visibility)
                continue;

            _list->push_back(QString::fromStdString(submenus[E_MT_PARAMETERS].submenu_page[it].item_name));
            m_ptr_left_list.push_back(&submenus[E_MT_PARAMETERS].submenu_page[it]);
        }
    }
    CATCH_BLOCK
}

void newMenuItems::get_right_list(QList<QStringList>* _list, QStringList* _values)
{
    TRY_BLOCK
    if (m_esl_current != E_SL_SUBPARAMS)
        m_ptr_right_list.clear();
    if (!_list->empty())
        _list->clear();
    if(!_values->empty())
        _values->clear();

    uint8_t i = 0;
    if (m_esl_current != E_SL_SUBPARAMS && m_ptr_left_list.size()>0)
    {
        for(auto& it : m_ptr_left_list[m_cached_list_pos]->opt_submenu_string)
        {
            if(!it.visibility)
                continue;

            QStringList temp_list;
            temp_list.append(it.param_name);
            temp_list.append(QString::fromStdString(it.img_path.value_or("")));
            temp_list.append(QString::fromStdString(to_string(get_param_type(i++))));
            temp_list.append(QString::fromStdString(to_string(it.min_value.value_or(0))));
            temp_list.append(QString::fromStdString(to_string(it.max_value.value_or(0))));
            if(it.mid_value.has_value())
            {
                std::ostringstream mid{};
                mid << std::fixed << std::setprecision(0) << it.mid_value.value();
                temp_list.append(QString::fromStdString(mid.str()));
            }
            else
                temp_list.append("");
            temp_list.append(it.uom.value_or(""));
            if (it.value_type != E_PT_BOOLPARAM)
            {
                string* value = get_if<string>(&it.submenu_string);
                if (value)
                {
                    temp_list.append(QString::fromStdString(*value));
                    _values->push_back(QString::fromStdString(*value));
                }
                else if (get_param_type((it.value_type != E_PT_GROUP) && (it.value_type != E_PT_DTC_CODE)))
                {
                    temp_list.append("--");
                    _values->push_back("--");
                }
                else
                {
                    temp_list.append("");
                    _values->push_back("");
                }
            }
            else
            {
                bool* value = get_if<bool>(&it.submenu_string);
                if(unlikely(&it == &submenus[E_MT_SETTINGS].submenu_page.find(CLIMATE_CONTROL_DRIVER_CAB)->second.opt_submenu_string[1]))
                {
                    temp_list.append((*value)? str_open : str_close);
                    _values->push_back((*value)? str_open : str_close);
                }
                else if (unlikely(&it == &submenus[E_MT_SETTINGS].submenu_page.find(DASH_BOARD)->second.opt_submenu_string[E_MTSET_DASH_LANG]))
                {
                    temp_list.append((*value)? str_rus : str_eng);
                    _values->push_back((*value)? str_rus : str_eng);
                }
                else
                {
                    temp_list.append((*value)? str_on : str_off);
                    _values->push_back((*value)? str_on : str_off);
                }
            }

            _list->push_back(temp_list);
            m_ptr_right_list.push_back(&it);
        }
    }
    else
    {
        m_subparamlist_limit = 0;
        if (m_ptr_right_list[m_cached_param_pos]->value_type != E_PT_DTC_CODE)
        {
            FailureModule* ptr_temp = get_if<FailureModule>(&(m_ptr_right_list[m_cached_param_pos]->submenu_string));
            for(auto& it : ptr_temp->error_code)
            {
    //            if(!it.error_code_status)
    //                continue;

                QStringList temp_list;
                temp_list.append(QString::fromStdString(it.error_code));
                temp_list.append(QString::fromStdString(it.error_code_description));
                temp_list.append(QString::fromStdString(to_string(get_param_type(i++))));
                temp_list.append(str_recomendation);
                temp_list.append(QString::fromStdString(it.error_repetation));

                _list->push_back(temp_list);
                m_subparamlist_limit++;
            }
        }
        else
        {
            DtcModule* ptr_temp = get_if<DtcModule>(&(m_ptr_right_list[m_cached_param_pos]->submenu_string));
            for(auto& it : ptr_temp->trouble_code)
            {
//            if(!it.error_code_status)
//                continue;

                QStringList temp_list;
                temp_list.append(QString::fromStdString(it.trouble_code_source) + MENU_RANGE_SEPERATOR + QString::number(it.trouble_code_spn) + MENU_RANGE_SEPERATOR + QString::number(it.trouble_code_fmi));
                temp_list.append(QString::fromStdString(it.trouble_code_recommendations));
                temp_list.append(QString::fromStdString(to_string(E_PT_GROUP)));
                temp_list.append(str_advice);
                temp_list.append(QString::number(it.trouble_code_repetations));

                _list->push_back(temp_list);
                m_subparamlist_limit++;
            }
        }
    }
    CATCH_BLOCK
}

void newMenuItems::get_value_list(QStringList* _list)
{
    TRY_BLOCK
    if (m_ptr_right_list.size() <= 0)
        return;

    if (!_list->empty())
        _list->clear();

    for (auto& it : m_ptr_left_list[m_cached_list_pos]->opt_submenu_string)
    {
        if(!it.visibility)
            continue;

        if (it.value_type != E_PT_BOOLPARAM)
        {
            string* value = get_if<string>(&it.submenu_string);
            if (value)
            {
                _list->append(QString::fromStdString(*value));
            }
            else
            {
                _list->append("--");
            }
        }
        else
        {
            bool* value = get_if<bool>(&it.submenu_string);
            if(unlikely(&it == &submenus[E_MT_SETTINGS].submenu_page.find(CLIMATE_CONTROL_DRIVER_CAB)->second.opt_submenu_string[1]))
                _list->append((*value)? str_open : str_close);
            else if(unlikely(&it == &submenus[E_MT_SETTINGS].submenu_page.find(DASH_BOARD)->second.opt_submenu_string[E_MTSET_DASH_LANG]))
                _list->append((*value)? str_rus : str_eng);
            else
                _list->append((*value)? str_on : str_off);
        }
    }
    CATCH_BLOCK
}

void newMenuItems::check_active_list(submenu_window* _ptr_window)
{
    TRY_BLOCK
    if(m_esl_current > E_SL_MAIN && m_esl_current < E_SL_SUBPARAMS)
        if (m_ptr_left_list.size() > 0 && m_ptr_left_list.size() > m_cached_list_pos && m_ptr_left_list[m_cached_list_pos] == _ptr_window)
            m_ptr_menu_drawer->set_values(m_cached_main_pos > E_MT_PARAMETERS);
    CATCH_BLOCK
}

eParamType newMenuItems::get_param_type(uint8_t i)
{
    TRY_BLOCK
    if(m_ptr_left_list.size() > m_cached_list_pos && m_ptr_left_list[m_cached_list_pos]->opt_submenu_string.size() > i)
    {
        auto temp = m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[i].value_type;
        return temp == E_PT_DTC_CODE ? E_PT_GROUP : temp;
    }
    else
        return E_PT_CONSTVALUE;
    CATCH_BLOCK
}

void newMenuItems::set_bool_param()
{
    TRY_BLOCK
    if (m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[m_cached_param_pos].value_type != E_PT_BOOLPARAM)
        return;

    if (m_cached_main_pos == E_MT_DIAGNOSTICS)
    {
        if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_DIAGNOSTICS].submenu_page.find(LIGHTING_EQUIPEMENTS)->second)
        {
            if (m_cached_param_pos == 0)
            {
                bool* ptr_bool = get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[0].submenu_string);
                *ptr_bool = !(*ptr_bool);
                for (auto& it : m_ptr_left_list[m_cached_list_pos]->opt_submenu_string)
                {
                    bool* temp = get_if<bool>(&it.submenu_string);
                    *temp = *ptr_bool;
                }
            }
            else
            {
                bool* ptr_bool = get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[m_cached_param_pos].submenu_string);
                *ptr_bool = !(*ptr_bool);
                ptr_bool = get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[0].submenu_string);
                *ptr_bool = false;
                for (auto& it : m_ptr_left_list[m_cached_list_pos]->opt_submenu_string)
                {
                    bool* temp = get_if<bool>(&it.submenu_string);
                    *ptr_bool = *ptr_bool || *temp;
                }
            }
            auto _ptr = HmiHandler::getInstance();
            DD_Settings_t* ptr_dd = reinterpret_cast<DD_Settings_t*>(_ptr->get_data_from_msg(HMIHANDLER_DD_SETTINGS_ID));
            ptr_dd->parking_lights = *(get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[1].submenu_string));
            ptr_dd->low_beam_headlights = *(get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[2].submenu_string));
            ptr_dd->high_beam_headlights = *(get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[3].submenu_string));
            ptr_dd->direction_indicators = *(get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[4].submenu_string));
            ptr_dd->daytime_running_lights = *(get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[5].submenu_string));
            ptr_dd->fog_lights = *(get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[6].submenu_string));
            ptr_dd->rear_fog_lights = *(get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[7].submenu_string));
            ptr_dd->reversing_lights = *(get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[8].submenu_string));
            ptr_dd->stop_signal = *(get_if<bool>(&m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[9].submenu_string));
        }
    }
    else if (m_cached_main_pos == E_MT_SETTINGS)
    {
        if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(HEATING_SYSTEM)->second)
        {
            auto _ptr = HmiHandler::getInstance();
            DD_Settings_t* ptr_dd = reinterpret_cast<DD_Settings_t*>(_ptr->get_data_from_msg(HMIHANDLER_DD_SETTINGS_ID));
            if (m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(HEATING_SYSTEM)->second.opt_submenu_string[1])
            {
                bool* ptr_heater_errors_reset = get_if<bool>(&(submenus[E_MT_SETTINGS].submenu_page[HEATING_SYSTEM].opt_submenu_string[1].submenu_string));
                *ptr_heater_errors_reset = !(*ptr_heater_errors_reset);
                ptr_dd->reset_heater_errors = *ptr_heater_errors_reset;
            }
            else
            {
                bool* ptr_heater_release = get_if<bool>(&(submenus[E_MT_SETTINGS].submenu_page[HEATING_SYSTEM].opt_submenu_string[2].submenu_string));
                *ptr_heater_release = !(*ptr_heater_release);
                ptr_dd->unlocking_the_heater = *ptr_heater_release;
            }
        }
        else if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(DASH_BOARD)->second)
        {
            if (m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(DASH_BOARD)->second.opt_submenu_string[E_MTSET_DASH_AUTO_BRIGHT])
            {
                bool* ptr_auto_bright = get_if<bool>(&(submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string[E_MTSET_DASH_AUTO_BRIGHT].submenu_string));
                *ptr_auto_bright = !(*ptr_auto_bright);
                QtJsonConfigureData::get_instance()->write_json_file("automatic_adjustment_brightness", *ptr_auto_bright ? STATUS_ON : STATUS_OFF);
                if (*ptr_auto_bright)
                {
                    QtJsonConfigureData::get_instance()->write_json_file("brightness", "50");
                    string* ptr_bright = get_if<string>(&(submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string[E_MTSET_DASH_BRIGHT].submenu_string));
                    *ptr_bright = "50";
                    set_brightness("50");
                }
            }
            else
            {
                bool* ptr_lang = get_if<bool>(&(submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string[E_MTSET_DASH_LANG].submenu_string));
                *ptr_lang = !(*ptr_lang);
                QtJsonConfigureData::get_instance()->write_json_file("language_change", *ptr_lang ? LANGUAGE_RUSSIAN : LANGUAGE_ENGLISH);
                m_ptr_menu_drawer->set_language();
            }

        }
        else if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second)
        {
            auto _ptr = HmiHandler::getInstance();
            DD_Settings_t* ptr_dd = reinterpret_cast<DD_Settings_t*>(_ptr->get_data_from_msg(HMIHANDLER_DD_SETTINGS_ID));
            if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second.opt_submenu_string[0])
            {
                bool* ptr_automatic_low_beam = get_if<bool>(&(submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string[0].submenu_string));
                *ptr_automatic_low_beam = !(*ptr_automatic_low_beam);
                ptr_dd->auto_settings_low_beam = *ptr_automatic_low_beam;
                QtJsonConfigureData::get_instance()->write_json_file(AUTOMATIC_LOW_BEAM_CONFIG, *ptr_automatic_low_beam ? STATUS_ON : STATUS_OFF);
            }
            else if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second.opt_submenu_string[1])
            {
                bool* ptr_automatic_wiper_ops = get_if<bool>(&(submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string[1].submenu_string));
                *ptr_automatic_wiper_ops = !(*ptr_automatic_wiper_ops);
                ptr_dd->auto_wiper_settings_mode = *ptr_automatic_wiper_ops;
                QtJsonConfigureData::get_instance()->write_json_file(AUTOMATIC_WIPER_OPERATION_CONFIG, *ptr_automatic_wiper_ops ? STATUS_ON : STATUS_OFF);
            }
        }
    }
    else if (m_cached_main_pos == E_MT_SERVICES)
    {
        if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_SERVICES].submenu_page.find(DOOR_MANAGEMENT)->second)
        {
            auto _ptr = HmiHandler::getInstance();
            DD_Settings_t* ptr_dd = reinterpret_cast<DD_Settings_t*>(_ptr->get_data_from_msg(HMIHANDLER_DD_SETTINGS_ID));
            if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SERVICES].submenu_page.find(DOOR_MANAGEMENT)->second.opt_submenu_string[0])
            {
                bool* ptr_automatic_opening = get_if<bool>(&(submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string[0].submenu_string));
                *ptr_automatic_opening = !(*ptr_automatic_opening);
                ptr_dd->automatic_opening = *ptr_automatic_opening;
                QtJsonConfigureData::get_instance()->write_json_file(AUTOMATIC_OPENING_CONFIG, *ptr_automatic_opening ? STATUS_ON : STATUS_OFF);
            }
            else if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SERVICES].submenu_page.find(DOOR_MANAGEMENT)->second.opt_submenu_string[1])
            {
                bool* auto_closing_doors_by_sensors = get_if<bool>(&(submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string[1].submenu_string));
                *auto_closing_doors_by_sensors = !(*auto_closing_doors_by_sensors);
                ptr_dd->auto_closing_doors_by_sensors = *auto_closing_doors_by_sensors;
                QtJsonConfigureData::get_instance()->write_json_file(AUTOMATIC_DOOR_CLOSING_BY_SENSORS_CONFIG, *auto_closing_doors_by_sensors ? STATUS_ON : STATUS_OFF);
            }
            else if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SERVICES].submenu_page.find(DOOR_MANAGEMENT)->second.opt_submenu_string[2])
            {
                bool* auto_closing_drs_when_leaving_vehicle = get_if<bool>(&(submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string[2].submenu_string));
                *auto_closing_drs_when_leaving_vehicle = !(*auto_closing_drs_when_leaving_vehicle);
                ptr_dd->auto_closing_drs_when_leaving_vehicle = *auto_closing_drs_when_leaving_vehicle;
                QtJsonConfigureData::get_instance()->write_json_file(AUTOMATIC_DOOR_CLOSING_WHEN_LEAVING_BUS_CONFIG, *auto_closing_drs_when_leaving_vehicle ? STATUS_ON : STATUS_OFF);
            }
            else if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SERVICES].submenu_page.find(DOOR_MANAGEMENT)->second.opt_submenu_string[3])
            {
                bool* auto_kneeling = get_if<bool>(&(submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string[3].submenu_string));
                *auto_kneeling = !(*auto_kneeling);
                ptr_dd->auto_kneeling = *auto_kneeling;
                QtJsonConfigureData::get_instance()->write_json_file(AUTOMATIC_KNEELING_CONFIG, *auto_kneeling ? STATUS_ON : STATUS_OFF);
            }
            else if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SERVICES].submenu_page.find(DOOR_MANAGEMENT)->second.opt_submenu_string[4])
            {
                bool* automatic_on_alarm = get_if<bool>(&(submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string[4].submenu_string));
                *automatic_on_alarm = !(*automatic_on_alarm);
                ptr_dd->automatic_on_alarm = *automatic_on_alarm;
                QtJsonConfigureData::get_instance()->write_json_file(AUTOMATIC_ON_OF_ALARM_SYSTEM_CONFIG, *automatic_on_alarm ? STATUS_ON : STATUS_OFF);
            }
            else if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SERVICES].submenu_page.find(DOOR_MANAGEMENT)->second.opt_submenu_string[5])
            {
                bool* sensors_presence_passenger_doorway = get_if<bool>(&(submenus[E_MT_SERVICES].submenu_page[DOOR_MANAGEMENT].opt_submenu_string[5].submenu_string));
                *sensors_presence_passenger_doorway = !(*sensors_presence_passenger_doorway);
                ptr_dd->sensors_presence_passenger_doorway = *sensors_presence_passenger_doorway;
                QtJsonConfigureData::get_instance()->write_json_file(DOORWAY_PASSENGER_SENSOR_CONFIG, *sensors_presence_passenger_doorway ? STATUS_ON : STATUS_OFF);
            }
        }
        else if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_SERVICES].submenu_page.find(WIPERS)->second)
        {
            auto _ptr = HmiHandler::getInstance();
            DD_Settings_t* ptr_dd = reinterpret_cast<DD_Settings_t*>(_ptr->get_data_from_msg(HMIHANDLER_DD_SETTINGS_ID));
            if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SERVICES].submenu_page.find(WIPERS)->second.opt_submenu_string[0])
            {
                bool* service_mode = get_if<bool>(&(submenus[E_MT_SERVICES].submenu_page[WIPERS].opt_submenu_string[0].submenu_string));
                *service_mode = !(*service_mode);
                ptr_dd->servece_mode = *service_mode;
            }
            else if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SERVICES].submenu_page.find(WIPERS)->second.opt_submenu_string[1])
            {
                bool* reset_number_activations = get_if<bool>(&(submenus[E_MT_SERVICES].submenu_page[WIPERS].opt_submenu_string[1].submenu_string));
                *reset_number_activations = !(*reset_number_activations);
                ptr_dd->reset_number_activations = *reset_number_activations;
            }
        }
        else if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_SERVICES].submenu_page.find(ADDITIONAL_FUNCTIONALITY)->second)
        {
            auto _ptr = HmiHandler::getInstance();
            DD_Settings_t* ptr_dd = reinterpret_cast<DD_Settings_t*>(_ptr->get_data_from_msg(HMIHANDLER_DD_SETTINGS_ID));
            if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SERVICES].submenu_page.find(ADDITIONAL_FUNCTIONALITY)->second.opt_submenu_string[0])
            {
                bool* removing_traffic_blocks = get_if<bool>(&(submenus[E_MT_SERVICES].submenu_page[ADDITIONAL_FUNCTIONALITY].opt_submenu_string[0].submenu_string));
                *removing_traffic_blocks = !(*removing_traffic_blocks);
                ptr_dd->removing_traffic_blocks = *removing_traffic_blocks;
            }
            else if(m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SERVICES].submenu_page.find(ADDITIONAL_FUNCTIONALITY)->second.opt_submenu_string[1])
            {
                bool* turbo_timer = get_if<bool>(&(submenus[E_MT_SERVICES].submenu_page[ADDITIONAL_FUNCTIONALITY].opt_submenu_string[1].submenu_string));
                *turbo_timer = !(*turbo_timer);
                ptr_dd->turbo_timer = *turbo_timer;
                QtJsonConfigureData::get_instance()->write_json_file("turbo_timer", *turbo_timer ? STATUS_ON : STATUS_OFF);
            }
        }
    }
    check_active_list(m_ptr_left_list[m_cached_list_pos]);
    CATCH_BLOCK
}

void newMenuItems::set_diap_param(bool _is_increase)
{
    TRY_BLOCK
    if (m_ptr_left_list[m_cached_list_pos]->opt_submenu_string[m_cached_param_pos].value_type != E_PT_DIAPASONE)
        return;

    if (m_cached_main_pos == E_MT_SETTINGS)
    {
         if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(HEATING_SYSTEM)->second)
        {
            auto _ptr = HmiHandler::getInstance();
            DD_Settings_t* ptr_dd = reinterpret_cast<DD_Settings_t*>(_ptr->get_data_from_msg(HMIHANDLER_DD_SETTINGS_ID));
            string* ptr_installation_temperature = get_if<string>(&(submenus[E_MT_SETTINGS].submenu_page[HEATING_SYSTEM].opt_submenu_string[0].submenu_string));
            int _temp = stoi(*ptr_installation_temperature);
            if (_is_increase)
                (_temp == submenus[E_MT_SETTINGS].submenu_page[HEATING_SYSTEM].opt_submenu_string[0].max_value.value_or(MAXIMUM_INSTALLATION_TEMPERATURE)) ? _temp : _temp++;
            else
                (_temp == submenus[E_MT_SETTINGS].submenu_page[HEATING_SYSTEM].opt_submenu_string[0].min_value.value_or(MINIMUM_INSTALLATION_TEMPERATURE)) ? _temp : _temp--;
            QtJsonConfigureData::get_instance()->write_json_file(INSTALLATION_TEMPERATURE_CONFIG, QString::number(_temp));
            *ptr_installation_temperature = to_string(_temp);
            ptr_dd->installation_temperature = _temp;
        }
        else if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(DASH_BOARD)->second)
        {
            if (m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(DASH_BOARD)->second.opt_submenu_string[E_MTSET_DASH_BRIGHT])
            {
                bool* ptr_auto_bright = get_if<bool>(&(submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string[E_MTSET_DASH_AUTO_BRIGHT].submenu_string));
                if (!(*ptr_auto_bright))
                {
                    string* ptr_bright = get_if<string>(&(submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string[E_MTSET_DASH_BRIGHT].submenu_string));
                    int _temp = stoi(*ptr_bright);
                    if (_is_increase)
                        _temp += (_temp >= submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string[E_MTSET_DASH_BRIGHT].max_value.value_or(MAXIMUM_VALUE_BRIGHTNESS)) ? 0 : 10;
                    else
                        _temp -= (_temp <= submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string[E_MTSET_DASH_BRIGHT].min_value.value_or(MINIMUM_VALUE_BRIGHTNESS)) ? 0 : 10;
                    QtJsonConfigureData::get_instance()->write_json_file("brightness", QString::number(_temp));
                    *ptr_bright = to_string(_temp);
                    set_brightness(QString::number(_temp));
                }
            }
        }
        else if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second)
        {
            auto _ptr = HmiHandler::getInstance();
            DD_Settings_t* ptr_dd = reinterpret_cast<DD_Settings_t*>(_ptr->get_data_from_msg(HMIHANDLER_DD_SETTINGS_ID));
            if (m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second.opt_submenu_string[2])
            {
                string* ptr_rain = get_if<string>(&(submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string[2].submenu_string));
                int _temp = stoi(*ptr_rain);
                if (_is_increase)
                    (_temp == submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string[2].max_value.value_or(MAXIMUM_VALUE_SENSITIVITY_RAIN)) ? _temp : _temp++;
                else
                    (_temp == submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string[2].min_value.value_or(MINIMUM_VALUE_SENSITIVITY_RAIN)) ? _temp : _temp--;
                QtJsonConfigureData::get_instance()->write_json_file(SENSOR_SENSITIVITY_TO_RAIN_CONFIG, QString::number(_temp));
                *ptr_rain = to_string(_temp);
                ptr_dd->rain_sensitivity = _temp;
            }
            else if (m_ptr_right_list[m_cached_param_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(LIGHT_RAIN_SENSOR)->second.opt_submenu_string[3])
            {
                string* ptr_light = get_if<string>(&(submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string[3].submenu_string));
                int _temp = stoi(*ptr_light);
                if (_is_increase)
                    (_temp == submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string[3].max_value.value_or(MAXIMUM_VALUE_SENSITIVITY_LIGHT)) ? _temp : _temp++;
                else
                    (_temp == submenus[E_MT_SETTINGS].submenu_page[LIGHT_RAIN_SENSOR].opt_submenu_string[3].min_value.value_or(MINIMUM_VALUE_SENSITIVITY_LIGHT)) ? _temp : _temp--;
                QtJsonConfigureData::get_instance()->write_json_file(SENSOR_SENSITIVITY_TO_LIGHT_CONFIG, QString::number(_temp));
                *ptr_light = to_string(_temp);
                ptr_dd->sensitivity_to_light = _temp;
            }
        }
        else if (m_ptr_left_list[m_cached_list_pos] == &submenus[E_MT_SETTINGS].submenu_page.find(CLIMATE_CONTROL_DRIVER_CAB)->second)
        {
            auto _ptr = HmiHandler::getInstance();
            DD_Settings_t* ptr_dd = reinterpret_cast<DD_Settings_t*>(_ptr->get_data_from_msg(HMIHANDLER_DD_SETTINGS_ID));
            string* ptr_installation_temperature = get_if<string>(&(submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].opt_submenu_string[0].submenu_string));
            int _temp = stoi(*ptr_installation_temperature);
            if (_is_increase)
                (_temp == submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].opt_submenu_string[0].max_value.value_or(MAXIMUM_INSTALLATION_TEMPERATURE)) ? _temp : _temp++;
            else
                (_temp == submenus[E_MT_SETTINGS].submenu_page[CLIMATE_CONTROL_DRIVER_CAB].opt_submenu_string[0].min_value.value_or(MINIMUM_INSTALLATION_TEMPERATURE)) ? _temp : _temp--;
            QtJsonConfigureData::get_instance()->write_json_file("installation_temperature_DC", QString::number(_temp));
            *ptr_installation_temperature = to_string(_temp);
            ptr_dd->driver_installation_temperature = _temp;
        }
    }
    check_active_list(m_ptr_left_list[m_cached_list_pos]);
    CATCH_BLOCK
}

void newMenuItems::change_cached_value(uint8_t* _ptr_cache, optional<uint8_t> _lower_limit, uint8_t _upper_limit, bool _dir)
{
    TRY_BLOCK
    if (_dir)
    {
        if (*_ptr_cache < _upper_limit)
            (*_ptr_cache)++;
        else
            *_ptr_cache = _lower_limit.value_or(0);
    }
    else
    {
        if (*_ptr_cache > _lower_limit.value_or(0))
            (*_ptr_cache)--;
        else
            *_ptr_cache = _upper_limit;
    }
    CATCH_BLOCK
}

void newMenuItems::set_brightness(QString _brightness)
{
    TRY_BLOCK
    uint8_t brightness_value = _brightness.toUInt();
    if (brightness_value % BRIGHTNESS_COMPARE_VALUE_10 != 0)
    {
        if (brightness_value < BRIGHTNESS_COMPARE_VALUE_10)
            brightness_value = 0;
        else
        {
            brightness_value /= BRIGHTNESS_COMPARE_VALUE_10;
            brightness_value++;
            brightness_value *= BRIGHTNESS_COMPARE_VALUE_10;
        }
    }
    brightness_value += BRIGHTNESS_VALUE_10;
    //TODO: SAVE TO JSON
    char brightness_str[4];
    if (brightness_value)
    {
        FILE* brightness_file = fopen(PATH_BRIGHTNESS_CONTROL, WRITE_MODE);
        if (brightness_file)
        {
            snprintf(brightness_str, sizeof(brightness_str), "%d", brightness_value);
            fwrite(brightness_str, sizeof(char), 4, brightness_file);
            fclose(brightness_file);
        }
    }
    CATCH_BLOCK
}

void newMenuItems::init_subscribe()
{
    TRY_BLOCK
    auto ptrnotifer = subscribe_notifer::get_instance();
    ptrnotifer->subscribe(HMIHANDLER_DD_INFO3_ID, this);
    CATCH_BLOCK
}
