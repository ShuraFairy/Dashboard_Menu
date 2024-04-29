#ifndef QTSPEEDOMETER_H
#define QTSPEEDOMETER_H

#include "../Interfaces/iobserverforrender.h"
#include "mt_dsp_median.h"
#include "mt_dsp_mavg.h"
#include "../Connectivity/hmi_handler.h"
#include <QObject>
#include "../Logger/exception_define.h"

class QtSpeedometer : public QObject, public IObserverForRender, public ISubscriber {
    Q_OBJECT
    Q_PROPERTY(qreal speed READ get_speed WRITE set_speed NOTIFY speed_changed)

public:
    explicit QtSpeedometer(QObject* parent = nullptr);
    static QtSpeedometer* get_instance();
    ~QtSpeedometer();
    void update_gui() override;
    bool update_info(uint32_t _id) override;

    qreal get_speed() const;
    void set_speed(qreal new_speed);

signals:
    void speed_changed();
public slots:
    Q_INVOKABLE void qml_responses(int value) override; // QmlState state

private:
    void init_subscribe() override;
    void filter_init();

    static mutex m_build_mutex;
    static QtSpeedometer* m_ptr_instance;

    float _filter_buffer[QTSPEEDOMETER_GAUGE_FILTER_WINDOW_SIZE];
    mt_dsp_mavg_f32_t _gauge_filter;
    HmiHandler* m_ptr_cached_msg_handler;
    qreal _speed;
    QmlState _state;
};

#endif // QTSPEEDOMETER_H
