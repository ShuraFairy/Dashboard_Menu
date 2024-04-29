#ifndef PLAYLISTWAV_H
#define PLAYLISTWAV_H

#include <map>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <QMediaPlayer>
#include <QObject>
#include "./Logger/exception_define.h"

class PlaylistWAV : public QObject
{
    Q_OBJECT

public:
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

    typedef struct{
         const char* sound;
         uint8_t volume;
         types_sounds_e type_sound;
         uint8_t priority;
         uint8_t reccurence;
    }wav_audio_file_t;

    typedef std::map<types_sounds_e, wav_audio_file_t> map_wav_t;

    explicit PlaylistWAV(QObject *parent = nullptr);
    ~PlaylistWAV();

    //void init_playlist();
    map_wav_t* get_map_wav(){return &map_wav;};

    //void set_playback_status_wav(const types_sounds_e types_sounds, const bool request);
    void set_volume_wav(const types_sounds_e types_sounds, const uint8_t volume);

    static PlaylistWAV* getInstance();
    void add_wav(const wav_audio_file_t wav_audio_file);

private:
    map_wav_t map_wav{};

signals:
    void request_changed(types_sounds_e types_sounds);

};

#endif // PLAYLISTWAV_H
