#include "pwmchannel.h"
#include <iostream>
#include <string.h>

#define MAX_LEN_STR 64
#define MAX_SIZE_BUFFER 20
#define FAILURE 1
#define SUCCESS 0
#define INCORRECT_DATA -1
#define POLARITY_NORMAL "normal"
#define POLARITY_INVERSED "inversed"

PwmChannel::PwmChannel(const uint16_t npwmchip, const uint16_t npwm)
{
    this->npwm = npwm;
    this->npwmchip = npwmchip;
    exportPWM();
}

void PwmChannel::exportPWM()
{
    TRY_BLOCK
    int result_snprintf = 0;
    char export_pwm[MAX_LEN_STR];

    result_snprintf = snprintf(export_pwm, (MAX_LEN_STR * sizeof(char)), "/sys/class/pwm/pwmchip%d/export",npwmchip);

    if(result_snprintf == 0){
        result_export_pwm = FAILURE;
        return;
    }

    result_export_pwm = writeFile(export_pwm, std::to_string(npwm).c_str());
    CATCH_BLOCK
}

uint8_t PwmChannel::unexportPWM()
{
    TRY_BLOCK
    int result_snprintf = 0;

    char unexport_pwm[MAX_LEN_STR];
    result_snprintf = snprintf(unexport_pwm, (MAX_LEN_STR * sizeof(char)), "/sys/class/pwm/pwmchip%d/unexport",npwmchip);

    if(result_snprintf == 0)
        return FAILURE;

    return writeFile(unexport_pwm, std::to_string(npwm).c_str());
    CATCH_BLOCK
}

uint8_t PwmChannel::setPeriod(const int64_t period_ns)
{
    TRY_BLOCK
    int result_snprintf = 0;
    int64_t duty_cycle_ns = getDutyCycle();

    if(period_ns < duty_cycle_ns && duty_cycle_ns!=-1)
        return FAILURE;

    char period_pwm[MAX_LEN_STR];
    result_snprintf = snprintf(period_pwm, (MAX_LEN_STR * sizeof(char)), "/sys/class/pwm/pwmchip%d/pwm%d/period", npwmchip,npwm);

    if(result_snprintf == 0)
        return FAILURE;

    return writeFile(period_pwm, std::to_string(period_ns).c_str());
    CATCH_BLOCK
}

uint8_t PwmChannel::setEnable(const pwm_enable_e enable)
{
    TRY_BLOCK
    int result_snprintf = 0;

    if(enable != PWM_ENABLE_OFF && enable != PWM_ENABLE_ON)
        return 1;

    char enable_pwm[MAX_LEN_STR];
    result_snprintf = snprintf(enable_pwm, (MAX_LEN_STR * sizeof(char)), "/sys/class/pwm/pwmchip%d/pwm%d/enable", npwmchip,npwm);

    if(result_snprintf == 0)
        return FAILURE;

    if(enable == PWM_ENABLE_ON)
    {
        return writeFile(enable_pwm, "1");
    } else
        return writeFile(enable_pwm, "0");
    CATCH_BLOCK
}

uint8_t PwmChannel::setDutyCycle(const int64_t duty_cycle_ns)
{
    TRY_BLOCK
    int result_snprintf = 0;
    int64_t period_ns = getPeriod();

    if( period_ns < duty_cycle_ns && period_ns!=-1)
        return FAILURE;

    char duty_cycle_pwm[MAX_LEN_STR];

    result_snprintf =  snprintf(duty_cycle_pwm, (MAX_LEN_STR * sizeof(char)), "/sys/class/pwm/pwmchip%d/pwm%d/duty_cycle", npwmchip,npwm);

    if(result_snprintf == 0)
        return FAILURE;

    return writeFile(duty_cycle_pwm, std::to_string(duty_cycle_ns).c_str());
    CATCH_BLOCK
}

uint8_t PwmChannel::setPolarity(const pwm_polarity_e polarity)
{
    TRY_BLOCK
    int result_snprintf = 0;
    if(polarity != PWM_POLARITY_NORMAL && polarity != PWM_POLARITY_INVERSED)
        return FAILURE;

    char polarity_pwm[MAX_LEN_STR];
    result_snprintf = snprintf(polarity_pwm, (MAX_LEN_STR * sizeof(char)), "/sys/class/pwm/pwmchip%d/pwm%d/polarity", npwmchip,npwm);

    if(result_snprintf == 0)
        return FAILURE;

    if(polarity == PWM_POLARITY_NORMAL)
    {
        return writeFile(polarity_pwm, POLARITY_NORMAL);
    } else
        return writeFile(polarity_pwm, POLARITY_INVERSED);
    CATCH_BLOCK
}

