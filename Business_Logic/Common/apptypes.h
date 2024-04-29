#pragma once
#ifndef APPTYPES_H
#define APPTYPES_H

// C++ Includes
#include <map>
#include <unordered_map>
#include <list>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <vector>
#include <queue>

//-----Macroses for optimizator----------
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
//-----Returned status definition--------
#define STATUS_OK 0
#define STATUS_SOCKET_CREATION_FAILED -1
#define STATUS_BINDING_PROCESS_FAILED -2
//-----Possible CAN message id's---------
#define HMIHANDLER_EEC1_ID (217056256U)
#define HMIHANDLER_TCO1_ID (218000622U)
#define HMIHANDLER_CCVS1_ID (419361057U)
#define HMIHANDLER_TT_GRP_A_ID (419367457U)
#define HMIHANDLER_TT_GRP_B_ID (419367713U)
#define HMIHANDLER_TT_GRP_C_ID (419367969U)
#define HMIHANDLER_TT_GRP_D_ID (419368225U)
#define HMIHANDLER_TT_GRP_E_ID (419368481U)
#define HMIHANDLER_TT_GRP_F_ID (419368737U)
#define HMIHANDLER_TT_GRP_G_ID (419405857U)
#define HMIHANDLER_TT_GRP_H_ID (419406113U)
#define HMIHANDLER_TT_GRP_I_ID (0x18FFAB21U)
#define HMIHANDLER_TT_GRP_K_ID (419406881U)
#define HMIHANDLER_TT_GRP_P_ID (419408161U)
#define HMIHANDLER_TT_GRP_M_ID (419407393U)
#define HMIHANDLER_TT_GRP_J_ID (419406625U)
#define HMIHANDLER_DC2_ID (419276065U)
#define HMIHANDLER_ETC1_ID (217055747U)
#define HMIHANDLER_ETC2_ID (418383107U)
#define HMIHANDLER_EBC4_ID (486452235U)
#define HMIHANDLER_FB1_ID (419410209U)
#define HMIHANDLER_OEL_ID (217959473U)

#define HMIHANDLER_DD_INFO1_ID (419370785U)
#define HMIHANDLER_DD_INFO2_ID (419370801U)
#define HMIHANDLER_DD_INFO3_ID (0x18FF1821U)

#define HMIHANDLER_DC1_ID (419319329U)
#define HMIHANDLER_CL_ID (416314657U)
#define HMIHANDLER_AUXIO4_75_ID (413466741U)
#define HMIHANDLER_EFL_P1_ID (419360512U)
#define HMIHANDLER_LFE1_ID (419361280U)
#define HMIHANDLER_TRF1_ID (419362819U)
#define HMIHANDLER_CBCU2_ID (419377713U)
#define HMIHANDLER_AIR1_ID (419343920U)
#define HMIHANDLER_LS_ID (419354417U)
#define HMIHANDLER_D1_ID (419418401U)
#define HMIHANDLER_AT1T1I_ID (419321344U)
#define HMIHANDLER_VDHR_EE_ID (419348974U)
#define HMIHANDLER_TIRE_CONDITION_ID (419361843U)
#define HMIHANDLER_EBC4_ID (486452235U)
#define HMIHANDLER_DYN_BB_CURRENT_ID (419365409U)
#define HMIHANDLER_TD_ID (419358446U)
#define HMIHANDLER_SAS_ID (418389476U)
#define HMIHANDLER_SOFT_IC12_ID (419355159U)
#define HMIHANDLER_SOFT_ZR_ID (419355169U)
#define HMIHANDLER_SOFT_ZKSH_ID (419355185U)
#define HMIHANDLER_SOFT_STEERING_WHEEL_ID (419355253U)
#define HMIHANDLER_SOFT_PV_ID (419355273U)
#define HMIHANDLER_DD_SETTINGS_ID (419373335U)
#define HMIHANDLER_ET1_ID (419360256U)
#define HMIHANDLER_RF_ID (419363600U)
#define HMIHANDLER_RELAY_ID (418316397U)
#define HMIHANDLER_FB3_ID (419410721U)
#define HMIHANDLER_SAS_CFG_ID (418374667U)
#define HMIHANDLER_EBC1_ID (418382129U)
#define HMIHANDLER_ASC1_ID (217995823U)
#define HMIHANDLER_ADAS_600_ID (403046483U)
#define HMIHANDLER_VEHICLEDATA_620_ID (403054675U)
#define HMIHANDLER_RESET_ID (484371991U)

#define HMIHANDLER_DM1_00_ID (485214720U)
#define HMIHANDLER_DM1_00_BAM_ID (485293824U)
#define HMIHANDLER_DM1_03_ID (485214723U)
#define HMIHANDLER_DM1_03_BAM_ID (485293827U)
#define HMIHANDLER_DM1_0B_ID (485214731U)
#define HMIHANDLER_DM1_0B_BAM_ID (485293835U)
#define HMIHANDLER_DM1_12_ID (485214738U)
#define HMIHANDLER_DM1_12_BAM_ID (485293842U)
#define HMIHANDLER_DM1_2F_ID (485214767U)
#define HMIHANDLER_DM1_2F_BAM_ID (485293871U)
#define HMIHANDLER_DM1_33_ID (485214771U)
#define HMIHANDLER_DM1_33_BAM_ID (485293875U)
#define HMIHANDLER_DM1_EE_ID (485214958U)
#define HMIHANDLER_DM1_EE_BAM_ID (485294062U)

#define HMIHANDLER_AMB_ID (419362081U)
//UDS
#define HMIHANDLER_UDS (2033U)
#define TOTAL_CAN_IDS (67)
#define CAN_MSG_DATA_SIZE 8
#define CAN_MSG_ALARM_TIMEOUT 4
//Period MSG
#define CYCLE_TIME_50MS 50 * CAN_MSG_ALARM_TIMEOUT
#define CYCLE_TIME_100MS 100 * CAN_MSG_ALARM_TIMEOUT
#define CYCLE_TIME_250MS 250 * CAN_MSG_ALARM_TIMEOUT
#define CYCLE_TIME_500MS 500 * CAN_MSG_ALARM_TIMEOUT
#define CYCLE_TIME_1000MS 1000 * CAN_MSG_ALARM_TIMEOUT
#define CYCLE_TIME_2500MS 2500 * CAN_MSG_ALARM_TIMEOUT
#define CYCLE_TIME_5000MS 5000 * CAN_MSG_ALARM_TIMEOUT
#define CYCLE_TIME_10000MS 10000 * CAN_MSG_ALARM_TIMEOUT
#define CYCLE_TIME_25000MS 25000 * CAN_MSG_ALARM_TIMEOUT
#define CYCLE_TIME_50000MS 50000 * CAN_MSG_ALARM_TIMEOUT

