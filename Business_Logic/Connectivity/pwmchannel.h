#ifndef PWM_CHANNEL_H
#define PWM_CHANNEL_H

#include <stdint.h>
#include <stdio.h>
#include "../Logger/exception_define.h"


typedef enum{
    PWM_POLARITY_NORMAL,
    PWM_POLARITY_INVERSED,
    PWM_POLARITY_ERROR
}pwm_polarity_e;

typedef enum{
    PWM_ENABLE_OFF,
    PWM_ENABLE_ON,
    PWM_ENABLE_ERROR
}pwm_enable_e;

typedef enum{
    PWM_WRITE = 1u,
    PWM_READ
}pwm_flags_e;

class PwmChannel
{

public:
    typedef struct{
       pwm_enable_e enable;
       int64_t period_ns;
       int64_t duty_cycle_ns;
       pwm_polarity_e polarity;
       pwm_flags_e pwm_flags;
   }pwm_parameters_t;

    typedef struct{
        pwm_parameters_t* buffer;
        int counter_buffer;
    }pwm_rdwr_data_t;

    PwmChannel(const uint16_t npwmchip, const uint16_t npwm);
    PwmChannel(const uint16_t npwmchip, const uint16_t npwm, pwm_rdwr_data_t* pwm);
    ~PwmChannel();

    void pwm_settings(pwm_parameters_t* pwm); //whithout Enable

    uint8_t unexportPWM();

    uint8_t setEnable(const pwm_enable_e enable);
    pwm_enable_e getEnable();

private:
    void exportPWM();
    uint8_t writeFile(const char* fname, const char* text);
    size_t readFile(const char* fname, char* buff, const long fsize);
    long getFileSize(const char* fname);
    int64_t chartoint64(char* buffer, long size);
    void strcopy(char *destination_str, const char *source_str, const long size);

    void pwm_ctrl(pwm_rdwr_data_t* pwm);

    uint8_t setPeriod(const int64_t period_ns);
    int64_t getPeriod();

    uint8_t setDutyCycle(const int64_t duty_cycle_ns);
    int64_t getDutyCycle();

    uint8_t setPolarity(const pwm_polarity_e polarity);
    pwm_polarity_e getPolarity();

    uint8_t setPeriodAndDutyCycle(const int64_t period_ns, const int64_t duty_cycle_ns);

    uint16_t npwmchip = 0;
    uint16_t npwm = 0;
    uint8_t result_export_pwm = 0;


};
#endif // PWM_CHANNEL_H