uint8_t PwmChannel::writeFile(const char* fname,  const char* text)
{
    TRY_BLOCK
    if(fname == nullptr)
        return FAILURE;

    try {
        FILE* sysfs_handler = fopen(fname, "w");

        if(sysfs_handler == NULL)
        {
            throw std::runtime_error("File opening error!");
        }

        size_t data_size = strlen(text);
        size_t bytes_written = fwrite(text, sizeof(char), strlen(text), sysfs_handler);
        fclose(sysfs_handler);

        if(data_size != bytes_written)
        {
            throw std::runtime_error("Error writing data to a file!");
        }
        std::cout << "Data has been successfully recorded! "<< fname<< std::endl;
        return SUCCESS;

        //system();

    } catch (const std::exception& error) {
        std::cerr << "Error: "<<error.what() << std::endl;
        return FAILURE;
    }
    CATCH_BLOCK
}

pwm_enable_e PwmChannel::getEnable()
{
    TRY_BLOCK
    int result_snprintf = 0;
    char enable_pwm[MAX_LEN_STR];
    result_snprintf = snprintf(enable_pwm, (MAX_LEN_STR * sizeof(char)), "/sys/class/pwm/pwmchip%d/pwm%d/enable", npwmchip,npwm);

    if(result_snprintf == 0)
        return PWM_ENABLE_ERROR;

    char buffer[MAX_SIZE_BUFFER]{};
    size_t fsize = readFile(enable_pwm, buffer, MAX_SIZE_BUFFER);

    if(strlen(buffer)==0)
        return PWM_ENABLE_ERROR;

    int64_t result = chartoint64(buffer, fsize);

    if(result == 0)
    {
       return PWM_ENABLE_OFF;

    }else if(result == 1)
    {
        return PWM_ENABLE_ON;
    }

    return PWM_ENABLE_ERROR;
    CATCH_BLOCK
}

int64_t PwmChannel::getPeriod()
{
    TRY_BLOCK
    int result_snprintf{};
    char period_pwm[MAX_LEN_STR];
    result_snprintf = snprintf(period_pwm, (MAX_LEN_STR * sizeof(char)), "/sys/class/pwm/pwmchip%d/pwm%d/period", npwmchip,npwm);

    if(result_snprintf == 0)
           return INCORRECT_DATA;

    char buffer[MAX_SIZE_BUFFER]{};
    size_t fsize = readFile(period_pwm, buffer, MAX_SIZE_BUFFER);

    if(strlen(buffer)==0)
        return INCORRECT_DATA;

    int64_t result = chartoint64(buffer, fsize);
    return result;
    CATCH_BLOCK
}

int64_t PwmChannel::getDutyCycle()
{
    TRY_BLOCK
    int result_snprintf{};
    char duty_cycle_pwm[MAX_LEN_STR];
    result_snprintf = snprintf(duty_cycle_pwm, (MAX_LEN_STR * sizeof(char)), "/sys/class/pwm/pwmchip%d/pwm%d/duty_cycle", npwmchip,npwm);

    if(result_snprintf == 0)
            return INCORRECT_DATA;

    char buffer[MAX_SIZE_BUFFER]{};
    size_t fsize = readFile(duty_cycle_pwm, buffer, MAX_SIZE_BUFFER);

    if(strlen(buffer)==0)
        return INCORRECT_DATA;

    int64_t result = chartoint64(buffer, fsize);
    return result;
    CATCH_BLOCK
}

int64_t PwmChannel::chartoint64(char* buffer, long size)
{
    TRY_BLOCK
    uint8_t i;
    int64_t num = 0;

    if(size > MAX_SIZE_BUFFER)//in64_t - 19 символов + 1 если строка содержит символ "\n" или "\0"
        return INCORRECT_DATA;

    for (i = 0; i<size; i++)
    {
        if (buffer[i] == '\0' || buffer[i] == '\n' || isspace((unsigned char) buffer[i]))
        {
            return num;

        } else if (not isdigit(buffer[i]))
        {
            return INCORRECT_DATA;
        }
        num = 10 * num + (buffer[i] - '0');
    }

    return num;
    CATCH_BLOCK
}