//namespace
using namespace std;
static const unordered_map<uint32_t, uint32_t> g_DM1_pairs
{
    {HMIHANDLER_DM1_00_BAM_ID, HMIHANDLER_DM1_00_ID},
    {HMIHANDLER_DM1_03_BAM_ID, HMIHANDLER_DM1_03_ID},
    {HMIHANDLER_DM1_0B_BAM_ID, HMIHANDLER_DM1_0B_ID},
    {HMIHANDLER_DM1_12_BAM_ID, HMIHANDLER_DM1_12_ID},
    {HMIHANDLER_DM1_2F_BAM_ID, HMIHANDLER_DM1_2F_ID},
    {HMIHANDLER_DM1_33_BAM_ID, HMIHANDLER_DM1_33_ID},
    {HMIHANDLER_DM1_EE_BAM_ID, HMIHANDLER_DM1_EE_ID}
};

//message_id, cycle_time
static vector<pair<uint32_t, uint32_t>> const g_CAN_msg_ids
{
    {HMIHANDLER_EEC1_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TCO1_ID, CYCLE_TIME_50MS},
    {HMIHANDLER_CCVS1_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_A_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_B_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_C_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_D_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_E_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_F_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_G_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_H_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_I_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_K_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_P_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_M_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TT_GRP_J_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_DC2_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_ETC1_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_ETC2_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_EBC4_ID, CYCLE_TIME_10000MS},
    {HMIHANDLER_FB1_ID, CYCLE_TIME_5000MS},
    {HMIHANDLER_OEL_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_DD_INFO1_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_DD_INFO2_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_DD_INFO3_ID, CYCLE_TIME_5000MS},
    {HMIHANDLER_DC1_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_CL_ID, CYCLE_TIME_5000MS},
    {HMIHANDLER_AUXIO4_75_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_EFL_P1_ID, CYCLE_TIME_500MS},
    {HMIHANDLER_LFE1_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_TRF1_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_CBCU2_ID, CYCLE_TIME_5000MS},
    {HMIHANDLER_AIR1_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_LS_ID, CYCLE_TIME_5000MS},
    {HMIHANDLER_D1_ID,  CYCLE_TIME_5000MS},
    {HMIHANDLER_AT1T1I_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_VDHR_EE_ID, CYCLE_TIME_50MS},
    {HMIHANDLER_TIRE_CONDITION_ID, CYCLE_TIME_10000MS},
    {HMIHANDLER_EBC4_ID, CYCLE_TIME_10000MS},
    {HMIHANDLER_DYN_BB_CURRENT_ID, CYCLE_TIME_10000MS},
    {HMIHANDLER_TD_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_SAS_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_SOFT_IC12_ID, CYCLE_TIME_10000MS},
    {HMIHANDLER_SOFT_ZR_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_SOFT_ZKSH_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_SOFT_STEERING_WHEEL_ID, CYCLE_TIME_5000MS},
    {HMIHANDLER_SOFT_PV_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_DD_SETTINGS_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_ET1_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_RF_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_RELAY_ID, CYCLE_TIME_50MS},
    {HMIHANDLER_FB3_ID, CYCLE_TIME_5000MS},
    {HMIHANDLER_SAS_CFG_ID, CYCLE_TIME_250MS},
    {HMIHANDLER_EBC1_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_ASC1_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_ADAS_600_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_VEHICLEDATA_620_ID, CYCLE_TIME_100MS},
    {HMIHANDLER_RESET_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_AMB_ID, CYCLE_TIME_1000MS},
    {HMIHANDLER_UDS,  CYCLE_TIME_100MS},
};

typedef enum
{
    CAN_MESSAGE_STATE_NOT_RECEIVED = 0u,
    CAN_MESSAGE_STATE_OK = 1u,
    CAN_MESSAGE_STATE_TIMEOUT = 2u,
    CAN_MESSAGE_STATE_NOT_SENDING = 3u
} can_msg_state_e;

//-------------QtSpeedometer-------------------
#define MIN_SPEEDOMETER_ANGLE 0
#define MAX_SPEEDOMETER_ANGLE 140
#define SPEEDOMETER_FACTOR 0.00390625
#define SPEEDOMETER_ANGLE 1.5
#define QTSPEEDOMETER_GAUGE_FILTER_WINDOW_SIZE 7
//-------------QtAirpressure-------------------
#define AIRPRESSURE_FACTOR 8
#define AIRPRESSURE_MIN_ANGLE (36)
#define AIRPRESSURE_MAX_ANGLE (144) //(152)
#define AIRPRESSURE_ANGLE (18) // (19)
//-------------QtEnginemeter-------------------
#define MIN_ENGINESPEED_ANGLE 0
#define MAX_ENGINESPEED_ANGLE 3500
#define ENGINESPEED_FACTOR 0.125
#define ENGINESPEED_ANGLE 6
#define QTENGINEMETER_GAUGE_FILTER_WINDOW_SIZE 7
//-------------QtCentralDashboard--------------
#define QTCENTRALDASHBOARD_MIN_TEMPERATURE 0
#define OFFSET 5
#define INDEX 11
#define MENU_RU_FILENAME "menu_ru"
#define TRANSLATOR_DIRECTORY ":/Translator"
#define MILEAGE "MILEAGE"
#define DAILY_FUEL_CONSUMPTION "DAILY_FUEL_CONSUMPTION"
#define TRIP_DISTANCE "TRIP_DISTANCE"
#define PRESSURE_UOM "PRESSURE_UOM"
#define ENGINE_UOM "ENGINE_UOM"
#define SPEED_UOM "SPEED_UOM"
#define FUEL_CONSUMPTION "FUEL_CONSUMPTION"
#define FUEL_LEVEL "FUEL_LEVEL"
#define ENGINE_COOLANT_TEMPERATURE "ENGINE_COOLANT_TEMPERATURE"
#define BATTERY_AMPERE "BATTERY_AMPERE"
#define BATTERY_VOLTAGE "BATTERY_VOLTAGE"
#define TEMP_SENS_PASSENGER_COMPARTMENT "TEMP_SENS_PASSENGER_COMPARTMENT"
#define GEAR_PARKING "GEAR_PARKING"
#define GEAR_REVERSE "GEAR_REVERSE"
#define GEAR_NEUTRAL "GEAR_NEUTRAL"
#define GEAR_DRIVING "GEAR_DRIVING"
#define GEAR_STATE_OFF "OFF"
#define NA_VALUE "0.0 "
#define UOM_DEGREE_CELCIUS " °C"
#define UOM_PERCENTAGE " %"
#define LANGUAGE_ENGLISH "ENGLISH"
#define LANGUAGE_RUSSIAN "RUSSIAN"
//-------VDHR-----
#define TRIP_DISTANCE_FACTOR 5
#define METER_TO_KM_CONVERTOR 1000
#define AVERAGE_OF_CUR1_CUR2 2
#define CBCU2_FUELLEVEL_SENSOR_1FACTOR (0.4)
#define CBCU2_CBCU_MAINPWRFACTOR 0.1
#define DYN_BB_CURRENT_CURRENT_1FACTOR (0.1)
#define DYN_BB_CURRENT_CURRENT_2FACTOR (0.1)
#define DD_INFO1_FUELLEVEL1FACTOR (0.4)
#define DD_INFO1_FUELLEVEL1_ERROR 0xFA
#define AMB_AMBIENTAIRTEMPERATUREFACTOR (0.031250)
#define AMB_CANID_AMBIENTAIRTEMPERATURE_OFFSET (-273)

