#ifndef QTCENTRALDASHBOARD_H
#define QTCENTRALDASHBOARD_H

#include "../Connectivity/hmi_handler.h"
#include "Business_Logic/Menu/menu_handler.h"
#include "../Interfaces/iobserverforrender.h"
#include "../subscribe_notifer.h"
#include <QDateTime>
#include <QObject>
#include <QQuickView>
#include <QStringList>
#include <QTranslator>
#include <QDate>
#include <QDebug>
#include <QTime>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <tuple>

//#include <QVariant>
#include "../Logger/exception_define.h"

class QtCentralDashboard : public QObject, public IObserverForRender, public ISubscriber {
    Q_OBJECT
    Q_PROPERTY(QString temperature READ get_temperature WRITE set_temperature NOTIFY temperature_changed);
    Q_PROPERTY(QString cabin_temperature1 READ get_cabin_temperature1 WRITE set_cabin_temperature1 NOTIFY cabin_temperature1_changed);
    Q_PROPERTY(QString cabin_temperature2 READ get_cabin_temperature2 WRITE set_cabin_temperature2 NOTIFY cabin_temperature2_changed);
    Q_PROPERTY(QString present_date READ get_present_date WRITE set_present_date NOTIFY present_date_changed);
    Q_PROPERTY(QString present_time READ get_present_time WRITE set_present_time NOTIFY present_time_changed);
    Q_PROPERTY(QList<QStringList> mileage READ get_mileage WRITE set_mileage NOTIFY mileage_changed)
    Q_PROPERTY(QList<QStringList> daily_fuel_consumption READ get_daily_fuel_consumption WRITE set_daily_fuel_consumption NOTIFY daily_fuel_consumption_changed)
    Q_PROPERTY(QList<QStringList> pressure_uom READ get_pressure_uom WRITE set_pressure_uom NOTIFY pressure_uom_changed)
    Q_PROPERTY(QList<QStringList> engine_uom READ get_engine_uom WRITE set_engine_uom NOTIFY engine_uom_changed)
    Q_PROPERTY(QList<QStringList> speed_uom READ get_speed_uom WRITE set_speed_uom NOTIFY speed_uom_changed)
    Q_PROPERTY(QList<QStringList> fuel_consumption READ get_fuel_consumption WRITE set_fuel_consumption NOTIFY fuel_consumption_changed)
    Q_PROPERTY(QList<QStringList> engine_coolant_temperature READ get_engine_coolant_temperature WRITE set_engine_coolant_temperature NOTIFY engine_coolant_temperature_changed)
    Q_PROPERTY(QList<QStringList> battery_ampere READ get_battery_ampere WRITE set_battery_ampere NOTIFY battery_ampere_changed)
    Q_PROPERTY(QList<QStringList> battery_voltage READ get_battery_voltage WRITE set_battery_voltage NOTIFY battery_voltage_changed)
    Q_PROPERTY(QList<QStringList> trip_distance READ get_trip_distance WRITE set_trip_distance NOTIFY trip_distance_changed)

    Q_PROPERTY(int gear_shift READ get_gear_shift WRITE set_gear_shift NOTIFY gear_shift_changed)

    Q_PROPERTY(QString fuel_level READ get_fuel_level WRITE set_fuel_level NOTIFY fuel_level_changed)

public:
    explicit QtCentralDashboard(QObject* parent = nullptr);
    ~QtCentralDashboard();
    static QtCentralDashboard* get_instance();
    void update_gui() override;
    bool update_info(uint32_t _id) override;

    QString get_temperature() const;
    void set_temperature(QString temperature);

    QString get_cabin_temperature1() const;
    void set_cabin_temperature1(QString cabin_temperature1);

    QString get_cabin_temperature2() const;
    void set_cabin_temperature2(QString cabin_temperature2);

    const QString& get_present_date() const;
    void set_present_date(const QString& new_present_date);

    const QString& get_present_time() const;
    void set_present_time(const QString& new_present_time);

    const QList<QStringList>& get_mileage() const;
    void set_mileage(const QList<QStringList>& newMileage);

    const QList<QStringList>& get_daily_fuel_consumption() const;
    void set_daily_fuel_consumption(const QList<QStringList>& newDaily_fuel_consumption);

    const QList<QStringList>& get_pressure_uom() const;
    void set_pressure_uom(const QList<QStringList>& newPressure_uom);

    const QList<QStringList>& get_engine_uom() const;
    void set_engine_uom(const QList<QStringList>& newEngine_uom);

    const QList<QStringList>& get_speed_uom() const;
    void set_speed_uom(const QList<QStringList>& newSpeed_uom);

    const QList<QStringList>& get_fuel_consumption() const;
    void set_fuel_consumption(const QList<QStringList>& newFuel_consumption);

    const QList<QStringList>& get_engine_coolant_temperature() const;
    void set_engine_coolant_temperature(const QList<QStringList>& newEngine_coolant_temperature);

    const QList<QStringList>& get_battery_ampere() const;
    void set_battery_ampere(const QList<QStringList>& newBattery_ampere);

    const QList<QStringList>& get_battery_voltage() const;
    void set_battery_voltage(const QList<QStringList>& newBattery_voltage);

    const QList<QStringList>& get_trip_distance() const;
    void set_trip_distance(const QList<QStringList>& newTrip_distance);

    const int& get_gear_shift() const;
    void set_gear_shift(const int&);


    QString get_fuel_level() const;
    void set_fuel_level(const QString& new_fuel_level);

public slots:
    Q_INVOKABLE void update_central_dashboard_text();
    Q_INVOKABLE void qml_responses(int value) override;

signals:
    void temperature_changed();
    void cabin_temperature1_changed();
    void cabin_temperature2_changed();
    void present_date_changed();
    void present_time_changed();
    void mileage_changed();
    void daily_fuel_consumption_changed();
    void pressure_uom_changed();
    void engine_uom_changed();
    void speed_uom_changed();
    void fuel_consumption_changed();
    void engine_coolant_temperature_changed();
    void battery_ampere_changed();
    void battery_voltage_changed();
    void trip_distance_changed();
    void gear_shift_changed();

    void fuel_level_changed();

private:
    void init_subscribe() override;
    void init_main_data_container();

    void initialize_central_dashboard_data();
    void update_map_main_data(QString key_map, QString lang_text, QString init_value, QString uom);

    bool update_maindata(string element_value, QString key_data);

    typedef void (QtCentralDashboard:: *main_slot)(const QList<QStringList>&);
    QMap<QString, main_slot> map_main_slots;

    static mutex m_build_mutex;
    static QtCentralDashboard* m_ptr_instance;

    HmiHandler* m_ptr_cached_msgs;
    MenuHandler* m_ptr_menu_handler;

    QString _temperature;
    QString _cabin_temperature1;
    QString _cabin_temperature2;
    QString _present_date;
    QString _present_time;
    QMap<QString, QList<QStringList>> map_main_data;
    vector<tuple<QString, QString, QString, QString, QtCentralDashboard::main_slot>> g_main_data_container;
    int m_shift;
    QmlState _state;
    QString _fuel_level;
};

#endif // QTCENTRALDASHBOARD_H
