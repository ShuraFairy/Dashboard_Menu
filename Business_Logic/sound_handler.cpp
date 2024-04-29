#include "sound_handler.h"
#include <QDebug>
#include <time.h>


SoundHandler::SoundHandler(const uint16_t npwmchip, const uint16_t npwm)
    : PwmChannel(npwmchip, npwm)
{
    create_sound();
}


SoundHandler::~SoundHandler()
{
    setEnable(PWM_ENABLE_OFF);//Firs turn off PWM
    unexportPWM();
}

uint64_t curtime() {
    TRY_BLOCK
  return std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
  ).count();
    CATCH_BLOCK
}

void SoundHandler::create_sound()
{
    TRY_BLOCK
    sound_handler_data_t sound_handler_data{};
    pwm_parameters_t pwm_parameters{};
    sound_parameters_t sound_parameters{};

    /*----------ALARM_SOUND----------*/
    {
        pwm_parameters.enable = PWM_ENABLE_OFF;
        pwm_parameters.period_ns = 300000;
        pwm_parameters.duty_cycle_ns = 150000;
        pwm_parameters.polarity = PWM_POLARITY_NORMAL;
        pwm_parameters.pwm_flags = PWM_WRITE;

        sound_parameters.priority = 0;
        sound_parameters.duration_ms = 600;
        sound_parameters.reccurence = 1;
        sound_parameters.interruptability = 0;

        sound_handler_data.pwm_parameters = pwm_parameters;
        sound_handler_data.sound_parameters = sound_parameters;
        map_sound_handler_data.insert(std::make_pair(TYPE_SOUND_ALARM, sound_handler_data));
    }

    /*----------WARNING_SOUND----------*/
    {
        pwm_parameters.enable = PWM_ENABLE_OFF;
        pwm_parameters.period_ns = 250000;
        pwm_parameters.duty_cycle_ns = 180000;
        pwm_parameters.polarity = PWM_POLARITY_NORMAL;
        pwm_parameters.pwm_flags = PWM_WRITE;

        sound_parameters.priority = 1;
        sound_parameters.duration_ms = 400;
        sound_parameters.reccurence = 1;
        sound_parameters.interruptability = 0;

        sound_handler_data.pwm_parameters = pwm_parameters;
        sound_handler_data.sound_parameters = sound_parameters;
        map_sound_handler_data.insert(std::make_pair(TYPE_SOUND_WARNING, sound_handler_data));
    }

    /*----------TURN_SIGNALS_SOUND----------*/
    {
        pwm_parameters.enable = PWM_ENABLE_OFF;
        pwm_parameters.period_ns = 4000000;
        pwm_parameters.duty_cycle_ns = 2500000;
        pwm_parameters.polarity = PWM_POLARITY_NORMAL;
        pwm_parameters.pwm_flags = PWM_WRITE;

        sound_parameters.priority = 2;
        sound_parameters.duration_ms = 200;
        sound_parameters.reccurence = 1;
        sound_parameters.interruptability = 0;

        sound_handler_data.pwm_parameters = pwm_parameters;
        sound_handler_data.sound_parameters = sound_parameters;
        map_sound_handler_data.insert(std::make_pair(TYPE_SOUND_TURN_SIGNALS, sound_handler_data));
      }

    /*----------INFO_SOUND----------*/
    {
        pwm_parameters.enable = PWM_ENABLE_OFF;
        pwm_parameters.period_ns = 10000000;
        pwm_parameters.duty_cycle_ns = 500000;
        pwm_parameters.polarity = PWM_POLARITY_NORMAL;
        pwm_parameters.pwm_flags = PWM_WRITE;

        sound_parameters.priority = 3;
        sound_parameters.duration_ms = 100;
        sound_parameters.reccurence = 1;
        sound_parameters.interruptability = 0;

        sound_handler_data.pwm_parameters = pwm_parameters;
        sound_handler_data.sound_parameters = sound_parameters;
        map_sound_handler_data.insert(std::make_pair(TYPE_SOUND_INFO, sound_handler_data));
      }
    CATCH_BLOCK
}

void SoundHandler::play(pwm_parameters_t* pwm_parameters)
{
    TRY_BLOCK
    setEnable(PWM_ENABLE_OFF);//Firs turn off PWM
    pwm_settings(pwm_parameters);
    setEnable(pwm_parameters->enable);
    CATCH_BLOCK
}

