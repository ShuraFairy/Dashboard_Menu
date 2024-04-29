#ifndef SOUND_HANDLER_H
#define SOUND_HANDLER_H

#include "Connectivity/pwmchannel.h"
#include <map>
#include <vector>
#include <stdint.h>
#include "./Logger/exception_define.h"

typedef enum{
    PLAYBACK_STATUS_NOTDEFINED,
    PLAYBACK_STATUS_NOTACTIVE,
    PLAYBACK_STATUS_ACTIVE,
    PLAYBACK_STATUS_STOP,
    PLAYBACK_STATUS_FINISHED,
    PLAYBACK_STATUS_NOTREQUIRED,
    PLAYBACK_STATUS_INTERRUPTED,
    PLAYBACK_STATUS_ERROR
}playback_status_e;

typedef enum{
    TYPE_SOUND_NOTDEFINED,
    TYPE_SOUND_ALARM,
    TYPE_SOUND_WARNING,
    TYPE_SOUND_TURN_SIGNALS,
    TYPE_SOUND_INFO
}types_sounds_e;

typedef enum{
    AUDIO_PLAYER_OFF,
    AUDIO_PLAYER_ON,
    AUDIO_PLAYER_START,
    AUDIO_PLAYER_STOP,
    AUDIO_PLAYER_ERROR
}audio_player_e;

class SoundHandler : PwmChannel
{
    typedef struct{
        uint8_t priority;
        uint16_t duration_ms;
        uint8_t reccurence;
        uint8_t interruptability;
    }sound_parameters_t;

    typedef struct{
        pwm_parameters_t pwm_parameters;
        sound_parameters_t sound_parameters;
    }sound_handler_data_t;

public:

    typedef struct{
        uint8_t priority;
        types_sounds_e type_sound;
        uint8_t reccurence;
        pwm_enable_e req_play_sound;
        playback_status_e playback_status;
    }sound_req_t;

    SoundHandler(const uint16_t npwmchip, const uint16_t npwm);
    ~SoundHandler();
    void audio_player();
    audio_player_e get_audio_player_status(){return audio_player_status;};
    void ctrl_audio_player(audio_player_e audio_player);
    void set_sound(sound_req_t* new_sound);

private:
    std::map<types_sounds_e, sound_handler_data_t> map_sound_handler_data;
    sound_req_t* sound = nullptr;
    audio_player_e audio_player_status{};
    audio_player_e cmd_audio_player{};

    void create_sound();
    void play(pwm_parameters_t* pwm_parameters);

};

#endif // SOUND_HANDLER_H