#define AMB_CANID_AMBIENTAIRTEMPERATURE_MAXIMUM 1734

#define INIT_VALUE "0"
#define INIT_COLOR_TRANSPARENT "transparent"

#define DTC_VALUE_SEPERATOR ":"
#define GEAR_OFF "OFF"
#define GEAR_ON "ON"

#define INVALID_VALUE "--"

typedef enum {
    QMLSTATE_INPROGRESS,
    QMLSTATE_LOADING_COMPLETED,
    QMLSTATE_NORMAL,
    QMLSTATE_MENU,
    QMLSTATE_REFRESH,
} QmlState;

typedef enum {
    DOOR_STATUS_CLOSED,
    DOOR_STATUS_REQUEST,
    DOOR_STATUS_OPENING,
    DOOR_STATUS_OPENED,
    DOOR_STATUS_CLOSING,
    DOOR_STATUS_OBSTACLE_DETECT,
    DOOR_STATUS_ERROR,
    DOOR_STATUS_LOCKED2,
    DOOR_STATUS_RESERVED,
    DOOR_STATUS_RESTRICT_OPEN_DOOR,
    DOOR_STATUS_NA,
} DoorStatus;

//Declaring of structure for data elements
typedef struct data_ele {
    data_ele()
        : id(0)
        , autoUpdate(true)
        , updateIfChanged(true)
    {
    }

    int id;
    /* application to configure if they want app to update dynamic data
     * associated with screen
     * on screen change automatically. Default is true. Application need to set it
     * to false if it
     * dont want app to send this dynamic data on screen change*/
    bool autoUpdate;
    /*By default App will send data update to HMI only if its value is
     * changed.
     * Application to set this to false in case data needs to be send to HMI
     * irrespective of
     * value is changed or not*/
    bool updateIfChanged;

    /* As the name indicates a variant is able to store and retrieve all basic types.
     * In addition this class also supports storing strings */
    //    custom_datatypes_t value;
    string value;

    string visibility;
    string color;
    uint8_t position;
    uint8_t priority;
    string path;

    DoorStatus door_status;

    bool msg_status;

} data_ele_t;

typedef struct {
    string telltale_name;
    uint8_t telltale_value;
} TelltalesDataStr;

typedef struct {
    string popup_name;
    uint8_t popup_value;
} PopupDataStr;

typedef struct
{
    unsigned driveline_engaged              :2;
    unsigned torqu_conv_lockup_engaged      :2;
    unsigned shift_in_process               :2;
    unsigned                                :2;
    unsigned output_speed_TCU               :16;
    unsigned clutch_slip                    :8;
    unsigned meos_TCU                       :2;
    unsigned progressive_shift_disable      :2;
    unsigned PTO2_permission                :2;
    unsigned PTO1_permission                :2;
    unsigned input_speed                    :16;
    unsigned src_address_of_control_dev_eng :8;
} ETC1_t;

typedef struct
{
    uint64_t eng_torque_mode_spn899         :4;
    uint64_t act_eng_perc_tq_hi_res_spn4154 :4;
    uint64_t drv_demand_eng_perc_tq_spn512  :8;
    uint64_t act_eng_perc_tq_spn513         :8;
    uint64_t eng_speed                      :16;
    uint64_t src_adderss_spn1483            :8;
    uint64_t eng_starter_mode_spn1675       :4;
    uint64_t                                :4;
    uint64_t eng_demand_perc_tq_spn2432     :8;
} EEC1_t;

typedef struct
{
    unsigned nominal_level_front_axle           :4;
    unsigned nominal_level_rear_axle            :4;
    unsigned below_nominal_level_front_axle     :2;
    unsigned below_nominal_level_rear_axle      :2;
    unsigned above_nominal_level_front_axle     :2;
    unsigned above_nominal_level_rear_axle      :2;
    unsigned lowering_ctrl_mode_front_axle      :2;
    unsigned lowering_ctrl_mode_rear_axle       :2;
    unsigned lifting_ctrl_mode_front_axle       :2;
    unsigned lifting_ctrl_mode_rear_axle        :2;
    unsigned kneeling_information               :4;
    unsigned level_ctrl_mode                    :4;
    unsigned security_device                    :2;
    unsigned vehicle_motion_inhibit             :2;
    unsigned door_release                       :2;
    unsigned lift_axle1_pos                     :2;
    unsigned front_axle_in_bumper_range         :2;
    unsigned rear_axle_in_bumper_range          :2;
    unsigned lift_axle2_pos                     :2;
    unsigned suspension_remote_ctrl1            :2;
    unsigned suspension_remote_ctrl2            :2;
    unsigned allow_lvl_ctrl_during_brk_sts      :2;
    unsigned speed_dependant_lvl_ctrl_sts       :2;
    unsigned suspension_ctrl_refusal_info       :4;
    unsigned memory_level                       :4;
} ASC1_t;

typedef struct
{
    unsigned driver1_working_state          :3;
    unsigned driver2_working_state          :3;
    unsigned vehicle_motion                 :2;
    unsigned driver1_time_related_states    :4;
    unsigned driver_card_driver1            :2;
    unsigned vehicle_overspeed              :2;
    unsigned driver2_time_related_states    :4;
    unsigned driver_card_driver2            :2;
    unsigned                                :2;
    unsigned system_event                   :2;
    unsigned handling_information           :2;
    unsigned tachograph_perfomance          :2;
    unsigned direction_indicator            :2;
    unsigned tachograph_out_shaft_speed     :16;
    unsigned tachograph_vehicle_speed       :16;
}TCO1_t;

typedef struct
{
    unsigned                            :13;
    unsigned zero_speed                 :1;
    unsigned                            :2;
    unsigned headway_valid              :1;
    unsigned headway_measurement        :7;
    unsigned error_valid                :1;
    unsigned                            :7;
    unsigned ldw_off                    :1;
    unsigned left_ldw_on                :1;
    unsigned right_ldw_on               :1;
    unsigned fcw_on                     :1;
    unsigned left_lane_recognized       :1;
    unsigned right_lane_recognized      :1;
    unsigned                            :1;
    unsigned failsafe                   :1;
    unsigned                            :1;
    unsigned peds_fcw                   :1;
    unsigned peds_in_dz                 :1;
    unsigned                            :2;
    unsigned tamper_alert               :1;
    unsigned reserved                   :1;
} ADAS_600_t;