void SoundHandler::ctrl_audio_player(audio_player_e cmd_audio_player)
{
    TRY_BLOCK
    this->cmd_audio_player = cmd_audio_player;
    CATCH_BLOCK
}

void SoundHandler::audio_player()
{
    TRY_BLOCK
    std::map<types_sounds_e, sound_handler_data_t>::iterator map_it;

    static uint64_t begin_time = 0, current_time = 0;
    //uint8_t i = 0;
    pwm_enable_e pwm_enable;

    if(map_sound_handler_data.empty())
        return;

    if(cmd_audio_player == AUDIO_PLAYER_OFF && audio_player_status != AUDIO_PLAYER_OFF)
    {
        pwm_enable = getEnable();
        begin_time = current_time = curtime();

        switch (pwm_enable) {
        case PWM_ENABLE_OFF:
            audio_player_status = AUDIO_PLAYER_OFF;
            break;
        case PWM_ENABLE_ON:
            setEnable(PWM_ENABLE_OFF);
            audio_player_status = (audio_player_e)getEnable();
            break;
        case PWM_ENABLE_ERROR:
            audio_player_status = AUDIO_PLAYER_ERROR;
            setEnable(PWM_ENABLE_OFF);
            break;
        }
    }

    if((sound != nullptr) && (sound->type_sound != TYPE_SOUND_NOTDEFINED))
    {
        map_it = map_sound_handler_data.find(sound->type_sound);

        if(map_it != map_sound_handler_data.end() && map_it->second.sound_parameters.duration_ms > 0)
        {
            if(cmd_audio_player == AUDIO_PLAYER_ON && audio_player_status != AUDIO_PLAYER_START)//start
            {
                audio_player_status = AUDIO_PLAYER_ON;
                    map_it->second.pwm_parameters.enable = PWM_ENABLE_ON;
                    play(&map_it->second.pwm_parameters);
                    pwm_enable = getEnable();

                    switch (pwm_enable) {
                        case PWM_ENABLE_OFF:
                             qDebug()<<"PWM = OFF\n";
                            break;
                        case PWM_ENABLE_ON:
                            qDebug()<<"PWM = ON\n";
                            begin_time = current_time = curtime();
                            audio_player_status = AUDIO_PLAYER_START;
                            sound->playback_status = PLAYBACK_STATUS_ACTIVE;
                            break;
                        case PWM_ENABLE_ERROR:
                            qDebug()<<"PWM = Error\n";
                            begin_time = current_time = curtime();
                            audio_player_status = AUDIO_PLAYER_ERROR;
                            sound->playback_status = PLAYBACK_STATUS_ERROR;
                            break;
                    }

            }else if (audio_player_status == AUDIO_PLAYER_START && current_time - begin_time < map_it->second.sound_parameters.duration_ms)
            {
                current_time = curtime();

            } else if (audio_player_status == AUDIO_PLAYER_START)
            {
                cmd_audio_player = AUDIO_PLAYER_OFF;
                map_it->second.pwm_parameters.enable = PWM_ENABLE_OFF;
                play(&map_it->second.pwm_parameters);
                begin_time = current_time = curtime();

                pwm_enable = getEnable();

                switch (pwm_enable) {
                    case PWM_ENABLE_OFF:
                         qDebug()<<"PWM = OFF\n";
                         begin_time = current_time = curtime();
                         audio_player_status = AUDIO_PLAYER_STOP;
                         sound->playback_status = PLAYBACK_STATUS_FINISHED;
                        break;
                    case PWM_ENABLE_ON:
                        qDebug()<<"The PWM channel is not turned off!\n";
                        break;
                    case PWM_ENABLE_ERROR:
                        qDebug()<<"PWM = Error\n";
                        begin_time = current_time = curtime();
                        audio_player_status = AUDIO_PLAYER_ERROR;
                        sound->playback_status = PLAYBACK_STATUS_ERROR;
                        break;
                }
            }
        }
    }
    CATCH_BLOCK
}

void SoundHandler::set_sound(sound_req_t* new_sound)
{
    TRY_BLOCK
    if(new_sound == nullptr)
        return;

    this->sound=new_sound;
    CATCH_BLOCK
}
