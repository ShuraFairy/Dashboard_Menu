#ifndef QTPWMCONTROL_H
#define QTPWMCONTROL_H

#include <QDebug>
#include <QObject>
#include <QString>
#include <QTime>
#include <QTimer>
//#include <QVariant>
#include <QtCore>
#include <fcntl.h>
#include <unistd.h>
#include "../Logger/exception_define.h"

class QtPwmControl : public QObject {
    Q_OBJECT
public:
    explicit QtPwmControl(QObject* parent = nullptr);
    Q_INVOKABLE int open_pwm(const int& pwm_line_number);
    Q_INVOKABLE int close_pwm(const int& pwm_line_number);
    Q_INVOKABLE int settings_pwm(const int& period, const int& duty_cycle, const char* polarity, const int& pwm_line_number);
    Q_INVOKABLE int enable_disable_pwm(const int& enable_flag, const int& pwm_line_number);
};

#endif // QTPWMCONTROL_H
