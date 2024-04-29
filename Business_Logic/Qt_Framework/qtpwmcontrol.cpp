#include "qtpwmcontrol.h"

#define MAX_STR 64
#define FAILURE -1
#define SUCCESS 0

QtPwmControl::QtPwmControl(QObject* parent)
    : QObject{ parent }
{
}

int QtPwmControl::open_pwm(const int& pwm_line_number)
{
    TRY_BLOCK
    int status = FAILURE;
    FILE* sysfs_handler = fopen("/sys/class/pwm/pwmchip0/export", "w");
    if (sysfs_handler == NULL) {
        qDebug() << "Could not open pwm file";
        return status;
    }
    char pwm_line_number_str[MAX_STR];
    snprintf(pwm_line_number_str, (MAX_STR * sizeof(char)), "%d", pwm_line_number);
    fwrite(&pwm_line_number_str, sizeof(char), MAX_STR, sysfs_handler);
    fclose(sysfs_handler);
    status = SUCCESS;
    return status;
    CATCH_BLOCK
}

int QtPwmControl::close_pwm(const int& pwm_line_number)
{
    TRY_BLOCK
    int status = FAILURE;
    char pwm_line_number_str[MAX_STR];
    snprintf(pwm_line_number_str, (MAX_STR * sizeof(char)), "%d", pwm_line_number);
    FILE* sysfs_handler = fopen("/sys/class/pwm/pwmchip0/unexport", "w");
    if (sysfs_handler == NULL) {
        return status;
    }
    status = fwrite(&pwm_line_number_str, sizeof(char), MAX_STR, sysfs_handler);
    qDebug() << "Status of write PWM line export" << status;
    fclose(sysfs_handler);
    status = SUCCESS;
    return status;
    CATCH_BLOCK
}

int QtPwmControl::settings_pwm(const int& period, const int& duty_cycle, const char* polarity, const int& pwm_line_number)
{
    TRY_BLOCK
    int status = FAILURE;
    char period_file_path[MAX_STR];
    char duty_cycle_file_path[MAX_STR];
    char polarity_file_path[MAX_STR];
    char period_value_str[MAX_STR];
    char duty_cycle_value_str[MAX_STR];

    /* period settings */
    snprintf(period_file_path, (MAX_STR * sizeof(char)), "/sys/class/pwm/pwmchip0/pwm%d/period", pwm_line_number);
    FILE* sysfs_handler = fopen(period_file_path, "w");
    if (sysfs_handler == NULL) {
        qDebug() << "Could not open pwm period file";
        return status;
    }
    snprintf(period_value_str, (MAX_STR * sizeof(char)), "%d", period);
    fwrite(period_value_str, sizeof(char), MAX_STR, sysfs_handler);
    fclose(sysfs_handler);
    /*end of period settings */

    /* duty_cycle settings */
    snprintf(duty_cycle_file_path, (MAX_STR * sizeof(char)), "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pwm_line_number);
    sysfs_handler = fopen(duty_cycle_file_path, "w");
    if (sysfs_handler == NULL) {
        qDebug() << "Could not open pwm duty cycle file";
        return status;
    }
    snprintf(duty_cycle_value_str, (MAX_STR * sizeof(char)), "%d", duty_cycle);
    fwrite(duty_cycle_value_str, sizeof(char), MAX_STR, sysfs_handler);
    fclose(sysfs_handler);
    /*end of duty_cycle settings */

    /* polarity settings */
    snprintf(polarity_file_path, (MAX_STR * sizeof(char)), "/sys/class/pwm/pwmchip0/pwm%d/polarity", pwm_line_number);
    sysfs_handler = fopen(polarity_file_path, "w");
    if (sysfs_handler == NULL) {
        qDebug() << "Could not open pwm polarity file";
        return status;
    }
    fwrite(polarity, sizeof(char), MAX_STR, sysfs_handler);
    fclose(sysfs_handler);
    status = SUCCESS;
    return status;
    CATCH_BLOCK
}

int QtPwmControl::enable_disable_pwm(const int& enable_flag, const int& pwm_line_number)
{
    TRY_BLOCK
    int status = FAILURE;
    char pwm_enable_file_path[MAX_STR];
    memset(&pwm_enable_file_path, 0, sizeof(pwm_enable_file_path));
    char enable_flag_str[MAX_STR];
    memset(&enable_flag_str, 0, sizeof(enable_flag_str));
    snprintf(pwm_enable_file_path, (MAX_STR * sizeof(char)), "/sys/class/pwm/pwmchip0/pwm%d/enable", pwm_line_number);
    FILE* sysfs_handler = fopen(pwm_enable_file_path, "w");
    if (sysfs_handler == NULL) {
        qDebug() << "Could not open pwm enable file";
        return status;
    }
    snprintf(enable_flag_str, (MAX_STR * sizeof(char)), "%d", enable_flag);
    status = fwrite(enable_flag_str, sizeof(char), MAX_STR, sysfs_handler);
    if (status != MAX_STR) {
        qDebug() << "Could not enable pwm signal" << status;
    }
    fclose(sysfs_handler);
    status = SUCCESS;
    return status;
    CATCH_BLOCK
}
