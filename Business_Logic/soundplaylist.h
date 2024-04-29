#ifndef SOUNDPLAYLIST_H
#define SOUNDPLAYLIST_H

#include "Connectivity/hmi_handler.h"
#include <QObject>
#include <stdint.h>
#include <map>
#include <vector>
#include "sound_handler.h"
#include "./Logger/exception_define.h"
#include "./Interfaces/iplaylist.h"

typedef enum {
    //GRP B
    B01_ALARM = 0u,
    B02_ALARM,
    B03_ALARM,
    B04_ALARM,
    B15_ALARM,
    B22_ALARM,
    B23_ALARM,
    B26_ALARM,
    //GRP F
    F03_ALARM,
    F04_ALARM,
    F05_ALARM,
    F18_ALARM,
    //GRP G
    G21_ALARM,
    G22_ALARM,
    G26_ALARM,
    G10_ALARM,
    //GRP H
    H05_ALARM,
    //GRP I
    I30_ALARM,
    //GRP K
    K01_ALARM,
    K32_ALARM,
    K34_ALARM,
    K35_ALARM,
    //GRP M
    M01_ALARM,
    //GRP P
    P08_ALARM,
    TOTAL_ALARM_INDICATORS
}alarm_indicators_e;

typedef enum {
    //GRP B
    B10_WARNING = 0u,
    //GRP E
    E20_WARNING,
    //GRP F
    F01_WARNING,
    F02_WARNING,
    F15_WARNING,
    F22_WARNING,
    G01_WARNING,
    //GRP I
    I30_WARNING,
    //GRP K
    K28_WARNING,
    K35_WARNING,
    TOTAL_WARNING_INDICATORS
}warning_indicators_e;

class SoundPlaylist : public IPlaylist
{   
public:
    SoundPlaylist();
    static SoundPlaylist* getInstance();
    ~SoundPlaylist();

    void run_playlist() override;
private:
    void update_playback_status();

    int request_handler(std::map<types_sounds_e, std::vector<SoundHandler::sound_req_t>>::iterator it_list_sounds,  uint8_t number_signals);
    void playlist_handler();
    void update_playlist();
    void init_playlist() override;

    static shared_ptr<SoundPlaylist> m_ptr_instance;
    static mutex m_build_mutex;

    HmiHandler* m_ptr_cached_msgs;
    SoundHandler* obj_sound_player;
    playback_status_e cmd_audio_player;
    SoundHandler::sound_req_t* prev_sound;
    std::map<types_sounds_e, std::vector<SoundHandler::sound_req_t>> list_sounds;
};

#endif // SOUNDPLAYLIST_H