typedef struct
{
    unsigned brakes             :1;
    unsigned left_signal        :1;
    unsigned right_signal       :1;
    unsigned                    :12;
    unsigned speed_available    :1;
    unsigned speed              :8;
    unsigned slr_state          :8;
    unsigned slr_recognize      :8;
    unsigned slr_sensitivity    :8;
} VehicleData_620_t;

typedef struct
{
    unsigned auxi_084                       :2;
    unsigned auxi_083                       :2;
    unsigned auxi_082                       :2;
    unsigned auxi_081                       :2;
    unsigned auxi_O88_button06_right_state  :2;
    unsigned auxi_O87_button02_left_state   :2;
    unsigned auxi_O86_button01_back_state   :2;
    unsigned auxi_O85_button03_up_state     :2;
    unsigned auxi_O92_button05_ok_state     :2;
    unsigned auxi_O91_button04_down_state   :2;
    unsigned auxi_090_button_accept_state   :2;
    unsigned auxi_089_button_mode_state     :2;
    unsigned auxi_096_button_reserve2_state :2;
    unsigned auxi_095_button_reserve_state  :2;
    unsigned auxi_094                       :2;
    unsigned auxi_093                       :2;
    unsigned auxi_100                       :2;
    unsigned auxi_99                        :2;
    unsigned auxi_98                        :2;
    unsigned auxi_97                        :2;
    unsigned auxi_104                       :2;
    unsigned auxi_103                       :2;
    unsigned auxi_102                       :2;
    unsigned auxi_101                       :2;
    unsigned auxi_108                       :2;
    unsigned auxi_107                       :2;
    unsigned auxi_106                       :2;
    unsigned auxi_105                       :2;
    unsigned auxi_112                       :2;
    unsigned auxi_111                       :2;
    unsigned auxi_110                       :2;
    unsigned auxi_109                       :2;
} AUXIO4_75_t;

typedef struct
{
    unsigned                                        :8;
    unsigned swtch_bcklight_illmtn_brghtnss_prcnt   :8;
}CL_t;

typedef struct
{
    unsigned asotpremote    :8;
    unsigned asotpmode      :8;
    unsigned asotpin1       :4;
    unsigned asotpin2       :4;
    unsigned asotpin3       :4;
    unsigned asotpin4       :4;
    unsigned asotpout1      :4;
    unsigned asotpout2      :4;
    unsigned asotpout3      :4;
    unsigned asotpout4      :4;
    unsigned asotpbtn1      :8;
    unsigned asotpbtn2      :8;
} Relay_t;

typedef struct
{
    unsigned                        :32;
    unsigned programming_sequence   :16;
    unsigned                        :12;
    unsigned msg_chksum             :4;
}SAS_CFG_t;

typedef struct
{
    unsigned asr_engine_control_active          :2;
    unsigned asr_brake_contro_active            :2;
    unsigned anti_lock_braking_active           :2;
    unsigned ebs_brake_switch                   :2;
    unsigned brake_pedal_position               :8;
    unsigned abs_offRoad_switch                 :2;
    unsigned asr_off_road_switch                :2;
    unsigned asr_hill_holder_switch             :2;
    unsigned traction_control_override_switch   :2;
    unsigned accelerator_interlock_switch       :2;
    unsigned engine_derate_switch               :2;
    unsigned engine_auxiliary_shutdown_switch   :2;
    unsigned remote_accelerator_enable_switch   :2;
    unsigned engine_retarder_selection          :8;
    unsigned abs_fully_operational              :2;
    unsigned ebs_red_warning_signal             :2;
    unsigned absebs_amber_warning_signal        :2;
    unsigned atcasr_information_signal          :2;
    unsigned source_addres_controlling_brk_ctrl :8;
    unsigned                                    :2;
    unsigned halt_break_switch                  :2;
    unsigned trailer_abs_status                 :2;
    unsigned tractor_mounted_trailer_warningsign:2;
} EBC1_t;

typedef struct
{
    unsigned steering_wheel_angle               :16;
    unsigned steering_wheel_counter             :6;
    unsigned steering_wheel_angle_sensor_type   :2;
    unsigned                                    :8;
    unsigned steering_wheel_angle_range         :16;
    unsigned active_mode                        :2;
    unsigned sas_calibrated                     :2;
    unsigned message_counter                    :4;
    unsigned message_checksum                   :4;
} SAS_t;

typedef struct
{
    //door1
    unsigned door1_closed                   :1;
    unsigned door1_request                  :1;
    unsigned door1_opening                  :1;
    unsigned door1_opened                   :1;
    unsigned door1_closing                  :1;
    unsigned door1_locked                   :1;
    unsigned door1_error                    :1;
    unsigned door1_locked2                  :1;
    unsigned eeprom_par_proviu              :1;
    //door2
    unsigned door2_closed                   :1;
    unsigned door2_request                  :1;
    unsigned door2_opening                  :1;
    unsigned door2_opened                   :1;
    unsigned door2_closing                  :1;
    unsigned door2_locked                   :1;
    unsigned door2_error                    :1;
    unsigned door2_locked2                  :1;
    unsigned door2_reserved                 :1;
    //door3
    unsigned door3_closed                   :1;
    unsigned door3_request                  :1;
    unsigned door3_opening                  :1;
    unsigned door3_opened                   :1;
    unsigned door3_closing                  :1;
    unsigned door3_locked                   :1;
    unsigned door3_error                    :1;
    unsigned door3_locked2                  :1;
    unsigned door3_reserved                 :1;
    //door4
    unsigned door4_closed                   :1;
    unsigned door4_request                  :1;
    unsigned door4_opening                  :1;
    unsigned door4_opened                   :1;
    unsigned door4_closing                  :1;

    unsigned heater_valve_9                  :1;

    unsigned door4_locked                   :1;
    unsigned door4_error                    :1;
    unsigned door4_locked2                  :1;
    unsigned door4_reserved                 :1;

    unsigned restrict_opendoor_1            :1;
    unsigned restrict_opendoor_2            :1;
    unsigned restrict_opendoor_3            :1;
    unsigned door1_apparel                  :1;
    unsigned invalid_call                   :1;
    unsigned direction_indication           :1;
    unsigned frontalac_recirculation_damper :2;
    unsigned frontalac_coolant_damper       :2;
    unsigned restrict_opendoor_4            :1;
    unsigned door_sensorst_1_2              :8;
    unsigned door_sensorst_3_4              :8;
} DC2_t;

