#ifndef QTAIRPRESSURE1_H
#define QTAIRPRESSURE1_H
#include "../Connectivity/hmi_handler.h"
#include "../Interfaces/iobserverforrender.h"
#include "../subscribe_notifer.h"
#include <QObject>
#include "../Logger/exception_define.h"
//#include <QVariant>

class QtAirPressure1 : public QObject, public IObserverForRender, public ISubscriber {
    Q_OBJECT
    Q_PROPERTY(qreal air_pressure_1 READ get_air_pressure_1 WRITE set_air_pressure_1 NOTIFY air_pressure_1_changed)
public:
    explicit QtAirPressure1(QObject* parent = nullptr);
    ~QtAirPressure1();
    static QtAirPressure1* get_instance();
    void update_gui() override;
    bool update_info(uint32_t _id) override;

    qreal get_air_pressure_1() const;
    void set_air_pressure_1(qreal new_air_pressure_1);
    qreal airpressure1_data;

signals:
    void air_pressure_1_changed();
    void air_pressure1_telltale(const qreal airpressure1_data);

public slots:
    Q_INVOKABLE void qml_responses(int value) override;

private:
    void init_subscribe() override;
    static mutex m_build_mutex;
    static QtAirPressure1* m_ptr_instance;

    HmiHandler* m_ptr_cached_msgs;
    qreal _air_pressure_1;
    QmlState _state;
};

#endif // QTAIRPRESSURE1_H
