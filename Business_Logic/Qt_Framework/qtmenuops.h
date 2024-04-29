#ifndef QTMENUOPS_H
#define QTMENUOPS_H

#include <utility>
#include "Business_Logic/navigation.h"
#include "QString"
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QMutexLocker>
#include <QTextStream>
#include <QTimer>
#include <string>
#include <unistd.h>
#include "qtpopup.h"
#include <QGuiApplication>
#include <QObject>
#include <QQuickView>
#include <QStringList>
#include <QThread>
#include <QTranslator>
#include <qmap.h>
#include "../subscribe_notifer.h"
#include "../Common/menu_defines.h"
#include "../Connectivity/JSON/qtjsonconfiguredata.h"
#include "../Interfaces/iobserverforrender.h"
#include "../Menu/menu_handler.h"
#include "../Connectivity/can_handler.h"
#include "../Logger/exception_define.h"

using namespace std;

#define IMPL_PROPERTY_WITH_NUMBER(name, container, i, key) \
    Q_PROPERTY(QList<QStringList> name##i READ get_##name##i WRITE set_##name##i NOTIFY name##i##_changed()); \
    public: \
        inline const QList<QStringList>& get_##name##i() const { return container.find(key)->second; } \
        inline void set_##name##i(const QList<QStringList>& value) \
        { \
            if (value != container[key]) \
            { \
                container[key] = value; \
                emit name##i##_changed();\
            }\
        }

#define IMPL_PROPERTY(name, container, key) \
    Q_PROPERTY(QList<QStringList> name READ get_##name WRITE set_##name NOTIFY name##_changed()); \
    public: \
        inline const QList<QStringList>& get_##name() const { return container.find(key)->second; } \
        inline void set_##name(const QList<QStringList>& value) \
        { \
            if (value != container[key]) \
            { \
                container[key] = (value);\
                emit name##_changed();\
            } \
        }
class QtMenuOps : public QObject, public IObserverForRender, public ISubscriber, public IMenuDrawer {
    Q_OBJECT
    Q_PROPERTY(int screen_state READ get_screen_state WRITE set_screen_state NOTIFY screen_state_changed)
    Q_PROPERTY(int main_menu_pos READ get_main_menu_pos WRITE set_main_menu_pos NOTIFY main_menu_pos_changed)
    Q_PROPERTY(int list_menu_pos READ get_list_menu_pos WRITE set_list_menu_pos NOTIFY list_menu_pos_changed)
    Q_PROPERTY(int param_menu_pos READ get_param_menu_pos WRITE set_param_menu_pos NOTIFY param_menu_pos_changed)
    Q_PROPERTY(QString type_of_vehicle READ get_type_of_vehicle WRITE set_type_of_vehicle NOTIFY type_of_vehicle_changed)
    Q_PROPERTY(QStringList main_menu_names READ get_main_menu_names WRITE set_main_menu_names NOTIFY main_menu_names_changed)
    Q_PROPERTY(QStringList sub_menu_names READ get_sub_menu_names WRITE set_sub_menu_names NOTIFY sub_menu_names_changed)
    Q_PROPERTY(QStringList right_menu_values_list READ get_right_menu_values_list WRITE set_right_menu_values_list NOTIFY right_menu_values_list_changed)
    Q_PROPERTY(QList<QStringList> param_menu_names READ get_param_menu_names WRITE set_param_menu_names NOTIFY param_menu_names_changed)

private:
    unordered_map<QString, QList<QStringList>> map_menu_data;
    //Streeing angle sensor
    IMPL_PROPERTY(menu_services_streering_sensor_n_degree, map_menu_data, N_DEGREE);
    IMPL_PROPERTY(menu_services_streering_sensor_m_value, map_menu_data, M_VALUE);
    IMPL_PROPERTY(menu_services_streering_sensor_instructions, map_menu_data, STEERING_INSTRUCTIONS);
    IMPL_PROPERTY(menu_services_streering_sensor_status, map_menu_data, STEERING_ANGLE_STATUS);
    //Data Source
    IMPL_PROPERTY(menu_services_tempelate1_droplist, map_menu_data, TEMPELATE1_DROPLIST);
    IMPL_PROPERTY(menu_services_tempelate2_droplist, map_menu_data, TEMPELATE2_DROPLIST);
    IMPL_PROPERTY(menu_services_tempelate3_droplist, map_menu_data, TEMPELATE3_DROPLIST);
    IMPL_PROPERTY(menu_services_tempelate4_droplist, map_menu_data, TEMPELATE4_DROPLIST);
    IMPL_PROPERTY(menu_services_tempelate5_droplist, map_menu_data, TEMPELATE5_DROPLIST);
    IMPL_PROPERTY(menu_services_tempelate6_droplist, map_menu_data, TEMPELATE6_DROPLIST);
    //Change Password
    IMPL_PROPERTY(menu_services_password_data, map_menu_data, PASSWORD_DATA);
    IMPL_PROPERTY(menu_services_change_pwd_valid_password, map_menu_data, VALID_PASSWORD);
    IMPL_PROPERTY(menu_services_change_pwd_new_password, map_menu_data, NEW_PASSWORD);
    IMPL_PROPERTY(menu_services_change_pwd_confirmation_password, map_menu_data, CONFIRMATION_PASSWORD);
    /*
    //Service software version
    IMPL_PROPERTY(menu_services_software_version_ec12, map_menu_data, EC12_SOFTWARE_VERSION);
    IMPL_PROPERTY(menu_services_software_version_cc, map_menu_data, CC_SOFTWARE_VERSION);
    IMPL_PROPERTY(menu_services_software_version_redp, map_menu_data, REDP_SOFTWARE_VERSION);
    IMPL_PROPERTY(menu_services_software_version_res, map_menu_data, RES_SOFTWARE_VERSION);
*/
    //UDS
    Q_PROPERTY(bool menu_screen_visibility READ get_menu_screen_visibility WRITE set_menu_screen_visibility NOTIFY menu_screen_visibility_changed)
    //PASSWORD
    Q_PROPERTY(QString valid_password_not_match READ get_valid_password_not_match WRITE set_valid_password_not_match NOTIFY valid_password_not_match_changed)
    Q_PROPERTY(QString new_password_not_match READ get_new_password_not_match WRITE set_new_password_not_match NOTIFY new_password_not_match_changed)
    Q_PROPERTY(QString new_password_update READ get_new_password_update WRITE set_new_password_update NOTIFY new_password_update_changed)
    Q_PROPERTY(QString new_password_update_failed READ get_new_password_update_failed WRITE set_new_password_update_failed NOTIFY new_password_update_failed_changed)
public:
    explicit QtMenuOps(QObject* parent = nullptr);
    ~QtMenuOps();
    typedef void (QtMenuOps:: *set_operation)(const QList<QStringList>&);
    typedef struct {
        uint32_t can_id;
        uint16_t timer_prescribed;
        uint16_t counter;
        char can_frame_name[15];
        bool flag;
    } TimerHandlerData;

    typedef struct {
        QString menu_items;
        QString invalid_value;
        QString init_value;
    } MenuItemData;

    DD_Settings_t dd_settings;

    typedef void (QtMenuOps::*menu_slot)(const QList<QStringList>&);

    static QtMenuOps* getInstance();

    const int& get_screen_state() const;
    void set_screen_state(const int& newState);

    const int& get_main_menu_pos() const;
    void set_main_menu_pos(const int& newState);

    const int& get_list_menu_pos() const;
    void set_list_menu_pos(const int& newState);

    const int& get_param_menu_pos() const;
    void set_param_menu_pos(const int& newState);

    void set_popup(QtPopUpWindow* ptrpopupwindow);

    void update_gui() override;
    bool update_info(uint32_t _id) override;

    const QString& get_type_of_vehicle() const;
    void set_type_of_vehicle(const QString& newType_of_vehicle);

    const QList<QStringList>& get_menu_services_software_version_sub_item_no() const;
    void set_menu_services_software_version_sub_item_no(const QList<QStringList>& newMenu_services_software_version_sub_item_no);

    const QList<QStringList>& get_menu_services_software_version_sub_item_name() const;
    void set_menu_services_software_version_sub_item_name(const QList<QStringList>& newMenu_services_software_version_sub_item_name);

    const QList<QStringList>& get_menu_services_software_version_client_id() const;
    void set_menu_services_software_version_client_id(const QList<QStringList>& newMenu_services_software_version_client_id);

    const QList<QStringList>& get_menu_services_software_version_model_id() const;
    void set_menu_services_software_version_model_id(const QList<QStringList>& newMenu_services_software_version_model_id);

    const QList<QStringList>& get_menu_services_software_version_ecu_id() const;
    void set_menu_services_software_version_ecu_id(const QList<QStringList>& newMenu_services_software_version_ecu_id);

    const QList<QStringList>& get_menu_services_software_version_software_type() const;
    void set_menu_services_software_version_software_type(const QList<QStringList>& newMenu_services_software_version_software_type);

    const QList<QStringList>& get_menu_services_software_version_software_version_no() const;
    void set_menu_services_software_version_software_version_no(const QList<QStringList>& newMenu_services_software_version_software_version_no);

    bool get_menu_screen_visibility() const;
    void set_menu_screen_visibility(bool newMenu_screen_visibility);

    const QString& get_valid_password_not_match() const;
    void set_valid_password_not_match(const QString& newValid_password_not_match);

    const QString& get_new_password_not_match() const;
    void set_new_password_not_match(const QString& newNew_password_not_match);

    const QString& get_new_password_update() const;
    void set_new_password_update(const QString& newNew_password_update);

    const QString& get_new_password_update_failed() const;
    void set_new_password_update_failed(const QString& newNew_password_update_failed);

    const QStringList& get_main_menu_names() const;
    void set_main_menu_names(const QStringList&);

    const QStringList& get_sub_menu_names() const;
    void set_sub_menu_names(const QStringList&);

    const QStringList& get_right_menu_values_list() const;
    void set_right_menu_values_list(const QStringList&);

    const QList<QStringList>& get_param_menu_names() const;
    void set_param_menu_names(const QList<QStringList>&);

public slots:
    bool set_new_screen(int) override final;
    void set_new_focus(int, int, int) override final;
    void set_values(bool) override final;
    void set_language() override final;

signals:
    void main_menu_names_changed();
    void sub_menu_names_changed();
    void param_menu_names_changed();
    void update_central_dashboard_data();

    void screen_state_changed();
    void main_menu_pos_changed();
    void list_menu_pos_changed();
    void right_menu_values_list_changed();
    void param_menu_pos_changed();

    void type_of_vehicle_changed();

    void menu_services_streering_sensor_n_degree_changed();

    void menu_services_streering_sensor_m_value_changed();

    void menu_services_tempelate1_droplist_changed();

    void menu_services_tempelate2_droplist_changed();

    void menu_services_tempelate3_droplist_changed();

    void menu_services_tempelate4_droplist_changed();

    void menu_services_tempelate5_droplist_changed();

    void menu_services_tempelate6_droplist_changed();

    void menu_services_change_pwd_valid_password_changed();

    void menu_services_change_pwd_new_password_changed();

    void menu_services_change_pwd_confirmation_password_changed();

    void menu_services_password_data_changed();
/*
    void menu_services_software_version_ec12_changed();

    void menu_services_software_version_cc_changed();

    void menu_services_software_version_redp_changed();

    void menu_services_software_version_res_changed();
*/
    void menu_services_streering_sensor_instructions_changed();

    void menu_services_streering_sensor_status_changed();

    void steering_handle_sensor_signal(const QList<QStringList>&);

    void menu_screen_visibility_changed();

    void valid_password_not_match_changed();

    void new_password_not_match_changed();

    void new_password_update_changed();

    void new_password_update_failed_changed();

    void menu_settings_climate_control_driver_cab_status_changed();

    void menu_services_header_logbook_changed();

    void menu_services_low_engine_oil_pressure_changed();

    void menu_services_low_engine_coolant_level_changed();

    void menu_services_high_engine_coolant_temperature_changed();

    void menu_services_forced_shutdown_turbotimer_changed();

    void menu_services_exceeding_engine_speed_changed();

    void menu_services_low_engine_oil_pressure_index1_changed();

    void menu_services_low_engine_oil_pressure_index2_changed();

    void menu_services_low_engine_oil_pressure_index3_changed();

    void menu_services_low_engine_oil_pressure_index4_changed();

    void menu_services_low_engine_oil_pressure_index5_changed();

    void menu_services_low_engine_coolant_level_index1_changed();

    void menu_services_low_engine_coolant_level_index2_changed();

    void menu_services_low_engine_coolant_level_index3_changed();

    void menu_services_low_engine_coolant_level_index4_changed();

    void menu_services_low_engine_coolant_level_index5_changed();

    void menu_services_high_engine_coolant_temperature_index1_changed();

    void menu_services_high_engine_coolant_temperature_index2_changed();

    void menu_services_high_engine_coolant_temperature_index3_changed();

    void menu_services_high_engine_coolant_temperature_index4_changed();

    void menu_services_high_engine_coolant_temperature_index5_changed();

    void menu_services_forced_shutdown_turbotimer_index1_changed();

    void menu_services_exceeding_engine_speed_index1_changed();

    void menu_services_exceeding_engine_speed_index2_changed();

    void menu_services_exceeding_engine_speed_index3_changed();

    void menu_services_exceeding_engine_speed_index4_changed();

    void menu_services_exceeding_engine_speed_index5_changed();

    void menu_services_forced_shutdown_turbotimer_index2_changed();

    void menu_services_forced_shutdown_turbotimer_index3_changed();

    void menu_services_forced_shutdown_turbotimer_index4_changed();

    void menu_services_forced_shutdown_turbotimer_index5_changed();
private:
    void init_subscribe() override;
    void update_init_config_data();
    void initialize_menu_parameter_names();
    void initialize_typemenu_items_names();
    void initialize_menu_diagnostics_names();
    void initialize_menu_settings_names();
    void initialize_menu_services_names();

    QString get_sensor_senitivity(QString sensor_type, QString senstivity_value);

    bool update_menudata(string value, QString key_data);
    void update_language(int);
    void update_language_change(QString language);

    static mutex m_build_mutex;
    static QtMenuOps* m_ptr_instance;

    QString _valid_password_not_match;
    QString _new_password_not_match;
    QString _new_password_update;
    QString _new_password_update_failed;
    bool _menu_screen_visibility;
    bool _init_config_data_update_status;
    QString language_menu;
    QtJsonConfigureData* json_configure_data;
    MenuHandler* menu_handler;
    navigation* m_ptr_navigation;
    HmiHandler* m_ptr_msgs_handler;
    newMenuItems* _menu_items;
    QString _vehicle_type;
    int screen_state;
    int main_menu_pos;
    int list_menu_pos;
    int param_menu_pos;
    qint8 _present_menu_selected;
    QGuiApplication* _app;
    QTranslator _translator;
    QTimer* _timer;
    QTimer* _timer_steering_angle_sensor;
    mutex _mtx_timer_handler_data;
    mutex _mtx_map_menu_data;
    uint16_t _timer_id;
    bool _loading_flag = false;
    QtPopUpWindow* _ptrpopupwindow;
    QString _type_of_vehicle;
    QList<QStringList> _temp_menu_data;
    QStringList left_menu_list;
    QStringList right_menu_values_list;
    QList<QStringList> right_menu_params;
    QStringList m_main_menu_names;

    bool _menu_settings_climate_control_driver_cab_status = false;

    bool _menu_settings_light_rain_sensor_status = false;

    bool _menu_settings_brightness_status = false;
    chrono::steady_clock::time_point m_update_time_stamp;
public slots:
    Q_INVOKABLE void qml_menu_responses(bool value); // QmlState state
    Q_INVOKABLE void qml_responses(int value) override;
    Q_INVOKABLE void reset_average_fuel_consumption_data();
    Q_INVOKABLE QString get_config_file_data(QString key_data);
    Q_INVOKABLE void steering_angle_sensor_handler(QString activity);

    //save Change
    void steering_angle_sensor_timer_slot();

protected:
    QmlState _state = QMLSTATE_NORMAL;
};

#endif // QTMENUOPS_H
