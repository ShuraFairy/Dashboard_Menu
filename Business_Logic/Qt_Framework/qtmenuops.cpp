#include "qtmenuops.h"
#define BUTTON_REPEAT 2

static QString steering_activity;
static qreal engine_rpm_speed;
static SAS_t* sas_data;

using std::vector;
using namespace std;

mutex QtMenuOps::m_build_mutex;
QtMenuOps* QtMenuOps::m_ptr_instance(nullptr);

QtMenuOps::QtMenuOps(QObject* parent)
    : QObject{ parent }
    , map_menu_data()
    , dd_settings()
    , _init_config_data_update_status(false)
    , language_menu()
    , screen_state()
    , main_menu_pos()
    , list_menu_pos()
    , param_menu_pos()
{
    if (!m_ptr_instance)
        m_ptr_instance = this;
    json_configure_data = QtJsonConfigureData::get_instance();
    _init_config_data_update_status = json_configure_data->is_reachable();
    menu_handler = MenuHandler::get_instance();
    m_ptr_navigation = navigation::get_instance(menu_handler->get_menu_item_data());
    m_ptr_msgs_handler = HmiHandler::getInstance();
    _menu_items = menu_handler->init_menu_item_data();
    update_init_config_data();
    update_language_change(get_config_file_data("language_change"));
    init_subscribe();
    _menu_items->set_menu_drawer(this);
}

QtMenuOps::~QtMenuOps()
{
}

QString QtMenuOps::get_sensor_senitivity(QString sensor_type, QString sensitivity_value)
{
    TRY_BLOCK
    QString return_value;
    if (sensor_type == RAIN_SENSOR )
    {
        return_value = tr(SENSITIVITY_LEVEL_) + " ";
        if (sensitivity_value == "0" || sensitivity_value == "5")
            return_value += (sensitivity_value == "0") ? "0" : "5";
        else
            return_value += sensitivity_value;
    }
    else
        return_value = tr(SENSITIVITY_) + " " + sensitivity_value;

    return return_value;
    CATCH_BLOCK
}

QtMenuOps* QtMenuOps::getInstance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = new QtMenuOps;
    }
    return m_ptr_instance;
    CATCH_BLOCK
}

void QtMenuOps::initialize_menu_parameter_names()
{
    TRY_BLOCK
    submenu_window* ptr_page;
    m_main_menu_names.insert(0, tr("Parameters"));
    m_main_menu_names.insert(1, tr("Diagnostics"));
    m_main_menu_names.insert(2, tr("Settings"));
    m_main_menu_names.insert(3, tr("Services"));
    emit main_menu_names_changed();

    _menu_items->str_on = tr(STATUS_ON);
    _menu_items->str_off = tr(STATUS_OFF);

    _menu_items->submenus[E_MT_PARAMETERS].submenu_page.find(BRAKE_PADS_WEAR)->second.item_name = tr("Brake pads wear").toStdString();
    ptr_page = &(_menu_items->submenus[E_MT_PARAMETERS].submenu_page.find(ENGINE)->second);
    ptr_page->item_name = tr("Engine").toStdString();
    menu_string* ptr_raw_string = &ptr_page->opt_submenu_string[0];
    ptr_raw_string->param_name = tr("Coolant temperature");
    ptr_raw_string->uom = UOM_DEGREE_CELCIUS;
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Oil temperature");
    ptr_raw_string->uom = UOM_DEGREE_CELCIUS;
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Oil pressure");
    ptr_raw_string->uom = tr(" bar");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Instant fuel consumption");
    ptr_raw_string->uom = tr(" l/h", "Instant fuel consumption");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Average fuel consumption");
    ptr_raw_string->uom = tr(" l/100km", "Average fuel consumption");

    //TRANSMISSION
    ptr_page = &(_menu_items->submenus[E_MT_PARAMETERS].submenu_page.find(TRANSMISSION)->second);
    ptr_page->item_name = tr("Transmission").toStdString();
    ptr_raw_string = &ptr_page->opt_submenu_string[0];
    ptr_raw_string->param_name = tr("Oil Temperature");
    ptr_raw_string->uom = UOM_DEGREE_CELCIUS;
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Oil temperature in hydraulic retarder");
    ptr_raw_string->uom = UOM_DEGREE_CELCIUS;
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Output shaft speed");
    ptr_raw_string->uom = tr(" U/min");

    //BATTERY
    ptr_page = &(_menu_items->submenus[E_MT_PARAMETERS].submenu_page.find(BATTERY)->second);
    ptr_page->item_name = tr("Battery").toStdString();
    ptr_raw_string = &ptr_page->opt_submenu_string[0];
    ptr_raw_string->param_name = tr("Voltage");
    ptr_raw_string->uom = tr(" V");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Current1");
    ptr_raw_string->uom = tr(" A");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Current2");
    ptr_raw_string->uom = tr(" A");

    initialize_typemenu_items_names();
    //TODO: undo type
    set_type_of_vehicle(QString::number((_menu_items->vehicle_type > 0) ? _menu_items->vehicle_type : 2));
//    set_type_of_vehicle("2");

    // Wipers
    ptr_page = &(_menu_items->submenus[E_MT_PARAMETERS].submenu_page.find(WIPERS)->second);
    ptr_page->item_name = tr("Wipers").toStdString();
    ptr_raw_string = &ptr_page->opt_submenu_string[0];
    ptr_raw_string->param_name = tr("Washer fluid level");
    ptr_raw_string->uom = UOM_PERCENTAGE;
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Number of Operation");

    // Reagent Adblue
    ptr_page = &(_menu_items->submenus[E_MT_PARAMETERS].submenu_page.find(REAGENT_ADBLUE)->second);
    ptr_page->item_name = tr("Reagent AdBlue").toStdString();
    ptr_raw_string = &ptr_page->opt_submenu_string[0];
    ptr_raw_string->param_name = tr("AdBlue Level");
    ptr_raw_string->uom = UOM_PERCENTAGE;
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("AdBlue temperature");
    ptr_raw_string->uom = UOM_DEGREE_CELCIUS;
    CATCH_BLOCK
}

