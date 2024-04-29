#pragma once
#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <tuple>
#include <QGuiApplication>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QTranslator>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../Connectivity/JSON/qtjsonmenuhandler.h"
#include "menu_services_handler.h"
#include "menu_settings_handler.h"
#include "newmenuitems.h"
#include "../Connectivity/hmi_handler.h"
#include "menu_diagnostics_handler.h"
#include "../subscribe_notifer.h"
#include "../Logger/exception_define.h"


using namespace std;

class MenuHandler : public ISubscriber {
public:
    ~MenuHandler();
    QtJsonMenuHandler* json_menu_handler;

    static MenuHandler* get_instance();

    void update_all_menu_data();

    bool update_info(uint32_t _id) override;
    void update_engine_data(void);
    void update_battery_data(void);
    qreal* get_daily_fuel_consumption();

    newMenuItems* init_menu_item_data(void);
    newMenuItems* get_menu_item_data(void);
    map<VehicleName, uint8_t> _vehicle_details;
    newMenuItems _menu_data;

private:
    MenuHandler();
    void init_subscribe() override;

    void update_parameterdata(void);

    QtJsonMenuHandler::JsonMenuData* init_any(int, QString);
    void init_any_data(string, uint8_t);
    void init_engine_data();
    void init_transmission_data();
    void init_battery_data();
    void init_pneumatic_data();
    void init_tirepress_temp_data();
    void init_brakepads_data();
    void init_wipers_data();
    void init_reagentadblue_data();
    void init_add_data_to_map(void);

    void update_transmission_data(void);
    void update_tyre_temperature_pressure_data(void);
    void update_brakepads_data(void);
    //void update_vehicle_type_data(void);
    void update_pneumatic_data(void);
    void update_wipers_data(void);
    void update_reagentadblue_data(void);

    void init_menu_parameter_data(void);
    void init_menu_diagnostics_data(void);
    void init_menu_settings_data(void);
    void init_menu_services_data(void);

    static mutex build_lock_mutex;
    static shared_ptr<MenuHandler> m_ptr_instance;

    MenuDiagnosticsHandler* menu_diagnostic_handler;
    MenuSettingsHandler* menu_settings_handler;
    MenuServicesHandler* menu_services_handler;
    HmiHandler* _update_data;

    AUXIO4_75_t* _button_data_fromcan;

    qreal _prev_avrg_inst;
    qreal _pavrg_100km;
    qreal _nvm;
};

#endif // MENUHANDLER_H