typedef struct
{
    unsigned working_light_switch               :4;
    unsigned main_light_switch                  :4;
    unsigned turn_signal_switch                 :4;
    unsigned hazard_lamp_status                 :2;
    unsigned high_low_beam_switch               :2;
    unsigned operators_desired_back_light       :8;
    unsigned operators_desired_delayed_lamp_off :16;
}OEL_t;

typedef struct
{
    unsigned dc1_position_of_doors              :4;
    unsigned ramp_lift_position                 :2;
    unsigned frontAC_recirculation_damper_st    :1;
    unsigned driver_presence                    :1;
    unsigned rightturnsignallightscommand       :1;
    unsigned leftturnsignallightscommand        :1;
    unsigned ac_req                             :1;
    unsigned driverbelt                         :1;
    unsigned frontalac_automode                 :1;
    unsigned eeprom_par_addconvector            :1;
    unsigned                                    :2;
    unsigned zr_mainpower                       :8;
    unsigned doorcrane1_2                       :8;
    unsigned doorcrane3_4                       :8;
    unsigned doorvalvest1_2                     :8;
    unsigned doorvalvest3_4                     :8;
} DC1_t;

typedef struct
{
    unsigned aftr_trtmnt1dsl_exhst_fluid_tank_level     :8;
    unsigned aftr_trtmnt1dsl_exhst_fluid_tank_emp       :8;
    unsigned aftr_trtmnt1dsl_exhst_fluid_tank_level2    :16;
    unsigned aftr_trtmnt1dsl_exhst_fluid_tank_lvl_prlm  :5;
    unsigned aftr_trtmnt1slctv_ctlytc_rdctn_oprtr_i     :3;
    unsigned aftr_trtmnt1dsl_exhst_fluid_tank_1_tmp_prl :5;
    unsigned aftr_trtmnt1_scr_oprtr_indcmnt_sverity     :3;
    unsigned aftr_trtmnt1dsl_exhst_fluid_tank_heater    :8;
    unsigned aftr_trtmnt1dsl_exhst_fluid_tank1_htr_prl  :5;
} AT1T1I_t;

typedef struct
{
    unsigned pneumatic_supply_pressure          :8;
    unsigned parking_airpressure                :8;
    unsigned service_brake_airpressure_circuit1 :8;
    unsigned service_brake_airpressure_circuit2 :8;
    unsigned auxilary_equipment_supplypressure  :8;
    unsigned air_suspension_supply_press        :8;
    unsigned air_compressor_status              :2;
    unsigned                                    :6;
    unsigned powertrain_circuit_air_supply_press:8;
} AIR1_t;

typedef struct
{
    uint64_t spn917_high_resolution_total   :32;
    uint64_t spn918_high_resolution_trip_di :32;
} VDHR_EE_t;

//TODO:DM1_**_t struct of bit-fields
typedef struct
{
    //m1_id1
    unsigned m1_id1_gp1         :1;
    unsigned m1_id1_gp2         :1;
    unsigned m1_id1_gp3         :1;
    unsigned m1_id1_gp4         :1;
    unsigned m1_id1_gp5         :1;
    //m1_id2
    unsigned m1_id2_gp1         :1;
    unsigned m1_id2_gp2         :1;
    unsigned m1_id2_gp3         :1;
    unsigned m1_id2_gp4         :1;
    unsigned m1_id2_gp5         :1;
    //m1_id3
    unsigned m1_id3_gp1         :1;
    unsigned m1_id3_gp2         :1;
    unsigned m1_id3_gp3         :1;
    unsigned m1_id3_gp4         :1;
    unsigned m1_id3_gp5         :1;
    //m1_id4
    unsigned m1_id4_gp1         :1;
    unsigned m1_id4_gp2         :1;
    unsigned m1_id4_gp3         :1;
    unsigned m1_id4_gp4         :1;
    unsigned m1_id4_gp5         :1;
    //m1_id5
    unsigned m1_id5_gp1         :1;
    unsigned m1_id5_gp2         :1;
    unsigned m1_id5_gp3         :1;
    unsigned m1_id5_gp4         :1;
    unsigned m1_id5_gp5         :1;
    //m1_id6
    unsigned m1_id6_gp1         :1;
    unsigned m1_id6_gp2         :1;
    unsigned m1_id6_gp3         :1;
    unsigned m1_id6_gp4         :1;
    unsigned m1_id6_gp5         :1;
    //m2_id2
    unsigned m2_id2_gp1         :1;
    unsigned m2_id2_gp2         :1;
    unsigned m2_id2_gp3         :1;
    unsigned m2_id2_gp4         :1;
    unsigned m2_id2_gp5         :1;
    //m2_id4
    unsigned m2_id4_gp1         :1;
    unsigned m2_id4_gp2         :1;
    unsigned m2_id4_gp3         :1;
    unsigned m2_id4_gp4         :1;
    unsigned m2_id4_gp5         :1;
    //m2_id6
    unsigned m2_id6_gp1         :1;
    unsigned m2_id6_gp2         :1;
    unsigned m2_id6_gp3         :1;
    unsigned m2_id6_gp4         :1;
    unsigned m2_id6_gp5         :1;

    unsigned conditioner_heating:1;
    unsigned conditioner_cooling:1;
    unsigned big_heater_door2   :1;
    unsigned washer_level       :8;
    unsigned temp_salon_module4 :8;
} LS_t;

typedef struct
{
    unsigned customer_id        :8;
    unsigned project_id         :16;
    unsigned hardware_id        :8;
    unsigned function_id        :8;
    unsigned platform_id        :8;
    unsigned version_id         :16;
}SOFT_IC12_t, SOFT_ZR_t, SOFT_ZKSH_t, SOFT_PV_t;

typedef struct
{
    unsigned nmbr_of_sftwre_identification_fields   :8;
    unsigned swid_steering_wheel_test               :8;
    uint64_t swid_steering_wheel_release            :48;
}SOFT_STEERING_WHEEL_t;

typedef struct
{
    unsigned seconds            :8;
    unsigned minutes            :8;
    unsigned hours              :8;
    unsigned month              :8;
    unsigned day                :8;
    unsigned year               :8;
    unsigned local_minute_offset:8;
    unsigned local_hour_offset  :8;
} TD_t;

typedef struct
{
    unsigned engine_coolant_temperature             :8;
    unsigned                                        :8;
    unsigned SPN175_engine_oil_temperature          :16;
    unsigned                                        :24;
    unsigned eng_charge_air_cooler_thermo_opening   :8;
} ET1_t;

typedef struct
{
    unsigned eng_fuel_delivery_press        :8;
    unsigned eng_ex_crankcase_blow_by_press :8;
    unsigned eng_oil_level                  :8;
    unsigned engine_oilpressure             :8;
    unsigned eng_crankcase_press            :16;
    unsigned eng_coolant_press              :8;
    unsigned eng_coolant_level              :8;
} EFL_P1_t;