void QtMenuOps::initialize_menu_diagnostics_names()
{
    TRY_BLOCK
    auto& ptr_map = menu_handler->get_menu_item_data()->submenus[E_MT_DIAGNOSTICS].submenu_page;
    ptr_map.find(FAILURES)->second.item_name =  tr("Failures").toStdString();
    ptr_map.find(EMERGENCY_CRANES)->second.item_name =  tr("Emergency Cranes").toStdString();
    ptr_map.find(DOOR_VALVES)->second.item_name =  tr("Door Valves").toStdString();
    ptr_map.find(DOOR_SENSORS)->second.item_name =  tr("Door Sensors").toStdString();
    ptr_map.find(EMERGENCY_HAMMERS)->second.item_name =  tr("Emergency Hammers").toStdString();
    ptr_map.find(FIRE_EXTINGUISHERS)->second.item_name =  tr("Fire Extinguishers").toStdString();
    ptr_map.find(HEATERS)->second.item_name =  tr("Heaters").toStdString();
    ptr_map.find(HEATING_SYSTEM_VALVES)->second.item_name =  tr("Heating System Valves").toStdString();
    ptr_map.find(LIGHTING_EQUIPEMENTS)->second.item_name =  tr("Lighting Equipments").toStdString();

    /* Failures */
//TODO: ADD NO FAILURES
//    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("No Failures"), VISIBILITY_FALSE, NA_RANGE}, &QtMenuOps::set_menu_diagnostics_failures_no_failures));
    menu_handler->get_menu_item_data()->str_recomendation = tr("Please, contact your service center");

    menu_string* ptr_data = &ptr_map.find(FAILURES)->second.opt_submenu_string[0];
    ptr_data->param_name = tr("Fire Extinguisher System");
    FailureModule* _ptr_temp = get_if<FailureModule>(&ptr_data->submenu_string);
    _ptr_temp->error_code[0].error_code_description = (tr("FIRE DETECTOR IN E-PANEL DISABLED")).toStdString();
    _ptr_temp->error_code[1].error_code_description = (tr("NO COMMUNICATION WITH FIRE DETECTOR in E-PANEL")).toStdString();
    _ptr_temp->error_code[2].error_code_description = (tr("FIRE DETECTOR SHORT CIRCUIT IN E-PANEL!")).toStdString();
    _ptr_temp->error_code[3].error_code_description = (tr("THE FIRE DETECTOR IN THE MOTOR COMPARTMENT IS DISABLED!")).toStdString();
    _ptr_temp->error_code[4].error_code_description = (tr("NO COMMUNICATION WITH THE FIRE DETECTOR IN THE MOTOR COMPARTMENT!")).toStdString();
    _ptr_temp->error_code[5].error_code_description = (tr("SHORT CIRCUIT OF THE FIRE DETECTOR IN THE MOTOR COMPARTMENT!")).toStdString();
    _ptr_temp->error_code[6].error_code_description = (tr("THE FIRE EXTINGUISHER IN THE EPANEL IS OFF!")).toStdString();
    _ptr_temp->error_code[7].error_code_description = (tr("THERE IS NO COMMUNICATION WITH THE FIRE EXTINGUISHER IN THE E-PANEL!")).toStdString();
    _ptr_temp->error_code[8].error_code_description = (tr("FIRE EXTINGUISHER IN MOTOR COMPARTMENT IS OFF!")).toStdString();
    _ptr_temp->error_code[9].error_code_description = (tr("NO COMMUNICATION WITH THE FIRE EXTINGUISHER IN THE MOTOR COMPARTMENT!")).toStdString();
    ptr_data++;

    ptr_data->param_name = tr("Brake System");
    _ptr_temp = get_if<FailureModule>(&ptr_data->submenu_string);
    _ptr_temp->error_code[0].error_code_description = (tr("No communication with brake ECU!")).toStdString();
    _ptr_temp->error_code[1].error_code_description = (tr("There are active brake system errors!")).toStdString();
    _ptr_temp->error_code[2].error_code_description = (tr("Brake system mainfunction!")).toStdString();
    ptr_data++;

    ptr_data->param_name = tr("Pneumatic System");
    _ptr_temp = get_if<FailureModule>(&ptr_data->submenu_string);
    _ptr_temp->error_code[0].error_code_description = (tr("There is no communication with the pneumatic system ECU")).toStdString();
    _ptr_temp->error_code[1].error_code_description = (tr("There are active errors in the Pneumatic System")).toStdString();
    _ptr_temp->error_code[2].error_code_description = (tr("Air Suspension failure")).toStdString();
    ptr_data++;

    ptr_data->param_name = tr("Propulsion System");
    _ptr_temp = get_if<FailureModule>(&ptr_data->submenu_string);
    _ptr_temp->error_code[0].error_code_description = (tr("There is no communication with the ECU of the Power plant")).toStdString();
    _ptr_temp->error_code[1].error_code_description = (tr("There are active errors on the Power plant")).toStdString();
    _ptr_temp->error_code[2].error_code_description = (tr("Engine Protection command")).toStdString();
    ptr_data++;

    ptr_data->param_name = tr("Transmission");
    _ptr_temp = get_if<FailureModule>(&ptr_data->submenu_string);
    _ptr_temp->error_code[0].error_code_description = (tr("No communication with Transmission ECU")).toStdString();
    _ptr_temp->error_code[1].error_code_description = (tr("There are active errors in the Transmission")).toStdString();
    _ptr_temp->error_code[2].error_code_description = (tr("Automatic Transmission Malfunction")).toStdString();
    ptr_data++;

    ptr_data->param_name = tr("Tachograph");
    _ptr_temp = get_if<FailureModule>(&ptr_data->submenu_string);
    _ptr_temp->error_code[0].error_code_description = (tr("No connection to Tachograph")).toStdString();
    _ptr_temp->error_code[1].error_code_description = (tr("Critical Tachograph Error")).toStdString();
    ptr_data++;

    ptr_data->param_name = tr("Tyre Pressure and Temperature Monitoring system");
    _ptr_temp = get_if<FailureModule>(&ptr_data->submenu_string);
    _ptr_temp->error_code[0].error_code_description = (tr("No communication with Tyre Pressure and Temperature monitoring system")).toStdString();
    _ptr_temp->error_code[1].error_code_description = (tr("There are active errors in the Tire Pressure and temerature monitoring system")).toStdString();
    ptr_data++;

    ptr_data->param_name = tr("ADAS Driver Assistance System");
    _ptr_temp = get_if<FailureModule>(&ptr_data->submenu_string);
    _ptr_temp->error_code[0].error_code_description = (tr("No communication with ADAS driver assistance ECU")).toStdString();
    submenu_window* ptr_page = &(_menu_items->submenus[E_MT_DIAGNOSTICS].submenu_page.find(LIGHTING_EQUIPEMENTS)->second);
    menu_string* ptr_raw_string = &ptr_page->opt_submenu_string[0];
    ptr_raw_string->param_name = tr("Testing of Lighting equipments");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Position Lights");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Low Beam");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("High Beam");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Turn Signals");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("DLR");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Front Fog Lamp");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Rear Fog Lamp");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Reverse Lights");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Lights");
    CATCH_BLOCK
}
void QtMenuOps::initialize_typemenu_items_names()
{
    //PNEUMATIC
    auto ptr_page = &(_menu_items->submenus[E_MT_PARAMETERS].submenu_page.find(PNEUMATIC_SYSTEM)->second);
    ptr_page->item_name = tr("Pneumatic System").toStdString();
    auto ptr_raw_string = &ptr_page->opt_submenu_string[0];
    ptr_raw_string->param_name = (_menu_items->vehicle_type == 3) ? tr("Intermediate axle breaking circuit") : tr("Rear axle breaking circuit");
    ptr_raw_string->uom = tr(" bar");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Front axle breaking circuit");
    ptr_raw_string->uom = tr(" bar");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Parking Brake");
    ptr_raw_string->uom = tr(" bar");
    ptr_raw_string++;
    ptr_raw_string->param_name = (_menu_items->vehicle_type == 3) ? tr("Rear axle breaking circuit") : tr("Auxiliary Equipment");
    ptr_raw_string->uom = tr(" bar");
    ptr_raw_string++;
    ptr_raw_string->param_name = tr("Auxiliary Equipment");
//    ptr_raw_string->visibility = (_menu_items->vehicle_type == 3);
    ptr_raw_string->uom = tr(" bar");

    ptr_page = &(_menu_items->submenus[E_MT_PARAMETERS].submenu_page.find(TIRE_PRESSURE_AND_TEMPERATURE)->second);
    ptr_page->item_name = tr("Tyre pressure and temperature").toStdString();
    for (auto& it : ptr_page->opt_submenu_string)
        it.uom = tr(" bar");
}
void QtMenuOps::initialize_menu_settings_names()
{
    TRY_BLOCK
    vector<pair<QStringList, set_operation>> init_menu_data_names;
    auto& ptr_map = menu_handler->get_menu_item_data()->submenus[E_MT_SETTINGS].submenu_page;
    ptr_map.find(HEATING_SYSTEM)->second.item_name =  tr("Heating system").toStdString();
    ptr_map.find(DASH_BOARD)->second.item_name =  tr("Dashboard").toStdString();
    ptr_map.find(LIGHT_RAIN_SENSOR)->second.item_name =  tr("Light and rain sensor").toStdString();
    ptr_map.find(CLIMATE_CONTROL_DRIVER_CAB)->second.item_name =  tr("Climate control in driver cab").toStdString();

    menu_string* ptr_string = &(ptr_map.find(HEATING_SYSTEM)->second.opt_submenu_string[0]);
    ptr_string->param_name = tr("Installation Temperature");
    ptr_string->uom = UOM_DEGREE_CELCIUS;
    ptr_string++;
    ptr_string->param_name = tr("Heater errors reset");
    ptr_string++;
    ptr_string->param_name = tr("Heater Release");

    ptr_string = &(ptr_map.find(DASH_BOARD)->second.opt_submenu_string[0]);
    ptr_string->param_name = tr("Automatic Adjustment Brightness");
    ptr_string++;
    ptr_string->param_name = tr("Brightness");
    ptr_string++;
    ptr_string->param_name = tr("Language Change");

    // Light and Rain Sensor
    ptr_string = &(ptr_map.find(LIGHT_RAIN_SENSOR)->second.opt_submenu_string[0]);
    ptr_string->param_name = tr("Automatic low Beam");
    ptr_string++;
    ptr_string->param_name = tr("Automatic wiper Operation");
    ptr_string++;
    ptr_string->param_name = tr("Sensor Sensitivity To Rain");
    ptr_string++;
    ptr_string->param_name = tr("Sensor Sensitivity To Light");

    ptr_string = &(ptr_map.find(CLIMATE_CONTROL_DRIVER_CAB)->second.opt_submenu_string[0]);
    ptr_string->param_name = tr("Installation temperature");
    ptr_string->uom = UOM_DEGREE_CELCIUS;
    ptr_string++;
    ptr_string->param_name = tr("Coolant damper");
    ptr_string++;
    ptr_string->param_name = tr("Air Intake");
    menu_handler->get_menu_item_data()->str_close = tr("CLOSE");
    menu_handler->get_menu_item_data()->str_open = tr("OPEN");
    CATCH_BLOCK
}

