#ifndef MENU_ITEMS_H
#define MENU_ITEMS_H
#include <cstdint>
#include <optional>
#include <variant>
#include <vector>
#include <unordered_map>
#include <string>
#include "../Connectivity/JSON/qtjsonmenuhandler.h"
#include "../Interfaces/IMenuNavigation.h"
using namespace std;

#define INIT_VALUE "0"
#define FLAG_EXISTS "Yes"
#define PARAMETERS "Parameters"
#define DIAGNOSTICS "Diagnostics"
#define SETTINGS "Settings"
#define SERVICES "Services"
#define ENGINE "Engine"
#define ENGINE_PARAMETERS_COUNT 5
#define TRANSMISSION "Transmission"
#define TRANSMISSION_PARAMETERS_COUNT 2
#define BATTERY "Battery"
#define BATTERY_PARAMETERS_COUNT 3
#define PNEUMATIC_SYSTEM "Pneumatic System"
#define PNEUMATIC_SYSTEM_PARAMETERS_COUNT 5
#define TIRE_PRESSURE_AND_TEMPERATURE "Tire Pressure and temperature"
#define BRAKE_PADS_WEAR "Brake pads wear"
#define WIPERS "Wipers"
#define REAGENT_ADBLUE "Reagent AdBlue"
#define PARAMETER_1 "1"
#define PARAMETER_2 "2"
#define PARAMETER_3 "3"
#define PARAMETER_4 "4"
#define PARAMETER_5 "5"
#define INVALID_SIGNAL "--"
#define INIT_PERCENTAGE_VALUE "0"
#define BRAKE_PADS_SEPERATOR ":"
#define BRAKE_PADS_MAX_PERCENTAGE 100

#define EFL_P1_ENGINEOILPRESSUREFACTOR 4
#define LFE1_SPN183_ENGINEFLUERATEFACTOR 0.05
#define TRF1_TRANSOILTEMP1FACTOR 0.03125
#define CBCU2_CBCU_MAINPWRFACTOR 0.1
#define AT1T1I_AFTRTRTMNT1DSLEXHSTFLIDTANKLEVELFACTOR 0.4
#define VDHR_EE_SPN918_HIGHRESOLUTIONTRIPDIFACTOR 5
#define AIR1_PARKINGAIRPRESSUREFACTOR 8
#define AIR1_SERVICEBRAKEAIRPRESSURECIRCUIT1FACTOR 8
#define AIR1_SERVICEBRAKEAIRPRESSURECIRCUIT2FACTOR 8
#define AIR1_AUXILARYEQUIPMENTSUPPLYPRESSUREFACTOR 8
#define AIR1_PERCENTAGE_CONVERT 10
#define AIR1_VALUE_CONVERTOR 100
#define CBCU2_CBCU_MAINPWRFACTOR_PERCENTAGE_CONVERTOR 0.17
#define CBCU2_CBCU_MAINPWRFACTOR_PERCENTAGE_OFFSET 15
#define LS_WASHER_LEVELFACTOR (1)
#define DYN_BB_CURRENT_CURRENT_1FACTOR (0.1)
#define DYN_BB_CURRENT_CURRENT_2FACTOR (0.1)

#define MAX_PRESSURE_BAR 10
#define MIN_PRESSURE_BAR 0
#define MAX_TEMPERATURE 210
#define MIN_TEMPERATURE -40

#define MIN_PNEUMATICSYSTEM_PRESSURE 0
#define MAX_PNEUMATICSYSTEM_PRESSURE 20

#define MAX_TRANSMISSION_OIL_TEMPERATURE 1735
#define MIN_TRANSMISSION_OIL_TEMPERATURE -273
#define MAX_TRANSMISSION_OIL_TEMPERATURE_HYDRAULIC_RETARDER 210
#define MIN_TRANSMISSION_OIL_TEMPERATURE_HYDRAULIC_RETARDER -40

#define MAX_ENGINE_OIL_TEMPERATURE 1735
#define MIN_ENGINE_OIL_TEMPERATURE -273
#define MIN_FUEL_CONSUMPTION 0
#define MAX_FUEL_CONSUMPTION 3213
#define MAX_LETER_PER_100KM 50
#define MIN_LETER_PER_100KM 0

