#ifndef QTENGINEMETER_H
#define QTENGINEMETER_H

#include "../Connectivity/hmi_handler.h"
#include "../Interfaces/iobserverforrender.h"
#include "../subscribe_notifer.h"
#include "mt_dsp_median.h"
#include "mt_dsp_mavg.h"
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <math.h>
#include <unistd.h>
#include "../Logger/exception_define.h"

class QtEngineMeter : public QObject, public IObserverForRender, public ISubscriber {
    Q_OBJECT
    Q_PROPERTY(qreal engine_speed READ get_engine_speed WRITE set_engine_speed NOTIFY engine_speed_changed)

public:
    explicit QtEngineMeter(QObject* parent = nullptr);
    ~QtEngineMeter();
    static QtEngineMeter* get_instance();
    void update_gui() override;
    bool update_info(uint32_t _id) override;

    qreal get_engine_speed() const;
    void set_engine_speed(qreal new_engine_speed);

signals:
    void engine_speed_changed();

public slots:
    Q_INVOKABLE void qml_responses(int value) override; // QmlState state);

private:
    void init_subscribe() override;
    void filter_init();

    static mutex m_build_mutex;
    static QtEngineMeter* m_ptr_instance;

    HmiHandler* m_ptr_cached_msgs;
    qreal _engine_speed;
    QmlState _state;
    float _filter_buffer[QTENGINEMETER_GAUGE_FILTER_WINDOW_SIZE];
    mt_dsp_mavg_f32_t _gauge_filter;
};

#endif // QTENGINEMETER_H
