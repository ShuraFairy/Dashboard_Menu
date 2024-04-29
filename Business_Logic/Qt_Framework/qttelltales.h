#ifndef QTTELLTALES_H
#define QTTELLTALES_H

#include "../Common/telltales_defines.h"
#include "../Connectivity/JSON/qtjsonhandler.h"
#include "../Connectivity/hmi_handler.h"
#include "../Interfaces/iobserverforrender.h"
#include <QObject>
#include "QDebug"
#include <QFileInfo>
#include <QImage>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QTimer>
#include <string.h>
#include <unistd.h>
#include <vector>
#include "../Logger/exception_define.h"

#define QTTELLTALES_RESET 0
#define QTTELLTALES_SET 1

#define IMPL(name, container, i) \
    Q_PROPERTY(QList<QStringList> name##_##i READ get_##name##_##i WRITE set_##name##_##i NOTIFY name##_##i##_changed()); \
    public: \
        inline const QList<QStringList>& get_##name##_##i() const { return container.find(i)->second; } \
        inline void set_##name##_##i(const QList<QStringList>& value) \
        { \
            if (value != container[i]) \
            { \
                container[i] = value; \
                emit name##_##i##_changed();\
            } \
        }

using std::vector;

class QtTelltales : public QObject, public IObserverForRender, public ISubscriber {
    Q_OBJECT
public:
    //Q_PROPERTY(uint8_t fuel_level READ get_fuel_level WRITE set_fuel_level NOTIFY fuel_level_changed)
    Q_PROPERTY(qreal current READ get_current WRITE set_current NOTIFY current_changed)
    Q_PROPERTY(qreal voltage READ get_voltage WRITE set_voltage NOTIFY voltage_changed)

    Q_PROPERTY(bool dialguage1 READ get_dialguage1 WRITE set_dialguage1 NOTIFY dialguage1_Changed)
    Q_PROPERTY(bool dialguage2 READ get_dialguage2 WRITE set_dialguage2 NOTIFY dialguage2_Changed)
    //Q_PROPERTY(QList<QStringList> bus_door_data READ get_bus_door_data WRITE set_bus_door_data NOTIFY bus_door_data_Changed);

private:
    unordered_map<uint32_t, QList<QStringList>> m_telltales_map;
    IMPL(telltale_pos, m_telltales_map, 1);
    IMPL(telltale_pos, m_telltales_map, 2);
    IMPL(telltale_pos, m_telltales_map, 3);
    IMPL(telltale_pos, m_telltales_map, 4);
    IMPL(telltale_pos, m_telltales_map, 5);
    IMPL(telltale_pos, m_telltales_map, 6);
    IMPL(telltale_pos, m_telltales_map, 7);
    IMPL(telltale_pos, m_telltales_map, 8);
    IMPL(telltale_pos, m_telltales_map, 9);
    IMPL(telltale_pos, m_telltales_map, 10);
    IMPL(telltale_pos, m_telltales_map, 11);
    IMPL(telltale_pos, m_telltales_map, 12);
    IMPL(telltale_pos, m_telltales_map, 13);
    IMPL(telltale_pos, m_telltales_map, 14);
    IMPL(telltale_pos, m_telltales_map, 15);
    IMPL(telltale_pos, m_telltales_map, 16);
    IMPL(telltale_pos, m_telltales_map, 17);
    IMPL(telltale_pos, m_telltales_map, 18);
    IMPL(telltale_pos, m_telltales_map, 19);
    IMPL(telltale_pos, m_telltales_map, 20);
    IMPL(telltale_pos, m_telltales_map, 21);
    IMPL(telltale_pos, m_telltales_map, 22);
    IMPL(telltale_pos, m_telltales_map, 23);
    IMPL(telltale_pos, m_telltales_map, 24);
    IMPL(telltale_pos, m_telltales_map, 25);
    IMPL(telltale_pos, m_telltales_map, 26);
    IMPL(telltale_pos, m_telltales_map, 27);
    IMPL(telltale_pos, m_telltales_map, 28);
    IMPL(telltale_pos, m_telltales_map, 29);
    IMPL(telltale_pos, m_telltales_map, 30);
    IMPL(telltale_pos, m_telltales_map, 31);
    IMPL(telltale_pos, m_telltales_map, 32);
    IMPL(telltale_pos, m_telltales_map, 33);
    IMPL(telltale_pos, m_telltales_map, 34);
    IMPL(telltale_pos, m_telltales_map, 35);
    IMPL(telltale_pos, m_telltales_map, 36);
    IMPL(telltale_pos, m_telltales_map, 37);
    IMPL(telltale_pos, m_telltales_map, 38);
    IMPL(telltale_pos, m_telltales_map, 39);
    IMPL(telltale_pos, m_telltales_map, 40);
    IMPL(telltale_pos, m_telltales_map, 41);
    IMPL(telltale_pos, m_telltales_map, 42);
    IMPL(telltale_pos, m_telltales_map, 43);
    IMPL(telltale_pos, m_telltales_map, 44);
    IMPL(telltale_pos, m_telltales_map, 45);
    IMPL(telltale_pos, m_telltales_map, 46);
    IMPL(telltale_pos, m_telltales_map, 47);
    IMPL(telltale_pos, m_telltales_map, 48);
    IMPL(telltale_pos, m_telltales_map, 49);
    IMPL(telltale_pos, m_telltales_map, 50);
    IMPL(telltale_pos, m_telltales_map, 51);
    IMPL(telltale_pos, m_telltales_map, 52);
    IMPL(telltale_pos, m_telltales_map, 53);
    IMPL(telltale_pos, m_telltales_map, 54);
    IMPL(telltale_pos, m_telltales_map, 55);
    IMPL(telltale_pos, m_telltales_map, 56);
    IMPL(telltale_pos, m_telltales_map, 57);
    IMPL(telltale_pos, m_telltales_map, 58);
    IMPL(telltale_pos, m_telltales_map, 59);
    IMPL(telltale_pos, m_telltales_map, 60);
    IMPL(telltale_pos, m_telltales_map, 61);
    IMPL(telltale_pos, m_telltales_map, 62);
    IMPL(telltale_pos, m_telltales_map, 63);
    IMPL(telltale_pos, m_telltales_map, 64);
    IMPL(telltale_pos, m_telltales_map, 65);
    IMPL(telltale_pos, m_telltales_map, 66);
    IMPL(telltale_pos, m_telltales_map, 67);
    IMPL(telltale_pos, m_telltales_map, 68);
    IMPL(telltale_pos, m_telltales_map, 69);
    IMPL(telltale_pos, m_telltales_map, 70);
    IMPL(telltale_pos, m_telltales_map, 71);
    IMPL(telltale_pos, m_telltales_map, 72);
    IMPL(telltale_pos, m_telltales_map, 73);
    IMPL(telltale_pos, m_telltales_map, 74);
    IMPL(telltale_pos, m_telltales_map, 75);
    IMPL(telltale_pos, m_telltales_map, 76);
    IMPL(telltale_pos, m_telltales_map, 77);
    IMPL(telltale_pos, m_telltales_map, 78);
    IMPL(telltale_pos, m_telltales_map, 79);
    IMPL(telltale_pos, m_telltales_map, 80);

public:
    Q_PROPERTY(QList<QStringList> bus_door1 READ get_bus_door1 WRITE set_bus_door1 NOTIFY bus_door1_changed)
    Q_PROPERTY(QList<QStringList> bus_door2 READ get_bus_door2 WRITE set_bus_door2 NOTIFY bus_door2_changed)
    Q_PROPERTY(QList<QStringList> bus_door3 READ get_bus_door3 WRITE set_bus_door3 NOTIFY bus_door3_changed)
    Q_PROPERTY(QList<QStringList> bus_door4 READ get_bus_door4 WRITE set_bus_door4 NOTIFY bus_door4_changed)
    typedef enum {
        ICCOLOR_OFF = 0U,
        ICCOLOR_COLOR1,
        ICCOLOR_COLOR2,
        ICCOLOR_COLOR3,
    } IcColor;

    typedef struct {
        QString telltale_name;
        uint8_t telltale_position;
        QString category;
        uint8_t priority;
        QString telltale_color;
        QString telltale_image_path;
    } TelltaleDataInit;

    qreal air_pressure1_data;
    QString telltale_path;

    QtTelltales(QObject* parent = nullptr);
    ~QtTelltales();

    static QtTelltales* get_instance();
    inline QmlState get_state(){return _state;};

    qreal get_current() const;
    void set_current(qreal current);

    qreal get_voltage() const;
    void set_voltage(qreal voltage);

    bool get_dialguage1() const;
    void set_dialguage1(bool newDialguage1);

    bool get_dialguage2() const;
    void set_dialguage2(bool newDialguage2);

    const QList<QStringList>& get_bus_door_data() const;
    void set_bus_door_data(const QList<QStringList>& newBus_door_data);

    /******************************/
    void update_gui() override;
    bool update_info(uint32_t _id) override;

    /******************************/
    const QList<QStringList>& get_bus_door1() const;
    void set_bus_door1(const QList<QStringList>& newBus_door1);

    const QList<QStringList>& get_bus_door2() const;
    void set_bus_door2(const QList<QStringList>& newBus_door2);

    const QList<QStringList>& get_bus_door3() const;
    void set_bus_door3(const QList<QStringList>& newBus_door3);

    const QList<QStringList>& get_bus_door4() const;
    void set_bus_door4(const QList<QStringList>& newBus_door4);

public slots:
    void get_airpressure1_data(const qreal airpressure1_data);
    void get_airpressure2_data(const qreal airpressure2_data);


    Q_INVOKABLE void qml_responses(int value) override;
    //void door_timer();

signals:

//    void fuel_level_changed();
    void current_changed();
    void voltage_changed();

    void dialguage1_Changed();
    void dialguage2_Changed();

    void bus_door_data_Changed();

    void bus_door1_changed();
    void bus_door2_changed();
    void bus_door3_changed();
    void bus_door4_changed();

    void telltale_pos_1_changed();

    void telltale_pos_2_changed();

    void telltale_pos_3_changed();

    void telltale_pos_4_changed();

    void telltale_pos_5_changed();

    void telltale_pos_6_changed();

    void telltale_pos_7_changed();

    void telltale_pos_8_changed();

    void telltale_pos_9_changed();

    void telltale_pos_10_changed();

    void telltale_pos_11_changed();

    void telltale_pos_12_changed();

    void telltale_pos_13_changed();

    void telltale_pos_14_changed();

    void telltale_pos_15_changed();

    void telltale_pos_16_changed();

    void telltale_pos_17_changed();

    void telltale_pos_18_changed();

    void telltale_pos_19_changed();

    void telltale_pos_20_changed();

    void telltale_pos_21_changed();

    void telltale_pos_22_changed();

    void telltale_pos_23_changed();

    void telltale_pos_24_changed();

    void telltale_pos_25_changed();

    void telltale_pos_26_changed();

    void telltale_pos_27_changed();

    void telltale_pos_28_changed();

    void telltale_pos_29_changed();

    void telltale_pos_30_changed();

    void telltale_pos_31_changed();

    void telltale_pos_32_changed();

    void telltale_pos_33_changed();

    void telltale_pos_42_changed();

    void telltale_pos_43_changed();

    void telltale_pos_44_changed();

    void telltale_pos_45_changed();

    void telltale_pos_46_changed();

    void telltale_pos_47_changed();

    void telltale_pos_48_changed();

    void telltale_pos_49_changed();

    void telltale_pos_50_changed();

    void telltale_pos_51_changed();

    void telltale_pos_53_changed();

    void telltale_pos_54_changed();

    void telltale_pos_55_changed();

    void telltale_pos_52_changed();

    void telltale_pos_34_changed();

    void telltale_pos_35_changed();

    void telltale_pos_36_changed();

    void telltale_pos_37_changed();

    void telltale_pos_38_changed();

    void telltale_pos_39_changed();

    void telltale_pos_40_changed();

    void telltale_pos_41_changed();

    void telltale_pos_56_changed();

    void telltale_pos_57_changed();

    void telltale_pos_58_changed();

    void telltale_pos_59_changed();

    void telltale_pos_60_changed();

    void telltale_pos_61_changed();

    void telltale_pos_62_changed();

    void telltale_pos_63_changed();

    void telltale_pos_64_changed();

    void telltale_pos_65_changed();

    void telltale_pos_66_changed();

    void telltale_pos_67_changed();

    void telltale_pos_68_changed();

    void telltale_pos_69_changed();

    void telltale_pos_70_changed();

    void telltale_pos_71_changed();

    void telltale_pos_72_changed();

    void telltale_pos_73_changed();

    void telltale_pos_74_changed();

    void telltale_pos_75_changed();

    void telltale_pos_76_changed();

    void telltale_pos_77_changed();

    void telltale_pos_78_changed();

    void telltale_pos_79_changed();

    void telltale_pos_80_changed();


private:
    bool check_priority(QString);
    void apply_telltale(uint8_t _value, QString _name);
    void init_subscribe() override;

    void update_map_telltale_data();
    void update_map_init_data();

    bool check_if_record_exists(uint8_t);
    TelltaleDataInit* get_telltale_position(uint8_t);

    void update_all_telltale_visiblity(bool visibility);

    void initialize_busdoors(void);
    void update_bus_doors(void);
    void update_all_telltales();
    void init_telltales(void);

    //QtPopUpWindow* _ptrpopupwindow;
    unordered_map<uint8_t, TelltaleDataInit> _map_telltale_data;
    unordered_map<QString, vector<uint8_t>> m_map_cat_and_pos;
//    uint8_t _fuel_level = QTTELLTALES_RESET;
    qreal _temp_fuel_level = QTTELLTALES_RESET;

    qreal _current = QTTELLTALES_RESET;

    qreal _voltage = QTTELLTALES_RESET;

    bool _dialguage1 = false;
    bool _dialguage2 = false;

    //    bool switching_pos_48 = 0; //1-индикатор уже был включен 0-индикатор не включен

    QmlState _state;

private:
    static mutex m_build_mutex;
    static QtTelltales* m_ptr_instance;

    QtJsonHandler* json_handler;
    HmiHandler* m_ptr_cached_msgs;
    QList<QStringList> telltale_pos;
    QList<QStringList> _bus_door_data;

    QList<QStringList> _bus_door1;
    QList<QStringList> _bus_door2;
    QList<QStringList> _bus_door3;
    QList<QStringList> _bus_door4;
    QList<QStringList> _bus_doors_data;

    typedef void (QtTelltales::*telltale_slot)(const QList<QStringList>&);
    unordered_map<uint8_t, telltale_slot> map_telltale_slots;
    map<QString, QtJsonHandler::JsonData>* ptr_map_json;
    //QTimer* _timer_door;
    //bool check_door_status = false;
};

#endif // QTTELLTALES_H