typedef struct
{
    unsigned two_speed_axle_switch          :2;
    unsigned parking_brake_switch           :2;
    unsigned cruise_ctrl_pause_switch       :2;
    unsigned park_brake_release_inhibit_rq  :2;
    unsigned wheel_based_vehicle_speed      :16;
    unsigned cruise_ctrl_active             :2;
    unsigned cruise_ctrl_enable_switch      :2;
    unsigned brake_switch                   :2;
    unsigned clutch_switch                  :2;
    unsigned cruise_ctrl_set_switch         :2;
    unsigned cruise_ctrl_coast_switch       :2;
    unsigned cruise_ctrl_resume_switch      :2;
    unsigned cruise_ctrl_accelerate_switch  :2;
    unsigned cruise_ctrl_set_speed          :8;
    unsigned pto_governor_state             :5;
    unsigned cruise_ctr_states              :3;
    unsigned eng_idle_increment_switch      :2;
    unsigned eng_idle_decrement_switch      :2;
    unsigned eng_test_mode_switch           :2;
} CCVS1_t;

typedef struct
{
    unsigned engine_flue_rate                   :16;
    unsigned engine_instantabneous_fuel_economy :16;
    unsigned engine_average_fuel_economy        :16;
    unsigned engine_throttle_valve1_position1   :8;
    unsigned engine_throttle_valve2_position   :8;
} LFE1_t;

typedef struct
{
    unsigned spn929_tire_location               :8;
    unsigned spn241_tire_pressure               :8;
    unsigned spn242_tire_temperature            :16;
    unsigned spn1699_cti_tire_sensenable_status :2;
    unsigned spn1698_cti_tire_status            :2;
    unsigned spn1697_cti_tire_senselectr_fault  :2;
    unsigned spn6990_extended_tire_pres_support :2;
    unsigned spn2586_tire_air_leakage_rate      :16;
    unsigned                                    :5;
    unsigned spn2587_tire_pres_threshold_detect :3;
} TIRE_t;
/*
typedef struct
{
    unsigned barometric_pressure        :8;
    unsigned cab_interior_temperature   :16;
    unsigned ambient_air_temperature    :16;
    unsigned engine_intake_airtemp      :8;
    unsigned road_surface_temperature   :16;
} AMB_t;
*/
typedef struct
{
    uint64_t barometric_pressure        :8;
    uint64_t cab_interior_temperature   :16;
    uint64_t ambient_air_temperature    :16;
    uint64_t engine_intake_airtemp      :8;
    uint64_t road_surface_temperature   :16;
} AMB_t;

typedef struct
{
    uint64_t clutch_press                           :8;
    uint64_t trans_oil_level1                       :8;
    uint64_t trans_filter_diff_press                :8;
    uint64_t trans_oil_press                        :8;
    uint64_t trans_oil_temp1                        :16;
    uint64_t trans_oil_level1_high_low              :8;
    uint64_t trans_oil_level1_countdown_timer       :4;
    uint64_t trans_oil_level1_measurement_status    :4;
} TRF1_t;

typedef struct
{
    unsigned hyd_retarder_press                     :8;
    unsigned hyd_retarder_oil_temp                  :8;
    unsigned drvline_retarder_overheat_indicator    :2;
} RF_t;

typedef struct
{
    unsigned current_1  :16;
    unsigned current_2  :16;
} DYN_BB_CURRENT_t;

typedef struct
{
    unsigned A01    :2;
    unsigned A02    :2;
    unsigned A05    :2;
    unsigned A06    :2;
    unsigned A09    :2;
    unsigned A27    :2;
    unsigned A37    :2;
    unsigned A40    :2;
    unsigned A41    :2;
    unsigned A42    :2;
    unsigned A21    :2;
    unsigned A43    :2;
    unsigned A46    :2;
    unsigned A47    :2;
    unsigned A48    :2;
    unsigned A49    :2;
    unsigned A50    :2;
    unsigned A51    :2;
    unsigned A52    :2;
    unsigned A53    :2;
    unsigned A14    :2;
    unsigned A38    :2;
    unsigned A24    :2;
} TT_GRP_A_t;

typedef struct
{
    unsigned B01    :2;
    unsigned B02    :2;
    unsigned B03    :2;
    unsigned B04    :2;
    unsigned B05    :2;
    unsigned B10    :2;
    unsigned B14    :2;
    unsigned B15    :2;
    unsigned B21    :2;
    unsigned B22    :2;
    unsigned B23    :2;
    unsigned B24    :2;
    unsigned B25    :2;
    unsigned B26    :2;
} TT_GRP_B_t;

typedef struct
{
    unsigned C02    :2;
    unsigned C25    :2;
    unsigned C26    :2;
    unsigned C27    :2;
    unsigned C28    :2;
    unsigned C29    :2;
    unsigned C30    :2;
    unsigned C31    :2;
    unsigned C07    :2;
    unsigned C18    :2;
} TT_GRP_C_t;

typedef struct
{
    unsigned D31    :2;
    unsigned D44    :2;
    unsigned D45    :2;
    unsigned D46    :2;
    unsigned D47    :2;
    unsigned D48    :2;
    unsigned D49    :2;
    unsigned D50    :2;
    unsigned D51    :2;
} TT_GRP_D_t;

typedef struct
{
    unsigned E15    :2;
    unsigned E16    :2;
    unsigned E17    :2;
    unsigned E18    :2;
    unsigned E19    :2;
    unsigned E20    :2;
} TT_GRP_E_t;

typedef struct
{
    unsigned F01    :2;
    unsigned F02    :2;
    unsigned F03    :2;
    unsigned F04    :2;
    unsigned F05    :2;
    unsigned F10    :2;
    unsigned F15    :2;
    unsigned F16    :2;
    unsigned F30    :2;
    unsigned F31    :2;
    unsigned F32    :2;
    unsigned F33    :2;
    unsigned F34    :2;
    unsigned F35    :2;
    unsigned F36    :2;
    unsigned F23    :2;
    unsigned F19    :2;
    unsigned F18    :2;
    unsigned F22    :2;
} TT_GRP_F_t;

typedef struct
{
    unsigned acces_use_menu :1;
    unsigned msg_01         :1;
    unsigned msg_02         :1;
    unsigned msg_03         :1;
    unsigned msg_04         :1;
    unsigned msg_05         :1;
    unsigned msg_06         :1;
    unsigned msg_07         :1;
    unsigned msg_08         :1;
    unsigned msg_09         :1;
    unsigned msg_10         :1;
    unsigned msg_11         :1;
    unsigned msg_12         :1;
    unsigned msg_13         :1;
    unsigned msg_14         :1;
    unsigned msg_15         :1;
    unsigned msg_16         :1;
    unsigned msg_17         :1;
    unsigned msg_18         :1;
    unsigned msg_19         :1;
    unsigned msg_20         :1;
    uint64_t                :35;
    unsigned fuel_level1    :8;
} DD_INFO1_t;