pwm_polarity_e PwmChannel::getPolarity()
{
    TRY_BLOCK
    int result_snprintf{};
    char polarity_pwm[MAX_LEN_STR];
    result_snprintf = snprintf(polarity_pwm, (MAX_LEN_STR * sizeof(char)), "/sys/class/pwm/pwmchip%d/pwm%d/polarity", npwmchip,npwm);

    if(result_snprintf == 0)
        return PWM_POLARITY_ERROR;

    char buffer[MAX_SIZE_BUFFER]{};

    size_t fsize = readFile(polarity_pwm, buffer, MAX_SIZE_BUFFER);

    if(strlen(buffer)==0)
        return PWM_POLARITY_ERROR;

    char str[MAX_LEN_STR]{};

    strcopy(str, buffer, fsize);

    if(!strcmp(str,POLARITY_NORMAL))
    {
        return PWM_POLARITY_NORMAL;

    }else if(!strcmp(str,POLARITY_INVERSED))
    {
        return PWM_POLARITY_INVERSED;
    }
    return PWM_POLARITY_ERROR;
    CATCH_BLOCK
}

void PwmChannel::strcopy(char *destination_str, const char *source_str, const long size)
{
    TRY_BLOCK
  for(int i=0; i<size; i++)
  {
      if(source_str[i] == '\0' || source_str[i] == '\n' || isspace((unsigned char) source_str[i])){break;}

        destination_str[i] = source_str[i];
    }
    CATCH_BLOCK
}

long PwmChannel::getFileSize(const char* fname)
{
    TRY_BLOCK
    FILE* sysfs_handler = fopen(fname, "r");

    if (sysfs_handler == NULL)
    {
        return -1;
    }

    fseek(sysfs_handler, 0, SEEK_END);//переместить внутренний указатель в конец файла
    long fsize = ftell(sysfs_handler);   //вернуть текущее положение внутреннего указателя
    fclose(sysfs_handler);

    return (sizeof(char) * fsize); //память для хранения содержимого файла
    CATCH_BLOCK
}

size_t PwmChannel::readFile(const char* fname, char* buff, const long fsize)
{
    TRY_BLOCK
    FILE* sysfs_handler = fopen(fname, "r");

    if (sysfs_handler == NULL)
        return 0;

    size_t result = fread(buff, 1, fsize, sysfs_handler);       // считываем файл в буфер
    fclose(sysfs_handler);

    return result;
    CATCH_BLOCK
}

uint8_t PwmChannel::setPeriodAndDutyCycle(const int64_t period_ns, const int64_t duty_cycle_ns)
{
    TRY_BLOCK
    uint8_t result_period{};
    uint8_t result_duty_cycle{};

    if(period_ns < duty_cycle_ns)
        return FAILURE;

    if(period_ns <= getDutyCycle())
    {
        result_duty_cycle = setDutyCycle(duty_cycle_ns);
        result_period = setPeriod(period_ns);
        return result_period | result_duty_cycle;

    }else{
        result_period = setPeriod(period_ns);
        result_duty_cycle = setDutyCycle(duty_cycle_ns);
        return result_period | result_duty_cycle;
    }
    CATCH_BLOCK
}

PwmChannel::~PwmChannel()
{
    unexportPWM();
}

PwmChannel::PwmChannel(const uint16_t npwmchip, const uint16_t npwm, pwm_rdwr_data_t* pwm)
{
    this->npwm = npwm;
    this->npwmchip = npwmchip;
    exportPWM();
    pwm_ctrl(pwm);
}

void PwmChannel::pwm_ctrl(pwm_rdwr_data_t* pwm)
{
    TRY_BLOCK
    if(pwm == nullptr)
        return;

    for(int i = 0; i<pwm->counter_buffer && pwm->counter_buffer>0; i++, pwm->buffer++)
    {
        if(pwm->buffer->pwm_flags == PWM_READ)
        {
            pwm->buffer->period_ns = getPeriod();
            pwm->buffer->duty_cycle_ns = getDutyCycle();
            pwm->buffer->enable = getEnable();
            pwm->buffer->polarity = getPolarity();

        }else if(pwm->buffer->pwm_flags == PWM_WRITE){
            setPeriodAndDutyCycle(pwm->buffer->period_ns, pwm->buffer->duty_cycle_ns);
            setPolarity(pwm->buffer->polarity);
            setEnable(pwm->buffer->enable);
        }
    }
    return;
    CATCH_BLOCK
}

void PwmChannel::pwm_settings(pwm_parameters_t* pwm)
{
    TRY_BLOCK
    if(pwm == nullptr)
        return;

    if(pwm->pwm_flags == PWM_WRITE)
    {
        setPeriodAndDutyCycle(pwm->period_ns, pwm->duty_cycle_ns);
        setPolarity(pwm->polarity);
    }
    CATCH_BLOCK
}