#define MAX_PERCENTAGE 100
#define MIN_PERCENTAGE 0

#define MAX_VOLTAGE 361
#define MIN_VOLTAGE 0
#define MIN_CURRENT -1000.0
#define MAX_CURRENT 1000.0
#define MAX_COOLANT_TEMP 210 //120
#define MIN_COOLANT_TEMP -40
#define MAX_WIPERS_NO_OF_OPERATIONS (64255U)
#define AVERAGE_SECONDS 3600
#define TWO_SECONDS 2
#define TIRE_TEMPERATURE_FACTOR 0.031250
#define TIRE_TEMPERATURE_OFFSET (-273)
#define TIRE_PRESSURE_FACTOR 4
#define BRAKEPADS_FACTOR 0.4
#define MAX_OUTPUT_SHAFT_SPEED 8032
#define ET1_CANID_SPN175_ENGINEOILTEMPERATURE_OFFSET (-273)
#define ET1_CANID_SPN175_ENGINEOILTEMPERATURE_FACTOR (0.031250)
#define TRANSMISSION_OUTPUT_SHAFT_SPEED_FACTOR (0.125)

#define EFL_P1_ENGINEOILPRESSURE_VALUE_CONVERTOR 100
#define EFL_P1_ENGINEOILPRESSURE_PERCENTAGE_CONVERTOR 10
#define LFE1_SPN183_PERCENTAGE_CONVERTOR 1.25
#define TRF1_TRANSOILTEMP1_PERCENTAGE_CONVERTOR 2.5
#define TRF1_TRANSOILTEMP1_PERCENTAGE_OFFSET 40
#define AT1T1I_PERCENTAGE_CONVERTOR 2.5
#define AT1T1I_PERCENTAGE_OFFSET 40
#define M_TO_KM(x) (float)(x) / 1000.f
#define AVERAGE_FUEL_CONSUMPTION_PERCENTAGE_CONVERTOR 0.5
#define AVERAGE_FUEL_CONSUMPTION 2
#define AVERAGE_FUEL_CONSUMPTION_100KM 100

#define UOM_DEGREE_CELCIUS " °C"
#define UOM_BAR " bar"
#define UOM_CONSUMPTION " L/h"
#define UOM_KM " L/100KM"
#define UOM_VOLTAGE " V"
#define UOM_AMPERE " A"
#define UOM_PERCENTAGE " %"
#define UOM_SHAFT_SPEED " U/min"
#define LIGHTING_EQUIPEMENTS "Lighting Equipments"

#define INIT_TYRE_TEMPERATURE "-- °C"
#define TYRE_INIT_COLOR "white"
#define TYRE_WARNING_COLOR "yellow"
#define TYRE_CRITICAL_COLOR "red"

#define MAXIMUM_TYRE_COUNT 10
#define EMERGENCE_CRANE_COUNT 8
#define DOOR_VALVES_COUNT 8
#define DOOR_SENSOR_COUNT 16
#define EMERGENCE_HAMMERS_COUNT 5
#define FIRE_EXTINGUISHER_COUNT 3
#define HEATERS_COUNT 9
#define HEATING_SYSTEM_VALVES_COUNT 9
#define LIGHTING_EQUIPMENT_COUNT 10

#define MAX_ERROR_CODES_FAILURE_FIRE_EXTINGUISHER 10
#define MAX_ERROR_CODES_FAILURE_BRAKE_SYSTEM 3
#define MAX_ERROR_CODES_FAILURE_PNEUMATIC_SYSTEM 3
#define MAX_ERROR_CODES_FAILURE_PROPULSION_SYSTEM 3
#define MAX_ERROR_CODES_FAILURE_TRANSMISSION_SYSTEM 3
#define MAX_ERROR_CODES_FAILURE_TACHOGRAPH_SYSTEM 3
#define MAX_ERROR_CODES_FAILURE_TIRE_PRESSURE_TEMP_MONITOR_SYSTEM 2
#define MAX_ERROR_CODES_FAILURE_ADAS_DRIVER_ASSISTANCE_SYSTEM 1

