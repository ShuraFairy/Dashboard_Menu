#include "playlistwav.h"

PlaylistWAV::PlaylistWAV(QObject *parent) : QObject(parent)
{

}

PlaylistWAV::~PlaylistWAV()
{

}

PlaylistWAV* PlaylistWAV::getInstance()
{
    TRY_BLOCK
    static PlaylistWAV instance;
    return &instance;
    CATCH_BLOCK
}

void PlaylistWAV::add_wav(const wav_audio_file_t wav_audio_file)
{
    TRY_BLOCK
    map_wav[wav_audio_file.type_sound]=(wav_audio_file);
    CATCH_BLOCK
}

void PlaylistWAV::set_volume_wav(const types_sounds_e types_sounds, const uint8_t volume)
{
    TRY_BLOCK
    auto it = map_wav.find(types_sounds);
    if(it != map_wav.end())
    {
        map_wav[types_sounds].volume = volume;
    }
    CATCH_BLOCK
}
