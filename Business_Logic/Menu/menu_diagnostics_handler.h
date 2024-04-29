#ifndef MENUDIAGNOSTICSHANDLER_H
#define MENUDIAGNOSTICSHANDLER_H

#include "../Connectivity/j1939_data_handler.h"
#include "newmenuitems.h"
#include "../Connectivity/hmi_handler.h"
#include "../subscribe_notifer.h"
#include <QMutexLocker>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../Logger/exception_define.h"
#include "./newmenuitems.h"
#include "../Common/hmi_config.h"

#define EMERGENCY_CRANES "Emergency Cranes"
#define DOOR_VALVES "Door Valves"
#define DOOR_SENSORS "Door Sensors"
#define EMERGENCY_HAMMERS "Emergency Hammers"
#define FIRE_EXTINGUISHERS "Fire Extinguishers"
#define HEATERS "Heaters"
#define HEATING_SYSTEM_VALVES "Heating System Valves"
#define FAILURES "Failures"
#define COLOR_WHITE "white"
#define COLOR_RED "red"
#define COLOR_YELLOW "yellow"
#define COLOR_GREEN "green"
#define STATE_OFF "OFF"
#define STATE_ON "ON"

#define FAILURE_ERROR_CODE_1002 "1002"
#define FAILURE_ERROR_CODE_1003 "1003"
#define FAILURE_ERROR_CODE_1004 "1004"
#define FAILURE_ERROR_CODE_1005 "1005"
#define FAILURE_ERROR_CODE_1006 "1006"
#define FAILURE_ERROR_CODE_1007 "1007"
#define FAILURE_ERROR_CODE_1008 "1008"
#define FAILURE_ERROR_CODE_1009 "1009"
#define FAILURE_ERROR_CODE_1010 "1010"
#define FAILURE_ERROR_CODE_1011 "1011"
#define FAILURE_ERROR_CODE_3001 "3001"
#define FAILURE_ERROR_CODE_3002 "3002"
#define FAILURE_ERROR_CODE_3003 "3003"
#define FAILURE_ERROR_CODE_4001 "4001"
#define FAILURE_ERROR_CODE_4002 "4002"
#define FAILURE_ERROR_CODE_4003 "4003"
#define FAILURE_ERROR_CODE_5001 "5001"
#define FAILURE_ERROR_CODE_5002 "5002"
#define FAILURE_ERROR_CODE_5003 "5003"
#define FAILURE_ERROR_CODE_6001 "6001"
#define FAILURE_ERROR_CODE_6002 "6002"
#define FAILURE_ERROR_CODE_6003 "6003"
#define FAILURE_ERROR_CODE_7001 "7001"
#define FAILURE_ERROR_CODE_7003 "7003"
#define FAILURE_ERROR_CODE_10001 "10001"
#define FAILURE_ERROR_CODE_10002 "10002"
#define FAILURE_ERROR_CODE_13001 "13001"
#define FAILURE_ERROR_CODE_TOTAL 27

using namespace std;
class MenuDiagnosticsHandler : public ISubscriber {
public:
    typedef struct {
        string error_code;
        bool error_status;
        uint8_t repetation_count;
    } HandleRepetationErrors;

    static MenuDiagnosticsHandler* get_instance(newMenuItems*);

    void update_diagnostics_data();
    bool update_info(uint32_t _id) override;
private:
    MenuDiagnosticsHandler(newMenuItems*);
    void init_subscribe() override;
    void init_diagnostics_emergency_cranes();
    void init_diagnostic_door_valves();
    void init_diagnostic_door_sensors();
    void init_diagnostic_emergency_hammers();
    void init_diagnostic_fire_extinguishers();
    void init_diagnostic_heaters();
    void init_diagnostic_heating_system_valves();
    void init_diagnostic_lighting_equipments();
    void init_diagnostic_failures_error_code();

    void update_diagnostics_emergency_cranes();
    void update_diagnostic_door_valves();
    void update_diagnostic_door_sensors();
    void update_diagnostic_emergency_hammers();
    void update_diagnostic_fire_extinguishers();
    void update_diagnostic_heaters();
    void update_diagnostic_heating_system_valves();
    void update_diagnostic_failures();

    void initialize_error_data_failures();
    void initialize_map_repetation_error_count();
    void update_map_repetation_error_count(bool status, string key_value);
    uint8_t get_map_repetation_error_count(string key_value);

    static mutex m_build_mutex;
    static shared_ptr<MenuDiagnosticsHandler> m_ptr_instance;

    map<string, MenuDiagnosticsHandler::HandleRepetationErrors> map_repetation_count;
    HmiHandler* m_ptr_cached_msg;
    newMenuItems* menu_diagnostic_data;
    J1939DataHandler* j1939_data;
};

#endif // MENUDIAGNOSTICSHANDLER_H