#define MAX_DIAGNOSTIC_TROUBLE_CODE 5
typedef enum {
    E_MT_PARAMETERS = 0,
    E_MT_DIAGNOSTICS,
    E_MT_SETTINGS,
    E_MT_SERVICES,
    E_MT_SUBMENU_TOTAL,

    //MENU->PARAMETERS->TRANSMISSION
    E_MTP_TRANS_OIL_TEMP = 0,
    E_MTP_TRANS_OIL_TEMP_HYDR,
    E_MTP_TRANS_OUT_SHAFT_SPEED,
    E_MTP_TRANS_TOTAL,

    //MENU->SETTINGS->DASHBOARD
    E_MTSET_DASH_AUTO_BRIGHT = 0,
    E_MTSET_DASH_BRIGHT,
    E_MTSET_DASH_LANG,
    E_MTSET_DASH_TOTAL,
} e_menu_titles;

typedef enum {
    VEHICLE_NAME_LIAZ429260_79 = 0U,
    VEHICLE_NAME_LIAZ529265_79,
    VEHICLE_NAME_LIAZ621365_79,
    VEHICLE_NAME_LIAZ529265_80,
    VEHICLE_NAME_LIAZ621365_80,
    VEHICLE_NAME_LIAZ62174_79_ELECTRIC,
    VEHICLE_NAME_LIAZ529271_79_CNG,
    VEHICLE_NAME_LIAZ621371_79_CNG,
    VEHICLE_NAME_LIAZ529271_80_CNG,
    VEHICLE_NAME_LIAZ621371_80_CNG,
    VEHICLE_NAME_LIAZ529265_79_Diesel,
    VEHICLE_NAME_LIAZ621365_79_Diesel,
    VEHICLE_NAME_LIAZ529265_80_Diesel,
    VEHICLE_NAME_LIAZ621365_80_Diesel,
    VEHICLE_NAME_TOTAL,
} VehicleName;

typedef enum {
    TIRE_POSITION_1 = 0u,
    TIRE_POSITION_2,
    TIRE_POSITION_3,
    TIRE_POSITION_4,
    TIRE_POSITION_5,
    TIRE_POSITION_6,
    TIRE_POSITION_7,
    TIRE_POSITION_8,
    TIRE_POSITION_9,
    TIRE_POSITION_10,
    TIRE_POSITION_TOTAL,
} TirePosition;

typedef struct {
    string group_name;
    uint8_t position;
    bool group_name_status;
} FailureGroupData;

typedef struct {
    string error_code;
    bool error_code_status;
    string error_code_description;
    string error_repetation;
} FailureErrorCode;

typedef struct {
    string group_name;
    uint8_t position;
    bool group_name_status;
    vector<FailureErrorCode> error_code;
    uint8_t module_error_count;
} FailureModule;

typedef struct {
    FailureGroupData fire_extinguisher_grp;
    FailureErrorCode error_code[MAX_ERROR_CODES_FAILURE_FIRE_EXTINGUISHER];
    uint8_t fire_extinguisher_error_count;
} FailureFireExtinguisher;

typedef struct {
    FailureGroupData brake_system_grp;
    FailureErrorCode error_code[MAX_ERROR_CODES_FAILURE_BRAKE_SYSTEM];
    uint8_t brake_system_error_count;
} FailureBrakeSystem;

typedef struct {
    FailureGroupData pneumatic_system_grp;
    FailureErrorCode error_code[MAX_ERROR_CODES_FAILURE_PNEUMATIC_SYSTEM];
    uint8_t pneumatic_system_error_count;
} FailurePneumaticSystem;

typedef struct {
    FailureGroupData propulsion_system_grp;
    FailureErrorCode error_code[MAX_ERROR_CODES_FAILURE_PROPULSION_SYSTEM];
    uint8_t propulsion_error_count;
} FailurePropulsionSystem;

typedef struct {
    FailureGroupData transmission_system_grp;
    FailureErrorCode error_code[MAX_ERROR_CODES_FAILURE_TRANSMISSION_SYSTEM];
    uint8_t transmission_error_count;
} FailureTransmissionSystem;

typedef struct {
    FailureGroupData tachograph_system_grp;
    FailureErrorCode error_code[MAX_ERROR_CODES_FAILURE_TACHOGRAPH_SYSTEM];
    uint8_t tachograph_error_count;
} FailureTachographSystem;