typedef struct
{
    unsigned black_box_event_type       :4;
    unsigned black_box_event_number     :4;
    unsigned black_box_event_counter    :16;
    unsigned minutes                    :8;
    unsigned hours                      :8;
    unsigned month                      :8;
    unsigned day                        :8;
    unsigned year                       :8;
}DD_INFO2_t;

typedef union{
    struct {
        //parameters
        uint64_t parameters_engine_submenu          :5;
        uint64_t parameters_transmission_submenu    :3;
        uint64_t parameters_battery_submenu         :3;
        uint64_t parameters_pneumatic_submenu       :5;
        uint64_t parameters_adblue_submenu          :2;
        uint64_t parameters_wipers_submenu          :2;

        //settings
        uint64_t settings_climate_ctrl_driver_submenu   :3;
        uint64_t settings_light_rain_sensor_submenu     :4;
        uint64_t settings_heating_system_submenu        :3;
        uint64_t settings_dash_board_submenu            :3;
        uint64_t                                        :1;

        //service
        uint64_t service_software_version_submenu       :4;
        uint64_t service_add_func_submenu               :2;
        uint64_t service_wipers_submenu                 :2;
        uint64_t                                        :6;
        uint64_t service_steering_angle_sens_submenu    :1;
        uint64_t service_data_source_submenu            :1;
        uint64_t service_dtc_submenu                    :1;
        uint64_t service_door_management_submenu        :1;
        uint64_t service_change_password_submenu        :1;

        //diagnostics
        uint64_t diagnostics_emergency_hammers_submenu      :1;
        uint64_t diagnostics_door_sensors_submenu           :1;
        uint64_t diagnostics_emergency_cranes_submenu       :1;
        uint64_t diagnostics_heaters_submenu                :1;
        uint64_t diagnostics_fire_extinguishers_submenu     :1;
        uint64_t diagnostics_lighting_equipements_submenu   :1;
        uint64_t diagnostics_door_valves_submenu            :1;
        uint64_t diagnostics_heating_sys_valves_submenu     :1;
        uint64_t diagnostics_failures_submenu               :1;

        //
        uint64_t parameters_brake_pads_wear_submenu         :1;
        uint64_t parameters_tire_press_and_temp_submenu     :1;
    }bitfield;
    uint64_t data;
}DD_INFO3_t;


typedef struct
{
    unsigned fuellevel_sensor_1         :8;
    unsigned fuel_temp_sensor_1         :8;
    unsigned fuellevel_sensor_2         :8;
    unsigned fuel_temp_sensor_2         :8;
    //fs_dtc_spn96_fmi
    unsigned fs_dtc_spn_96_fmi_0        :1;
    unsigned fs_dtc_spn_96_fmi_1        :1;
    unsigned fs_dtc_spn_96_fmi_10       :1;
    unsigned fs_dtc_spn_96_fmi_13       :1;
    unsigned fs_dtc_spn_96_fmi_14       :1;
    //fs_dtc_spn38_fmi
    unsigned fs_dtc_spn_38_fmi_0        :1;
    unsigned fs_dtc_spn_38_fmi_1        :1;
    unsigned fs_dtc_spn_38_fmi_10       :1;
    unsigned fs_dtc_spn_38_fmi_13       :1;
    unsigned fs_dtc_spn_38_fmi_14       :1;

    unsigned heater_x_green_lamp        :1;
    unsigned heater_x_yellow_lamp       :1;
    unsigned heater_x_red_lamp          :1;
    unsigned heater_x_speed1            :1;
    unsigned heater_x_speed2            :1;
    unsigned reset_fuel_system          :1;
    unsigned cbcu_mainpwr               :16;
} CBCU2_t;

typedef struct
{
    unsigned G01    :2;
    unsigned G21    :2;
    unsigned G22    :2;
    unsigned G23    :2;
    unsigned G24    :2;
    unsigned G25    :2;
    unsigned G26    :2;
    unsigned G10    :2;
} TT_GRP_G_t;

typedef struct
{
    unsigned H01    :2;
    unsigned H02    :2;
    unsigned H03    :2;
    unsigned H04    :2;
    unsigned H05    :2;
} TT_GRP_H_t;

typedef struct
{
    unsigned I30    :2;
}TT_GRP_I_t;

typedef struct
{
    unsigned J07    :2;
} TT_GRP_J_t;

typedef struct
{
    unsigned K01    :2;
    unsigned K10    :2;
    unsigned K13    :2;
    unsigned K28    :2;
    unsigned K29    :2;
    unsigned K30    :2;
    unsigned K31    :2;
    unsigned K32    :2;
    unsigned K33    :2;
    unsigned K34    :2;
    unsigned K35    :2;
} TT_GRP_K_t;

typedef struct
{
    unsigned M01    :2;
} TT_GRP_M_t;

typedef struct
{
    unsigned P08    :2;
} TT_GRP_P_t;

typedef struct
{
    unsigned frontal_FU01                   :1;
    unsigned frontal_FU02                   :1;
    unsigned frontal_FU05                   :1;
    unsigned frontal_FU06                   :1;
    unsigned frontal_FU09                   :1;
    unsigned frontal_FU10                   :1;
    unsigned central_FU25                   :1;
    unsigned frontal_FU37                   :1;
    unsigned frontal_FU41                   :1;
    unsigned frontal_FU42                   :1;
    unsigned frontal_FU43                   :1;
    unsigned frontal_FU45                   :1;
    unsigned frontal_FU46                   :1;
    unsigned relay_DWP_green                :1;
    unsigned relay_DWP_red                  :1;
    unsigned relay_wipers_speed_green       :1;
    unsigned relay_wipers_speed_red         :1;
    unsigned relay_wipers_ctr_brk_green     :1;
    unsigned relay_wipers_ctr_brk_red       :1;
    unsigned EEPROM_par_cabin_light2_modes  :1;
    unsigned EEPROM_par_AdBlueEuro6         :1;
    unsigned EEPROM_par_euro6               :1;
    unsigned EEPROM_par_bus_6274_15         :1;
    unsigned EEPROM_par_bus_5292_MTA        :1;
    unsigned EEPROM_par_bus_model           :4;
    unsigned EEPROM_par_Heater_A_frontal    :1;
    unsigned EEPROM_par_Heater_F_Door2      :1;
    unsigned EEPROM_par_Heater_S_door3      :1;
    unsigned EEPROM_contactor_CAN_capatibility  :1;
    unsigned central_FU03                   :1;
    unsigned central_FU05                   :1;
    unsigned central_FU06                   :1;
    unsigned central_FU09                   :1;
    unsigned central_FU10                   :1;
    unsigned central_FU11                   :1;
    unsigned central_FU44                   :1;
    unsigned central_FU27                   :1;
    unsigned central_FU28                   :1;
    unsigned central_FU29                   :1;
    unsigned central_FU30                   :1;
    unsigned central_FU38                   :1;
    unsigned central_FU39                   :1;
    unsigned central_FU40                   :1;
    unsigned central_FU41                   :1;
    unsigned central_FU42                   :1;
    unsigned central_FU43                   :1;
    unsigned central_FU45                   :1;
    unsigned central_FU46                   :1;
    unsigned central_FU47                   :1;
    unsigned relay_K2_gray                  :1;
    unsigned relay_K2_green                 :1;
    unsigned relay_K2_red                   :1;
    unsigned relay_KL15_gray                :1;
    unsigned relay_KL15_green               :1;
    unsigned relay_KL15_red                 :1;
    unsigned relay_KL15Front_gray           :1;
    unsigned relay_KL15Front_green          :1;
    unsigned relay_KL15Front_red            :1;
    unsigned central_FU01                   :1;
    unsigned EEPROM_par_trainee_bus         :1;
    unsigned TT_washer_level                :1;
} FB1_t;

