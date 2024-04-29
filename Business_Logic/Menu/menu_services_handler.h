#ifndef MENUSERVICESHANDLER_H
#define MENUSERVICESHANDLER_H

#include "newmenuitems.h"
#include "../Connectivity/hmi_handler.h"
#include "../Connectivity/JSON/qtjsonconfiguredata.h"
#include "../Connectivity/j1939_data_handler.h"
#include "../Common/menu_defines.h"
#include "../subscribe_notifer.h"
#include <QMutexLocker>
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <string>
#include "../Logger/exception_define.h"
#include "./newmenuitems.h"
#include "../Common/hmi_config.h"

#define DOOR_MANAGEMENT "DOOR_MANAGEMENT"
#define DIAGNOSTICS_TROUBLE_CODE "DIAGNOSTICS_TROUBLE_CODE"
#define ADDITIONAL_FUNCTIONALITY "ADDITIONAL_FUNCTIONALITY"
#define STEERING_ANGLE_SENSOR "STEERING_ANGLE_SENSOR"
#define DATA_SOURCE "DATA_SOURCE"

#define CHANGE_PASSWORD "CHANGE_PASSWORD"
#define SOFTWARE_VERSION "SOFTWARE_VERSION"

#define PROPULSION_SYSTEM "Propulsion System"
#define TRANSMISSION "Transmission"
#define BRAKE_SYSTEM "Brake system"
#define TACHOGRAPH "Tachograph"
#define TYRE_PRESSURE_MONITORING_SYSTEM "Tyre pressure monitoring system"
#define DTC_RECOMMENDATIONS "Advice : contact the service centre"

#define VALID_VALUE 1
#define SOFTWARE_VERSION_INIT "643.AMFE."
#define DOT_SEPERATOR "."
#define DASH_SEPERATOR "-"
// Software version
#define EC12_CLIENT_ID "02"
#define EC12_MODEL_ID "100"
#define EC12_ECU_ID "22"
#define EC12_FUNCTION_ID "17"
#define EC12_SOFTWARE_TYPE "06"
#define EC12_SOFTWARE_NUMBER "00002"

#define RAD " rad"
#define PI 3.14f
#define UOM_DEGREE_CELCIUS " °C"
#define AUTOMATIC_OPENING_CONFIG "automatic_opening"
#define AUTOMATIC_DOOR_CLOSING_BY_SENSORS_CONFIG "automatic_door_closing_by_sensors"
#define AUTOMATIC_DOOR_CLOSING_WHEN_LEAVING_BUS_CONFIG "automatic_door_closing_when_leaving_bus"
#define AUTOMATIC_KNEELING_CONFIG "automatic_kneeling"
#define AUTOMATIC_ON_OF_ALARM_SYSTEM_CONFIG "automatic_on_of_alarm_system"
#define DOORWAY_PASSENGER_SENSOR_CONFIG "doorway_passenger_sensor"

#define STEERING_ANGLE_FACTOR 0.000977
#define SAS_CANID_STEERING_WHEEL_ANGLE_OFFSET (-31.374)

#define STR(x) #x

#define CONCATENATE_STRINGS(s1, s2) s1 s2

#define _software_version_details_ec12         \
    CONCATENATE_STRINGS(SOFTWARE_VERSION_INIT, \
    CONCATENATE_STRINGS(EC12_CLIENT_ID,        \
    CONCATENATE_STRINGS(DOT_SEPERATOR,         \
    CONCATENATE_STRINGS(EC12_MODEL_ID,         \
    CONCATENATE_STRINGS(DOT_SEPERATOR,         \
    CONCATENATE_STRINGS(EC12_ECU_ID,           \
    CONCATENATE_STRINGS(DOT_SEPERATOR,         \
    CONCATENATE_STRINGS(EC12_FUNCTION_ID,      \
    CONCATENATE_STRINGS(DOT_SEPERATOR,         \
    CONCATENATE_STRINGS(EC12_SOFTWARE_TYPE,    \
    CONCATENATE_STRINGS(DASH_SEPERATOR, EC12_SOFTWARE_NUMBER)))))))))))

using namespace std;

class MenuServicesHandler : public ISubscriber {
public:
    static MenuServicesHandler* get_instance(newMenuItems*);
    void update_services_data(void);
    bool update_info(uint32_t _id) override;

private:
    MenuServicesHandler(newMenuItems*);
    void init_subscribe() override;

    void init_door_management(void);
    void init_wipers(void);
    void init_diagnostic_trouble_code(void);
    void init_additional_functionality(void);
    void init_steering_angle_sensor(void);
    void init_data_source(void);
    void init_change_passowrd(void);
    void init_software_version(void);

    void update_diagnostic_trouble_code();
    //void update_additional_functionality();
    void update_steering_angle_sensor();
    void update_software_version();

    void initialize_trouble_code_dtc_data();
    string calculate_prefix_zeroes(uint16_t software_id, uint8_t length);
    string convert_data_hexadecimal(uint8_t);

    string get_config_file_data(string);


    static shared_ptr<MenuServicesHandler> m_ptr_instance;
    static mutex m_build_mutex;
    J1939DataHandler* j1939_data_handler;
    HmiHandler* m_ptr_cached_msgs;
    newMenuItems* menu_services_data;
    QtJsonConfigureData* json_configure_data_services;
};

#endif // MENUSERVICESHANDLER_H