void QtMenuOps::initialize_menu_services_names()
{
    TRY_BLOCK
    QString menu_range;
    QString menu_dtc_init_value;
    QString password_value;
    QString off_status;
    QString password_language_change;
    QString config_file_value;

    off_status = tr("OFF");

    menu_dtc_init_value = QString::fromStdString(INIT_VALUE) + MENU_RANGE_SEPERATOR // SA
        + QString::fromStdString(INIT_VALUE) + MENU_RANGE_SEPERATOR // SPN
        + QString::fromStdString(INIT_VALUE) + MENU_RANGE_SEPERATOR // FMI
        + QString::fromStdString(INIT_VALUE) + MENU_RANGE_SEPERATOR // No Of Repetations
        + QString::fromStdString(VISIBILITY_FALSE); // Visibility

    vector<pair<QStringList, set_operation>> init_menu_data_names;
    auto& ptr_map = menu_handler->get_menu_item_data()->submenus[E_MT_SERVICES].submenu_page;
    ptr_map.find(DOOR_MANAGEMENT)->second.item_name = tr("Door Management").toStdString();
    ptr_map.find(WIPERS)->second.item_name =  tr("Wipers").toStdString();
    ptr_map.find(DIAGNOSTICS_TROUBLE_CODE)->second.item_name =  tr("Diagnostic trouble code").toStdString();
    ptr_map.find(ADDITIONAL_FUNCTIONALITY)->second.item_name =  tr("Additional Functionality").toStdString();
    ptr_map.find(STEERING_ANGLE_SENSOR)->second.item_name =  tr("Steering angle sensor").toStdString();
    ptr_map.find(DATA_SOURCE)->second.item_name =  tr("Data Source").toStdString();
    ptr_map.find(CHANGE_PASSWORD)->second.item_name =  tr("Change Password").toStdString();
    ptr_map.find(SOFTWARE_VERSION)->second.item_name =  tr("Software Version").toStdString();

    menu_string* ptr_string = &(ptr_map.find(DOOR_MANAGEMENT)->second.opt_submenu_string[0]);
    ptr_string->param_name = tr("Automatic Opening");
    ptr_string++;
    ptr_string->param_name = tr("Automatic door closing by sensors");
    ptr_string++;
    ptr_string->param_name = tr("Automatic door closing when leaving the bus");
    ptr_string++;
    ptr_string->param_name = tr("Automatic Kneeling");
    ptr_string++;
    ptr_string->param_name = tr("Automatic on of the alarm system");
    ptr_string++;
    ptr_string->param_name = tr("Doorway passenger sensor");

    ptr_string = &(ptr_map.find(WIPERS)->second.opt_submenu_string[0]);
    ptr_string->param_name = tr("Service Mode");
    ptr_string++;
    ptr_string->param_name = tr("Setting the number of operations to zero");

    menu_handler->get_menu_item_data()->str_advice = tr("Advice : Please contact Service Centre");
    // Diagnostic Trouble Code //TODO:
//    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("No trouble code (DTC)"), VISIBILITY_FALSE, NA_RANGE}, &QtMenuOps::set_menu_services_dtc_no_trouble_code));
//    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("DTC Group Count"), VISIBILITY_FALSE, NA_RANGE}, &QtMenuOps::set_menu_services_dtc_error_count));

    ptr_string = &(ptr_map.find(DIAGNOSTICS_TROUBLE_CODE)->second.opt_submenu_string[0]);
    ptr_string->param_name = tr("Propulsion System");
    DtcModule* ptr_module = get_if<DtcModule>(&(ptr_string->submenu_string));
    int i = 0;
    for (auto& it : ptr_module->trouble_code)
        it.trouble_code_recommendations = tr("Propulsion System DTC ").toStdString() + to_string(++i);
    ptr_string++;

    ptr_string->param_name = tr("Transmission System");
    ptr_module = get_if<DtcModule>(&(ptr_string->submenu_string));
    i = 0;
    for (auto& it : ptr_module->trouble_code)
        it.trouble_code_recommendations = tr("Transmission System DTC ").toStdString() + to_string(++i);
    ptr_string++;

    ptr_string->param_name = tr("Brake System");
    ptr_module = get_if<DtcModule>(&(ptr_string->submenu_string));
    i = 0;
    for (auto& it : ptr_module->trouble_code)
        it.trouble_code_recommendations = tr("Brake System DTC ").toStdString() + to_string(++i);
    ptr_string++;

    ptr_string->param_name = tr("Pneumatic System");
    ptr_module = get_if<DtcModule>(&(ptr_string->submenu_string));
    i = 0;
    for (auto& it : ptr_module->trouble_code)
        it.trouble_code_recommendations = tr("Pneumatic System DTC ").toStdString() + to_string(++i);
    ptr_string++;

    ptr_string->param_name = tr("Tachograph System");
    ptr_module = get_if<DtcModule>(&(ptr_string->submenu_string));
    i = 0;
    for (auto& it : ptr_module->trouble_code)
        it.trouble_code_recommendations = tr("Tachograph System DTC ").toStdString() + to_string(++i);
    ptr_string++;

    ptr_string->param_name = tr("Tire Pressure Monitoring System");
    ptr_module = get_if<DtcModule>(&(ptr_string->submenu_string));
    i = 0;
    for (auto& it : ptr_module->trouble_code)
        it.trouble_code_recommendations = tr("Tire Pressure Monitoring System DTC ").toStdString() + to_string(++i);

    // Additional Functionality
    ptr_string = &(ptr_map.find(ADDITIONAL_FUNCTIONALITY)->second.opt_submenu_string[0]);
    ptr_string->param_name = tr("Motion deblocked");
    ptr_string++;
    ptr_string->param_name = tr("Turbotimer");

    // Steering Angle Sensor
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("n degree"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_streering_sensor_n_degree));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("m value"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_streering_sensor_m_value));
    menu_range = tr("The regulatory process") + MENU_RANGE_SEPERATOR + tr("Sub-item 1 - Press OK on the steering wheel") + MENU_RANGE_SEPERATOR + tr("Sub-item 2 - Turn on the Power plant") + MENU_RANGE_SEPERATOR
        + tr("Sub-item 3 - Straighten the wheels and press OK");
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Steering Angle Sensor Instructions"), MENU_NA_VALUE, menu_range}, &QtMenuOps::set_menu_services_streering_sensor_instructions));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Steering Status"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_streering_sensor_status));

    // Data Source
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Template1 Droplist"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_tempelate1_droplist));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Template2 Droplist"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_tempelate2_droplist));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Template3 Droplist"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_tempelate3_droplist));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Template4 Droplist"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_tempelate4_droplist));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Template5 Droplist"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_tempelate5_droplist));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Template6 Droplist"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_tempelate6_droplist));

    // Change Password
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Valid Password"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_change_pwd_valid_password));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("New Password"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_change_pwd_new_password));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Confirmation"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_change_pwd_confirmation_password));
    password_value = get_config_file_data("new_password");
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Enter your password"), password_value, NA_RANGE}, &QtMenuOps::set_menu_services_password_data));

    // Software Version
    ptr_string = &(ptr_map.find(SOFTWARE_VERSION)->second.opt_submenu_string[0]);
    ptr_string->param_name = tr("Instrument Cluster");
    ptr_string++;
    ptr_string->param_name = tr("Body Controller");
    ptr_string++;
    ptr_string->param_name = tr("Cab Controller");
    ptr_string++;
    ptr_string->param_name = tr("Engine Control Panel");
    /*
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Instrument Cluster"), QString::fromStdString(*str_version), NA_RANGE}, &QtMenuOps::set_menu_services_software_version_ec12));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Body Controller"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_software_version_cc));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Cab Controller"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_software_version_redp));
    init_menu_data_names.emplace_back(make_pair<QStringList, set_operation>({tr("Engine Control Panel"), MENU_NA_VALUE, NA_RANGE}, &QtMenuOps::set_menu_services_software_version_res));
*/
    // PASSWORD Language Change
    password_language_change = tr("Valid Password not matching with original password");
    set_valid_password_not_match(password_language_change);
    password_language_change = tr("New Password not matching with the conifrmation password");
    set_new_password_not_match(password_language_change);
    password_language_change = tr("New Password has been updated");
    set_new_password_update(password_language_change);
    password_language_change = tr("New Password updation failed due to technical issue");
    set_new_password_update_failed(password_language_change);

    for(auto& it : init_menu_data_names)
    {
        (((QtMenuOps*)this)->*it.second)({it.first});
    }
    CATCH_BLOCK
}