typedef struct {
    FailureGroupData tire_pressure_temp_monitor_system_grp;
    FailureErrorCode error_code[MAX_ERROR_CODES_FAILURE_TIRE_PRESSURE_TEMP_MONITOR_SYSTEM];
    uint8_t tire_pressure_temp_error_count;
} FailureTirePressureTemperatureMonitoringSystem;

typedef struct {
    FailureGroupData adas_driver_system_grp;
    FailureErrorCode error_code[MAX_ERROR_CODES_FAILURE_ADAS_DRIVER_ASSISTANCE_SYSTEM];
    uint8_t adas_driver_error_count;
} FailureADASDriverSystem;

typedef struct {
    string group_name;
    bool group_name_status;
} DtcGroupData;

typedef struct {
    bool trouble_code_status;
    string trouble_code_source;
    uint32_t trouble_code_spn;
    uint8_t trouble_code_fmi;
    string trouble_code_recommendations;
    uint8_t trouble_code_repetations;
} DtcGroupErrorCode;

typedef struct {
    string group_name;
    bool group_name_status;
    vector<DtcGroupErrorCode> trouble_code;
    uint8_t module_error_count;
} DtcModule;

typedef struct {
    DtcGroupData propulsion_system_grp;
    DtcGroupErrorCode trouble_code[MAX_DIAGNOSTIC_TROUBLE_CODE];
    uint8_t propulsion_dtc_error_count;
} DtcPropulsionSystem;

typedef struct {
    DtcGroupData transmission_system_grp;
    DtcGroupErrorCode trouble_code[MAX_DIAGNOSTIC_TROUBLE_CODE];
    uint8_t transmission_dtc_error_count;
} DtcTransmissionSystem;

typedef struct {
    DtcGroupData brake_system_grp;
    DtcGroupErrorCode trouble_code[MAX_DIAGNOSTIC_TROUBLE_CODE];
    uint8_t brake_dtc_error_count;
} DtcBrakeSystem;

typedef struct {
    DtcGroupData pneumatic_system_grp;
    DtcGroupErrorCode trouble_code[MAX_DIAGNOSTIC_TROUBLE_CODE];
    uint8_t pneumatic_dtc_error_count;
} DtcPneumaticSystem;

typedef struct {
    DtcGroupData tachograph_system_grp;
    DtcGroupErrorCode trouble_code[MAX_DIAGNOSTIC_TROUBLE_CODE];
    uint8_t tachograph_dtc_error_count;
} DtcTachographSystem;

typedef struct {
    DtcGroupData tire_pressure_monitoring_system_grp;
    DtcGroupErrorCode trouble_code[MAX_DIAGNOSTIC_TROUBLE_CODE];
    uint8_t tire_pressure_monitor_dtc_error_count;
} DtcTirePressureMonitoringSystem;

typedef struct {
    VehicleName vehicle_name;
    uint8_t vehicle_type;
} VehicleDetails;

typedef struct {
    int32_t tire_temperature_data;
    float tire_pressure_data;
    uint8_t tire_status;
    uint8_t tire_sensor_elect_fault;
} TireDetails;

typedef struct TyreWarningPressureDetails
{
    void fill(tuple<VehicleName, float, float, float, float, float, float> _tuple)
    {
        vehicle_name = get<0>(_tuple);
        rated_pressure = get<1>(_tuple);
        first_low_pressure_threshold = get<2>(_tuple);
        second_low_pressure_threshold = get<3>(_tuple);
        high_pressure_threshold = get<4>(_tuple);
        exceed_permissable_pressure_diff_twin_wheels = get<5>(_tuple);
        exceed_permissable_pressure_diff_same_axle = get<6>(_tuple);
    };
    VehicleName vehicle_name;
    float rated_pressure;
    float first_low_pressure_threshold;
    float second_low_pressure_threshold;
    float high_pressure_threshold;
    float exceed_permissable_pressure_diff_twin_wheels;
    float exceed_permissable_pressure_diff_same_axle;
} TyreWarningPressureDetails;

#endif // MENU_ITEMS_H
