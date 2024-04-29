#ifndef MENUSETTINGSHANDLER_H
#define MENUSETTINGSHANDLER_H

#include "../Connectivity/JSON/qtjsonconfiguredata.h"
#include "../Connectivity/hmi_handler.h"
#include "newmenuitems.h"
#include "../Common/menu_defines.h"
#include "QDebug"
#include <QMutexLocker>
#include <cstdint>
#include <stdint.h>
#include <stdlib.h>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include "../Logger/exception_define.h"
#include "./newmenuitems.h"

#define INIT_VALUE "0"
#define INIT_DASHBOARD_VOLUME_VALUE "10"
#define INIT_DASHBOARD_BRIGHTNES_VALUE "10"
#define STATE_OFF "OFF"
#define STATE_ON "ON"
#define INSTALLATION_TEMPERATURE_MIN_VALUE 16
#define INSTALLATION_TEMPERATURE_MAX_VALUE 26
#define RAIN_MASK_VALUE 7
#define LIGHT_MASK_VALUE 15

#define SENSITIVITY_LEVEL_1 "Sensitivity level 1"
#define SENSITIVITY_LEVEL_2 "Sensitivity level 2"
#define SENSITIVITY_LEVEL_3 "Sensitivity level 3"
#define SENSITIVITY_LEVEL_4 "Sensitivity level 4"

#define SENSITIVITY_0 "Sensitivity 0"
#define SENSITIVITY_1 "Sensitivity 1"
#define SENSITIVITY_2 "Sensitivity 2"
#define SENSITIVITY_3 "Sensitivity 3"
#define SENSITIVITY_4 "Sensitivity 4"
#define SENSITIVITY_5 "Sensitivity 5"
#define LANGUAGE_ENGLISH "ENGLISH"
#define AIR_INTAKE_FROM_INSIDE "AIR_INTAKE_FROM_INSIDE"
#define AIR_INTAKE_FROM_OUTSIDE "AIR_INTAKE_FROM_OUTSIDE"

#define VALID_VALUE 1
#define MINIMUM_VALUE_VOLUME 10
#define MAXIMUM_VALUE_VOLUME 100

#define MINIMUM_VALUE_SENSITIVITY_LIGHT 0
#define MAXIMUM_VALUE_SENSITIVITY_LIGHT 5

#define MINIMUM_VALUE_SENSITIVITY_RAIN 1
#define MAXIMUM_VALUE_SENSITIVITY_RAIN 4

#define ROUND_OFF_BRIGHTNESS(brightness_value) (((brightness_value) / 10) * 10)
#define ROUND_OFF_VOLUME(volume_value) (((volume_value) / 10) * 10)

using namespace std;
class MenuSettingsHandler : QObject , public ISubscriber{
public:
    static MenuSettingsHandler* get_instance(newMenuItems*);
    void update_settings_data();
    bool update_info(uint32_t) override;
private:
    MenuSettingsHandler(newMenuItems*);
    bool update_config_data(string config_data, string config_value);
    string get_config_file_data(string);
    void update_climate_control_driver_cab(void);
    //void update_dashboard(void);
    //string update_light_rain_sensor(string, uint8_t);
    void init_heating_system(void);
    void init_dashboard(void);
    void init_light_rain_sensor(void);
    void init_climate_control_driver_cab(void);
    void init_subscribe() override;

    static shared_ptr<MenuSettingsHandler> m_ptr_instance;
    static mutex m_build_mutex;
    QtJsonConfigureData* json_configure_data;
    HmiHandler* m_ptr_cached_msgs;
    newMenuItems* menu_settings_data;
    string send_key;
    string receive_config_value;
};

#endif // MENUSETTINGSHANDLER_H