const int& QtMenuOps::get_screen_state() const
{
    TRY_BLOCK
        return screen_state;
    CATCH_BLOCK
}

void QtMenuOps::set_screen_state(const int& _newState)
{
    TRY_BLOCK
        if (screen_state != _newState)
    {
        screen_state = _newState;
        emit screen_state_changed();
    }
    CATCH_BLOCK
}

const int& QtMenuOps::get_main_menu_pos() const
{
    TRY_BLOCK
        return main_menu_pos;
    CATCH_BLOCK
}

void QtMenuOps::set_main_menu_pos(const int& _newState)
{
    TRY_BLOCK
        if (main_menu_pos != _newState)
    {
        main_menu_pos = _newState;
        emit main_menu_pos_changed();
    }
    CATCH_BLOCK
}

const int& QtMenuOps::get_list_menu_pos() const
{
    TRY_BLOCK
        return list_menu_pos;
    CATCH_BLOCK
}

void QtMenuOps::set_list_menu_pos(const int& _newState)
{
    TRY_BLOCK
        if (list_menu_pos != _newState)
    {
        list_menu_pos = _newState;
        emit list_menu_pos_changed();
    }
    CATCH_BLOCK
}

const int& QtMenuOps::get_param_menu_pos() const
{
    TRY_BLOCK
        return param_menu_pos;
    CATCH_BLOCK
}

