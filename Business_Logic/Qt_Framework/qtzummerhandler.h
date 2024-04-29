#ifndef QTZUMMERHANDLER_H
#define QTZUMMERHANDLER_H

#include "qtpwmcontrol.h"
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

class QtZummerHandler : public QObject {
    Q_OBJECT
public:
    explicit QtZummerHandler(QObject* parent = nullptr);
    ~QtZummerHandler();
    Q_INVOKABLE int zummer_tone_settings(const int& tone_level);
    Q_INVOKABLE int zummer_enable(const int& enable);
    Q_INVOKABLE int zummer_disable(const int& disable);

private:
    QtPwmControl* _pwm;
};

#endif // QTZUMMERHANDLER_H
