#include "qtzummerhandler.h"

#define TONE_LEVEL0_PERIOD 1000000
#define TONE_LEVEL1_PERIOD 500000
#define TONE_LEVEL2_PERIOD 366300
#define TONE_LEVEL0_DUTYCYCLE 500000
#define TONE_LEVEL1_DUTYCYCLE 250000
#define TONE_LEVEL2_DUTYCYCLE 183150
#define RESET 0
#define SUCCESS 0
#define FAILURE -1

QtZummerHandler::QtZummerHandler(QObject* parent)
    : QObject{ parent }
{
    _pwm = new QtPwmControl();
    if (_pwm)
        _pwm->open_pwm(0);
}

QtZummerHandler::~QtZummerHandler()
{
    if (_pwm) {
        _pwm->close_pwm(0);
        delete _pwm;
    }
}

int QtZummerHandler::zummer_tone_settings(const int& tone_level)
{
    TRY_BLOCK
    int status = FAILURE;
    int period, dutycycle;
    if (tone_level == 0)
    {
        period = TONE_LEVEL0_PERIOD;
        dutycycle = TONE_LEVEL0_DUTYCYCLE;

    }
    else if (tone_level == 1)
    {
        period = TONE_LEVEL1_PERIOD;
        dutycycle = TONE_LEVEL1_DUTYCYCLE;
    }
    else if (tone_level == 2)
    {
        period = TONE_LEVEL2_PERIOD;
        dutycycle = TONE_LEVEL2_DUTYCYCLE;
    }
    status = _pwm->settings_pwm(period, dutycycle, "normal", RESET);
    if (status != 0)
        qDebug() << "Couldn't PWM update settings to tone level " << tone_level;

    return status;
    CATCH_BLOCK
}

int QtZummerHandler::zummer_enable(const int& enable)
{
    TRY_BLOCK
    int status = FAILURE;
    status = _pwm->enable_disable_pwm(enable, RESET);
    if (status != 0)
        qDebug() << "Couldn't enable zummer";

    return status;
    CATCH_BLOCK
}

int QtZummerHandler::zummer_disable(const int& disable)
{
    TRY_BLOCK
    int status = FAILURE;
    status = _pwm->enable_disable_pwm(disable, RESET);
    if (status != 0)
        qDebug() << "Couldn't disable zummer";

    return status;
    CATCH_BLOCK
}
