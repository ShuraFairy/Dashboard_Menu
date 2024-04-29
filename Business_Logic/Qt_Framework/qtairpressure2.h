#ifndef QTAIRPRESSURE2_H
#define QTAIRPRESSURE2_H
#include "../Connectivity/hmi_handler.h"
#include "../Interfaces/iobserverforrender.h"
#include "../subscribe_notifer.h"
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <unistd.h>
//#include <QVariant>
#include "../Logger/exception_define.h"

class QtAirPressure2 : public QObject, public IObserverForRender, public ISubscriber {
    Q_OBJECT
    Q_PROPERTY(qreal air_pressure_2 READ get_air_pressure_2 WRITE set_air_pressure_2 NOTIFY air_pressure_2_changed)
public:
    explicit QtAirPressure2(QObject* parent = nullptr);
    ~QtAirPressure2();
    static QtAirPressure2* get_instance();
    void update_gui() override;
    bool update_info(uint32_t _id) override;

    qreal get_air_pressure_2() const;
    void set_air_pressure_2(qreal new_air_pressure_2);
    qreal airpressure2_data;

signals:
    void air_pressure_2_changed();
    void air_pressure2_telltale(const qreal airpressure2_data);

public slots:
    Q_INVOKABLE void qml_responses(int value) override; // QmlState state

private:
    void init_subscribe() override;
    static mutex m_build_mutex;
    static QtAirPressure2* m_ptr_instance;

    qreal _air_pressure_2;
    HmiHandler* m_ptr_cached_msgs;
    QmlState _state;
};

#endif // QTAIRPRESSURE2_H
