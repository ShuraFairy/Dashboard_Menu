#ifndef NEWMENUITEMS_H
#define NEWMENUITEMS_H

#include "../Interfaces/IMenuNavigation.h"
#include "../Common/menu_items.h"
#include <optional>
#include <sstream>
#include <iomanip>
#include "../Connectivity/hmi_handler.h"
#include "../Interfaces/IMenuDrawer.h"

#define HEATING_SYSTEM "Heating System"
#define DASH_BOARD "Dashboard"
#define LIGHT_RAIN_SENSOR "Light Rain Sensor"
#define CLIMATE_CONTROL_DRIVER_CAB "Climate  Control Driver Cab"

#define MINIMUM_VALUE_BRIGHTNESS 10
#define MAXIMUM_VALUE_BRIGHTNESS 100
#define MINIMUM_INSTALLATION_TEMPERATURE 16
#define MAXIMUM_INSTALLATION_TEMPERATURE 26

enum eParamType
{
    E_PT_CONSTVALUE = 0,
    E_PT_DIAPASONE,
    E_PT_BOOLPARAM,
    E_PT_GROUP,
    E_PT_PASSWORD,
    E_PT_BRAKEPADS,
    E_PT_TIRES,
    E_PT_SENSOR,
    E_PT_VALVE,
    E_PT_CRANE,
    E_PT_HAMMER,
    E_PT_FIRE,
    E_PT_HEATER,
    E_PT_SYSTEM_HEATER,
    E_PT_IMAGE_VALUE,
    E_PT_DTC_CODE
};

enum eScreenLevels
{
    E_SL_DASH = 0,
    E_SL_MAIN,
    E_SL_LIST,
    E_SL_PARAMS,
    E_SL_SUBPARAMS,
    E_SL_PASSLOCK
};
typedef struct
{
    QString param_name;
    optional<QString> uom;
    optional<int> min_value;
    optional<int> max_value;
    optional<float> mid_value;
    optional<string> img_path;
    eParamType value_type;
    bool visibility;
    variant<string, bool, FailureModule, uint8_t, DtcModule> submenu_string;
}menu_string;

class submenu_window
{
public:
    submenu_window()
        : item_name()
        , visibility(true)
        {};
    string item_name;
    bool visibility;
    vector<variant<string, FailureModule, uint8_t, DtcModule>> submenu_string;
    vector<menu_string> opt_submenu_string;
};

class submenulist
{
public:
    submenulist() = default;
    string item_name;
    unordered_map<string, submenu_window> submenu_page;
};

class newMenuItems : public QObject, public IMenuNavigation, public ISubscriber
{
    Q_OBJECT
public:
    newMenuItems();
    virtual void change_level(bool) override;
    virtual void change_focus_item(eDirrection) override;
    bool update_info(uint32_t _id) override;

    void set_menu_drawer(IMenuDrawer* _ptr){m_ptr_menu_drawer = _ptr;};
    void get_left_list(QStringList*);
    void get_right_list(QList<QStringList>*, QStringList*);
    void get_value_list(QStringList*);
    void check_active_list(submenu_window*);
    void set_subitem_visibility(DD_INFO3_t _data_msg_dd_info3);

    uint8_t vehicle_type;
    VehicleName vehicle_name;
    QString str_on;
    QString str_off;
    QString str_rus;
    QString str_eng;
    QString str_close;
    QString str_open;
    QString str_recomendation;
    QString str_advice;
     submenulist submenus[E_MT_SUBMENU_TOTAL];

signals:
    void wrong_password();
    void focus_changed(int, int, int);
    void level_changed(int);
    void value_changed(bool);
    void language_change();

private:
    void init_subscribe() override;
    eParamType get_param_type(uint8_t);
    void set_bool_param();
    void set_diap_param(bool);
    bool check_pass(){return true;};
    void change_cached_value(uint8_t*, optional<uint8_t>, uint8_t, bool);
    void set_brightness(QString);
    vector<submenu_window*> m_ptr_left_list;
    vector<menu_string*> m_ptr_right_list;
    eScreenLevels m_esl_current;
    uint8_t m_cached_main_pos;
    uint8_t m_cached_list_pos;
    uint8_t m_list_limit;
    uint8_t m_cached_param_pos;
    uint8_t m_paramlist_limit;
    uint8_t m_cached_subparam_pos;
    uint8_t m_subparamlist_limit;
    uint8_t m_cached_pass_letter;
    string m_str_trypass;
    IMenuDrawer* m_ptr_menu_drawer;
    HmiHandler* m_ptr_msgs_handler;
    DD_INFO3_t m_data_from_msg_dd_info3;

};

#endif // NEWMENUITEMS_H
