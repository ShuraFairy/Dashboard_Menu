#ifndef QTPLAYLISTHANDLERWAV_H
#define QTPLAYLISTHANDLERWAV_H

#include "Connectivity/hmi_handler.h"
#include <map>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <QMediaPlayer>
#include <QObject>
#include "playlistwav.h"
#include "./Logger/exception_define.h"
#include "./Interfaces/iplaylist.h"

class PlaylistHandlerWav : public IPlaylist
{
    Q_OBJECT
public:
    explicit PlaylistHandlerWav();
    ~PlaylistHandlerWav();

    static PlaylistHandlerWav* getInstance();
    void run_playlist() override;
private:
    QMediaPlayer* player = nullptr;
    PlaylistWAV* playlist_wav = nullptr;
    PlaylistWAV::map_wav_t* map_wav = nullptr;

    typedef struct{
         PlaylistWAV::types_sounds_e type_sound;
         uint8_t priority;
         PlaylistWAV::playback_status_e playback_status;
         bool playback_req;
    }signal_par_t;


    void play(const char* sound, int volume);
    void init_playlist() override;
    void run(PlaylistWAV::wav_audio_file_t* wav_file);
    void find_wav_file(PlaylistWAV::types_sounds_e types_sounds);
    void find_signal(PlaylistWAV::types_sounds_e types_sounds);
    void init_map_signals();
    static shared_ptr<PlaylistHandlerWav> m_ptr_instance;
    static mutex m_build_mutex;
    HmiHandler* m_ptr_cached_msgs;
    PlaylistWAV::wav_audio_file_t* prev_wav_audio_file = nullptr;
    std::map<PlaylistWAV::types_sounds_e, std::vector<signal_par_t>> map_signals{};
};

#endif // QTPLAYLISTHANDLERWAV_H