void QtMenuOps::set_param_menu_pos(const int& _newState)
{
    TRY_BLOCK
        if (param_menu_pos != _newState)
    {
        param_menu_pos = _newState;
        emit param_menu_pos_changed();
    }
    CATCH_BLOCK
}

void QtMenuOps::update_language(int lang)
{
    TRY_BLOCK
    switch (lang) {
    case LANGUAGE_RUS:
        _translator.load(MENU_RU_FILENAME, TRANSLATOR_DIRECTORY);
        QGuiApplication::installTranslator(&_translator);
        break;
    case LANGUAGE_ENG:
        _translator.load(MENU_RU_FILENAME, TRANSLATOR_DIRECTORY);
        QGuiApplication::removeTranslator(&_translator);
        break;
    default:
        QGuiApplication::removeTranslator(&_translator);
        break;
    }
    CATCH_BLOCK
}

void QtMenuOps::set_popup(QtPopUpWindow* ptrpopupwindow)
{
    TRY_BLOCK
    _ptrpopupwindow = ptrpopupwindow;
    m_ptr_navigation->set_popup(ptrpopupwindow);
    CATCH_BLOCK
}

void QtMenuOps::update_gui()
{
}


bool QtMenuOps::update_info(uint32_t _id)
{
    TRY_BLOCK
    if (_state == QMLSTATE_MENU || _state == QMLSTATE_NORMAL)
    {
        // UDS Start
        bool menu_screen_vis = true;
        set_menu_screen_visibility(menu_screen_vis);

        string element_value;
        switch (_id)
        {
        case HMIHANDLER_FB1_ID:
            if (m_ptr_msgs_handler->get_ptr_to_msg(HMIHANDLER_FB1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
            {
                FB1_t* fb1_msg = nullptr;
                uint8_t _can_value_uint8 = 0;

                fb1_msg = reinterpret_cast<FB1_t*>(m_ptr_msgs_handler->get_data_from_msg(HMIHANDLER_FB1_ID));
                _can_value_uint8 = (uint8_t)(fb1_msg->EEPROM_par_bus_model);

                _vehicle_type = QString::number(menu_handler->_vehicle_details[(VehicleName)_can_value_uint8]);
                menu_handler->_menu_data.vehicle_type = menu_handler->_vehicle_details[(VehicleName)_can_value_uint8];
                menu_handler->_menu_data.vehicle_name = (VehicleName)_can_value_uint8;
                set_type_of_vehicle(_vehicle_type);
            }
            break;
        case HMIHANDLER_SAS_ID:
            if (m_ptr_msgs_handler->get_ptr_to_msg(HMIHANDLER_SAS_ID)->get_state() == CAN_MESSAGE_STATE_OK)
            {
                string* ptr_data = get_if<string>(&(_menu_items->submenus[E_MT_SERVICES].submenu_page[STEERING_ANGLE_SENSOR].submenu_string[0]));
                element_value = *ptr_data;
                if (update_menudata(element_value, N_DEGREE))
                    set_menu_services_streering_sensor_n_degree(_temp_menu_data);

                ptr_data = get_if<string>(&(_menu_items->submenus[E_MT_SERVICES].submenu_page[STEERING_ANGLE_SENSOR].submenu_string[1]));
                element_value = *ptr_data;
                if (update_menudata(element_value, M_VALUE))
                    set_menu_services_streering_sensor_m_value(_temp_menu_data);
            }
            break;
        }
    return true;
    }
    return false;
    CATCH_BLOCK
}

void QtMenuOps::init_subscribe()
{
    TRY_BLOCK
    auto ptrnotifer = subscribe_notifer::get_instance();
    ptrnotifer->subscribe(HMIHANDLER_FB1_ID, this);
    ptrnotifer->subscribe(HMIHANDLER_SAS_ID, this);
    CATCH_BLOCK
}

void QtMenuOps::qml_responses(int value)
{
    TRY_BLOCK
    QTimer* timer_2;
    QmlState state = (QmlState)value;
    QString send_key;
    QString receive_config_value;
    _state = state;

    switch (state) {
    case QmlState::QMLSTATE_INPROGRESS:
        qDebug() << "Loading In Progress Inside Menuops" << Qt::endl;
        break;
    case QmlState::QMLSTATE_LOADING_COMPLETED:
        qDebug() << "Loading Completed" << Qt::endl;
        timer_2 = new QTimer();
        connect(timer_2, &QTimer::timeout, [=] {
            _state = QmlState::QMLSTATE_NORMAL;
            timer_2->stop();
            delete timer_2;
        });
        timer_2->start(2000);

        send_key = "language_change";
        receive_config_value = get_config_file_data(send_key);
        update_language_change(receive_config_value);
        break;
    case QmlState::QMLSTATE_NORMAL:
        send_key = "language_change";
        receive_config_value = get_config_file_data(send_key);
        update_language_change(receive_config_value);
        break;
    case QmlState::QMLSTATE_MENU:
        break;
    default:
        break;
    }
    CATCH_BLOCK
}

void QtMenuOps::reset_average_fuel_consumption_data()
{
    TRY_BLOCK
    string reset_avg_fuel_consumption = "0";
    reset_avg_fuel_consumption  += UOM_KM;
    update_menudata(reset_avg_fuel_consumption, AVG_FUEL_CONSUMPTION);
    CATCH_BLOCK
}

void QtMenuOps::qml_menu_responses(bool value)
{
    TRY_BLOCK
    bool is_inside_parameter_menu = false;
    is_inside_parameter_menu = value;
    if (is_inside_parameter_menu == true) {
        // Timer Start
        _timer_id = startTimer(10);
    } else if (is_inside_parameter_menu == false) {
        // Timer Stop
        killTimer(_timer_id);
    }
    CATCH_BLOCK
}

bool QtMenuOps::update_menudata(string element_value, QString key_data)
{
    TRY_BLOCK
    _temp_menu_data.clear();
    lock_guard lock(_mtx_map_menu_data);
    if (map_menu_data.find(key_data) != map_menu_data.end()) {              // Check if the key exists in map_menu_data
        _temp_menu_data = map_menu_data[key_data];           // Get the value_data associated with the key
        if (!_temp_menu_data.isEmpty()) {                                        // Check if value_data is not empty
            auto& first_element = _temp_menu_data.first();                     // Get the first element of the value_data
            if (!first_element.isEmpty() && first_element.size() > 1)       // Check if the first element is not empty
            {
                if (first_element.size() > 1)
                    (first_element)[1] = QString::fromStdString(element_value);   // Update the first element's first item with element_value
                return true;
            }
        }
    }
    return false;
    CATCH_BLOCK
}

const QString& QtMenuOps::get_type_of_vehicle() const
{
    TRY_BLOCK
    return _type_of_vehicle;
    CATCH_BLOCK
}

void QtMenuOps::set_type_of_vehicle(const QString& newType_of_vehicle)
{
    TRY_BLOCK
    if (_type_of_vehicle == newType_of_vehicle)
        return;
    _type_of_vehicle = newType_of_vehicle;
    initialize_typemenu_items_names();
    emit type_of_vehicle_changed();
    CATCH_BLOCK
}

void QtMenuOps::steering_angle_sensor_timer_slot()
{
    TRY_BLOCK
    QList<QStringList>* temp_menu_data;
    QStringList* second_element;
    static bool first_step_completed = false;
    static bool second_step_completed = false;
    static bool third_step_completed = false;
    static uint8_t sas_calibrated_value = 255;

    EEC1_t* ptr_eec1 = reinterpret_cast<EEC1_t*>(m_ptr_msgs_handler->get_data_from_msg(HMIHANDLER_EEC1_ID));
    qreal _temp_speed = round(ptr_eec1->eng_speed * ENGINESPEED_FACTOR);

    engine_rpm_speed = _temp_speed;
    if (engine_rpm_speed > 0) {
        if (steering_activity == "START_CALIBRATION" && !first_step_completed && !second_step_completed) {
            uint64_t ptr_data = 0;
            uint8_t* frame = reinterpret_cast<uint8_t*>(ptr_data);
            frame[0] = 0xFF;
            frame[1] = 0xFF;
            frame[2] = 0xAA;
            frame[3] = 0xFF;
            frame[4] = 0xAA;
            frame[5] = 0x55;
            frame[6] = 0xFF;
            frame[7] = 0x4F;
            
            m_ptr_msgs_handler->add_new_data(HMIHANDLER_SAS_ID, CAN_MESSAGE_STATE_OK, ptr_data);
            second_step_completed = true;
            temp_menu_data = &map_menu_data[STEERING_ANGLE_STATUS];
            second_element = &temp_menu_data[0][0];
            second_element[0][1] = "SECOND_STEP_COMPLETED";
            set_menu_services_streering_sensor_status(map_menu_data[STEERING_ANGLE_STATUS]);
        }

        sas_calibrated_value = sas_data->sas_calibrated;
        if (first_step_completed && second_step_completed && !third_step_completed
            && steering_activity == "STOP_CALIBRATION") {
            if (sas_calibrated_value == 0) {
                uint64_t ptr_data = 0;
                uint8_t* frame = reinterpret_cast<uint8_t*>(ptr_data);
                frame[0] = 0xFF;
                frame[1] = 0xFF;
                frame[2] = 0xAA;
                frame[3] = 0xFF;
                frame[4] = 0x0F;
                frame[5] = 0xF0;
                frame[6] = 0xFF;
                frame[7] = 0x4F;
                m_ptr_msgs_handler->add_new_data(HMIHANDLER_SAS_ID, CAN_MESSAGE_STATE_OK, ptr_data);
                third_step_completed = true;
                temp_menu_data = &map_menu_data[STEERING_ANGLE_STATUS];
                second_element = &temp_menu_data[0][0];
                second_element[0][1] = "THIRD_STEP_COMPLETED";
                set_menu_services_streering_sensor_status(map_menu_data[STEERING_ANGLE_STATUS]);
                first_step_completed = false;
                second_step_completed = false;
                third_step_completed = false;
            }
        }
        if (steering_activity == "STOP_TIMER" && _timer_steering_angle_sensor->isActive() == true) {
            _timer_steering_angle_sensor->stop();
            delete _timer_steering_angle_sensor;
        }
    }
    CATCH_BLOCK
}

void QtMenuOps::steering_angle_sensor_handler(QString activity)
{
    TRY_BLOCK
    steering_activity = activity;
    sas_data = reinterpret_cast<SAS_t*>(m_ptr_msgs_handler->get_data_from_msg(HMIHANDLER_SAS_ID));

    _timer_steering_angle_sensor = new QTimer(this);
    if (activity == "START_CALIBRATION" && _timer_steering_angle_sensor->isActive() == false) {
        connect(_timer_steering_angle_sensor, SIGNAL(timeout()), this, SLOT(steering_angle_sensor_timer_slot()));
        _timer_steering_angle_sensor->start(2000);
    }
    if (activity == "PRESSED_BACK" && _timer_steering_angle_sensor->isActive() == true) {
        _timer_steering_angle_sensor->stop();
        delete _timer_steering_angle_sensor;
    }
    CATCH_BLOCK
}

bool QtMenuOps::get_menu_screen_visibility() const
{
    TRY_BLOCK
    return _menu_screen_visibility;
    CATCH_BLOCK
}

void QtMenuOps::set_menu_screen_visibility(bool newMenu_screen_visibility)
{
    TRY_BLOCK
    if (_menu_screen_visibility == newMenu_screen_visibility)
        return;
    qDebug("set visibility\n");
    _menu_screen_visibility = newMenu_screen_visibility;
    emit menu_screen_visibility_changed();
    CATCH_BLOCK
}

const QString& QtMenuOps::get_valid_password_not_match() const
{
    TRY_BLOCK
    return _valid_password_not_match;
    CATCH_BLOCK
}

void QtMenuOps::set_valid_password_not_match(const QString& newValid_password_not_match)
{
    TRY_BLOCK
    if (_valid_password_not_match == newValid_password_not_match)
        return;
    _valid_password_not_match = newValid_password_not_match;
    emit valid_password_not_match_changed();
    CATCH_BLOCK
}

const QString& QtMenuOps::get_new_password_not_match() const
{
    TRY_BLOCK
    return _new_password_not_match;
    CATCH_BLOCK
}

void QtMenuOps::set_new_password_not_match(const QString& newNew_password_not_match)
{
    TRY_BLOCK
    if (_new_password_not_match == newNew_password_not_match)
        return;
    _new_password_not_match = newNew_password_not_match;
    emit new_password_not_match_changed();
    CATCH_BLOCK
}

const QString& QtMenuOps::get_new_password_update() const
{
    TRY_BLOCK
    return _new_password_update;
    CATCH_BLOCK
}

void QtMenuOps::set_new_password_update(const QString& newNew_password_update)
{
    TRY_BLOCK
    if (_new_password_update == newNew_password_update)
        return;
    _new_password_update = newNew_password_update;
    emit new_password_update_changed();
    CATCH_BLOCK
}

const QString& QtMenuOps::get_new_password_update_failed() const
{
    TRY_BLOCK
    return _new_password_update_failed;
    CATCH_BLOCK
}

void QtMenuOps::set_new_password_update_failed(const QString& newNew_password_update_failed)
{
    TRY_BLOCK
    if (_new_password_update_failed == newNew_password_update_failed)
        return;
    _new_password_update_failed = newNew_password_update_failed;
    emit new_password_update_failed_changed();
    CATCH_BLOCK
}

void QtMenuOps::update_init_config_data()
{
    TRY_BLOCK
    bool status = false;
    QString config_value_bool;

    DD_Settings_t* ptr_dd = reinterpret_cast<DD_Settings_t*>(m_ptr_msgs_handler->get_data_from_msg(HMIHANDLER_DD_SETTINGS_ID));
    ptr_dd->installation_temperature = json_configure_data->get_config_data(INSTALLATION_TEMPERATURE_CONFIG).toUInt(&status);

    config_value_bool = json_configure_data->get_config_data(AUTOMATIC_LOW_BEAM_CONFIG);
    ptr_dd->auto_settings_low_beam = (config_value_bool == STATUS_ON);

    config_value_bool = json_configure_data->get_config_data(AUTOMATIC_WIPER_OPERATION_CONFIG);
    ptr_dd->auto_wiper_settings_mode = (config_value_bool == STATUS_ON);

    ptr_dd->rain_sensitivity = json_configure_data->get_config_data(SENSOR_SENSITIVITY_TO_RAIN_CONFIG).toUInt();
    ptr_dd->sensitivity_to_light = json_configure_data->get_config_data(SENSOR_SENSITIVITY_TO_LIGHT_CONFIG).toUInt();
    config_value_bool = json_configure_data->get_config_data("turbo_timer");
    ptr_dd->turbo_timer = (config_value_bool == STATUS_ON);

    ptr_dd->driver_installation_temperature = json_configure_data->get_config_data(INSTALLATION_TEMPERATURE_DC_CONFIG).toUInt(&status);

    config_value_bool = json_configure_data->get_config_data(AUTOMATIC_OPENING_CONFIG);
    ptr_dd->automatic_opening = (config_value_bool == STATUS_ON);

    config_value_bool = json_configure_data->get_config_data(AUTOMATIC_DOOR_CLOSING_BY_SENSORS_CONFIG);
    ptr_dd->auto_closing_doors_by_sensors = (config_value_bool == STATUS_ON);

    config_value_bool = json_configure_data->get_config_data(AUTOMATIC_DOOR_CLOSING_WHEN_LEAVING_BUS_CONFIG);
    ptr_dd->auto_closing_drs_when_leaving_vehicle = (config_value_bool == STATUS_ON);

    config_value_bool = json_configure_data->get_config_data(AUTOMATIC_KNEELING_CONFIG);
    ptr_dd->auto_kneeling = (config_value_bool == STATUS_ON);

    config_value_bool = json_configure_data->get_config_data(AUTOMATIC_ON_OF_ALARM_SYSTEM_CONFIG);
    ptr_dd->automatic_on_alarm = (config_value_bool == STATUS_ON);

    config_value_bool = json_configure_data->get_config_data(DOORWAY_PASSENGER_SENSOR_CONFIG);
    ptr_dd->sensors_presence_passenger_doorway = (config_value_bool == STATUS_ON);
    CATCH_BLOCK
}

void QtMenuOps::update_language_change(QString language_chg)
{
    TRY_BLOCK
    newMenuItems* menu_items_dashboard;

    if (language_menu != language_chg)
    {
        language_menu = language_chg;
        update_language(language_menu == LANGUAGE_ENGLISH ? LANGUAGE_ENG : LANGUAGE_RUS);
        initialize_menu_parameter_names();
        initialize_menu_diagnostics_names();
        initialize_menu_settings_names();
        initialize_menu_services_names();
        //this->init_update_messageid();
        emit update_central_dashboard_data();
    }

    menu_items_dashboard = menu_handler->get_menu_item_data();
    bool* ptr_str_data = get_if<bool>(&(menu_items_dashboard->submenus[E_MT_SETTINGS].submenu_page[DASH_BOARD].opt_submenu_string[E_MTSET_DASH_LANG].submenu_string));
    *ptr_str_data = !(language_chg.toStdString() == LANGUAGE_ENGLISH);
    menu_handler->update_all_menu_data();
    CATCH_BLOCK
}

QString QtMenuOps::get_config_file_data(QString key_data)
{
    TRY_BLOCK
    QString text = "NULL";
    if (_init_config_data_update_status)
        text = json_configure_data->get_config_data(key_data);
    if ((text == "NULL") || (text == ""))
        text = key_data == "new_password" ? "1252" : "0";
    return text;
    CATCH_BLOCK
}

const QStringList& QtMenuOps::get_main_menu_names() const
{
    TRY_BLOCK
        return m_main_menu_names;
    CATCH_BLOCK
}

void QtMenuOps::set_main_menu_names(const QStringList& _names)
{
    if (m_main_menu_names == _names)
        return;
    m_main_menu_names = _names;
    emit main_menu_names_changed();
}

const QStringList& QtMenuOps::get_sub_menu_names() const
{
    TRY_BLOCK
        return left_menu_list;
    CATCH_BLOCK
}

void QtMenuOps::set_sub_menu_names(const QStringList& _names)
{
    if (left_menu_list == _names)
        return;
    left_menu_list = _names;
    emit sub_menu_names_changed();
}

    const QList<QStringList>& QtMenuOps::get_param_menu_names() const
{
    TRY_BLOCK
        return right_menu_params;
    CATCH_BLOCK
}

void QtMenuOps::set_param_menu_names(const QList<QStringList>& _names)
{
    if (right_menu_params == _names)
        return;
    right_menu_params = _names;
    emit param_menu_names_changed();
}

const QStringList& QtMenuOps::get_right_menu_values_list() const
{
    TRY_BLOCK
        return right_menu_values_list;
    CATCH_BLOCK
}

void QtMenuOps::set_right_menu_values_list(const QStringList& _names)
{
    if (right_menu_values_list == _names)
        return;
    right_menu_values_list = _names;
    emit right_menu_values_list_changed();
}

bool QtMenuOps::set_new_screen(int nScreenEnum)
{
    TRY_BLOCK
        qDebug("Set New Screen %d", nScreenEnum);
    if (nScreenEnum == E_SL_LIST && (get_screen_state() == E_SL_MAIN || get_screen_state() == E_SL_PASSLOCK))
    {
        menu_handler->get_menu_item_data()->get_left_list(&left_menu_list);

        if(left_menu_list.empty())
            return false;

        emit sub_menu_names_changed();
        menu_handler->get_menu_item_data()->get_right_list(&right_menu_params, &right_menu_values_list);
        emit param_menu_names_changed();
        emit right_menu_values_list_changed();
    }
    else if(nScreenEnum == E_SL_SUBPARAMS || (nScreenEnum == E_SL_PARAMS && get_screen_state() == E_SL_SUBPARAMS))
    {
        menu_handler->get_menu_item_data()->get_right_list(&right_menu_params, &right_menu_values_list);
        emit param_menu_names_changed();
        emit right_menu_values_list_changed();
    }
    set_screen_state(nScreenEnum);

    return true;
    CATCH_BLOCK
}

void QtMenuOps::set_new_focus(int _focus_main, int _focus_list, int _focus_param)
{
    TRY_BLOCK
    set_main_menu_pos(_focus_main);
    if (list_menu_pos != _focus_list)
    {

        menu_handler->get_menu_item_data()->get_right_list(&right_menu_params, &right_menu_values_list);
        emit param_menu_names_changed();
        emit right_menu_values_list_changed();
        set_list_menu_pos(_focus_list);
    }
    set_param_menu_pos(_focus_param);
    CATCH_BLOCK
}

void QtMenuOps::set_values(bool is_settings)
{
    if (is_settings || m_update_time_stamp + 1000ms < chrono::steady_clock::now())
    {
        menu_handler->get_menu_item_data()->get_value_list(&right_menu_values_list);
        emit right_menu_values_list_changed();
        m_update_time_stamp = chrono::steady_clock::now();
    }
};

void QtMenuOps::set_language()
{
    update_language_change(get_config_file_data("language_change"));
    menu_handler->get_menu_item_data()->get_left_list(&left_menu_list);
    emit sub_menu_names_changed();
    menu_handler->get_menu_item_data()->get_right_list(&right_menu_params, &right_menu_values_list);
    emit param_menu_names_changed();
    emit right_menu_values_list_changed();
}