typedef struct
{
    unsigned heater_ag      :1;
    unsigned heater_ar      :1;
    unsigned heater_ay      :1;
    unsigned heater_bg      :1;
    unsigned heater_br      :1;
    unsigned heater_by      :1;
    unsigned heater_cg      :1;
    unsigned heater_cr      :1;
    unsigned heater_cy      :1;
    unsigned heater_dg      :1;
    unsigned heater_dr      :1;
    unsigned heater_dy      :1;
    unsigned heater_eg      :1;
    unsigned heater_er      :1;
    unsigned heater_ey      :1;
    unsigned heater_fg      :1;
    unsigned heater_fr      :1;
    unsigned heater_fy      :1;
    unsigned heater_gg      :1;
    unsigned heater_gr      :1;
    unsigned heater_gy      :1;
    unsigned heater_hg      :1;
    unsigned heater_hr      :1;
    unsigned heater_hy      :1;
    unsigned heater_sg      :1;
    unsigned heater_sr      :1;
    unsigned heater_sy      :1;
    unsigned fire1          :1;
    unsigned fire2          :1;
    unsigned fire3          :1;
    unsigned fire4          :1;
    unsigned fire5          :1;
    unsigned heater_speed_byte1 :8;
    unsigned heater_speed_byte2 :8;
    unsigned heater_speed_byte3 :8;
    unsigned heater_valve1  :1;
    unsigned heater_valve2  :1;
    unsigned heater_valve3  :1;
    unsigned heater_valve4  :1;
    unsigned heater_valve5  :1;
    unsigned heater_valve6  :1;
    unsigned heater_valve7  :1;
    unsigned heater_valve8  :1;
} FB3_t;

typedef struct
{
    unsigned hammer_1                   :1;
    unsigned hammer_2                   :1;
    unsigned hammer_3                   :1;
    unsigned hammer_4                   :1;
    unsigned RLS_not_connection         :1;
    unsigned hammer_5                   :1;
    unsigned AC_cooling                 :1;
    unsigned AC_heating                 :1;
    unsigned wipers_count               :16;
    unsigned temp_sens_passenger_compt  :8;
    unsigned                            :24;
    unsigned temp_sens_cabin            :8;
} D1_t;

typedef struct
{
    unsigned trip_group1                        :2;
    unsigned trip_group2_proprietary            :2;
    unsigned                                    :4;
    unsigned service_component_identification   :8;
    unsigned eng_build_hours_reset              :2;
    unsigned steer_straight_ahead_pos_reset     :2;
}RESET_t;

typedef struct
{
    unsigned brk_lnng_rmining_front_axle_left_wheel     :8;
    unsigned brk_lnng_rmining_front_axle_right_wheel    :8;
    unsigned brk_lnng_rmining_rear_axle1_left_wheel     :8;
    unsigned brk_lnng_rmining_rear_axle1_right_wheel    :8;
    unsigned brk_lnng_rmining_rear_axle2_left_wheel     :8;
    unsigned brk_lnng_rmining_rear_axle2_right_wheel    :8;
    unsigned brk_lnng_rmining_rear_axle3_left_wheel     :8;
    unsigned brk_lnng_rmining_rear_axle3_right_wheel    :8;
} EBC4_t;

typedef struct
{
    uint64_t selected_gear                  :8;
    uint64_t actual_gear_ratio              :16;
    uint64_t current_gear                   :8;
    uint64_t transmission_requested_range   :16;
    uint64_t transmission_current_range     :16;
} ETC2_t;

typedef struct
{
    unsigned protect_lamp_status                :2;
    unsigned amber_warning_lamp_status          :2;
    unsigned red_stop_lamp_state                :2;
    unsigned malfunction_indicator_lamp_status  :2;
    unsigned flash_protect_lamp                 :2;
    unsigned flash_amber_warning_lamp           :2;
    unsigned flash_red_stop_lamp                :2;
    unsigned flash_malfunction_indicator_lamp   :2;
    unsigned dtc1                               :32;
    unsigned dtc2                               :32;
    unsigned dtc3                               :32;
    unsigned dtc4                               :32;
    unsigned dtc5                               :32;
} DM1_data_t;

typedef struct
{
    uint64_t setting_addressable_door_buttons           :1;
    uint64_t sensors_presence_passenger_doorway         :1;
    uint64_t automatic_on_alarm                         :1;
    uint64_t auto_kneeling                              :1;
    uint64_t auto_closing_drs_when_leaving_vehicle      :1;
    uint64_t auto_closing_doors_by_sensors              :1;
    uint64_t automatic_opening                          :1;
    uint64_t                                            :1;
    uint64_t servece_mode                               :1;
    uint64_t reset_number_activations                   :1;
    uint64_t removing_traffic_blocks                    :1;
    uint64_t turbo_timer                                :1;
    uint64_t black_box_event_request                    :4;
    uint64_t parking_lights                             :1;
    uint64_t low_beam_headlights                        :1;
    uint64_t high_beam_headlights                       :1;
    uint64_t direction_indicators                       :1;
    uint64_t daytime_running_lights                     :1;
    uint64_t fog_lights                                 :1;
    uint64_t rear_fog_lights                            :1;
    uint64_t reversing_lights                           :1;
    uint64_t stop_signal                                :1;
    uint64_t                                            :2;
    uint64_t reset_heater_errors                        :1;
    uint64_t unlocking_the_heater                       :1;
    uint64_t rain_sensitivity                           :3;
    uint64_t installation_temperature                   :8;
    uint64_t driver_installation_temperature            :8;
    uint64_t sensitivity_to_light                       :3;
    uint64_t auto_settings_low_beam                     :1;
    uint64_t auto_wiper_settings_mode                   :1;
    uint64_t                                            :11;
} DD_Settings_t;

#endif // APPTYPES_H
