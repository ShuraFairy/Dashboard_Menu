#include "playlisthandlerwav.h"

#define ALARM_SOUND         "qrc:/Sounds/001_MVP12_Snd.wav"
#define WARNING_SOUND       "qrc:/Sounds/004_MVP12_Snd.wav"
#define SOUND_TURN_SIGNALS  "qrc:/Sounds/002_MVP12_Snd.wav"
#define INFO_SOUND          "qrc:/Sounds/003_MVP12_Snd.wav"

#define MAX_NUM_ALARM_SIGNALS 25
#define MAX_NUM_WARNING_SIGNALS 11
#define MAX_NUM_TURN_SIGNALS 2
#define MAX_NUM_INFO_SIGNALS 10

shared_ptr<PlaylistHandlerWav> PlaylistHandlerWav::m_ptr_instance(nullptr);
mutex PlaylistHandlerWav::m_build_mutex;

PlaylistHandlerWav::PlaylistHandlerWav()
{
    m_ptr_cached_msgs = HmiHandler::getInstance();
    player = new QMediaPlayer;
    playlist_wav = new PlaylistWAV;
    init_playlist();
    init_map_signals();
}

PlaylistHandlerWav::~PlaylistHandlerWav()
{
    delete player;
    delete playlist_wav;
}

PlaylistHandlerWav* PlaylistHandlerWav::getInstance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = make_shared<PlaylistHandlerWav>();
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

void PlaylistHandlerWav::play(const char* sound, int volume)
{
    TRY_BLOCK
    if(sound == nullptr || volume == 0)
        return;

    player->setMedia(QUrl(sound));
    player->setVolume(volume);
    player->play();

    return;
    CATCH_BLOCK
}

void PlaylistHandlerWav::init_playlist()
{
    TRY_BLOCK
    if(playlist_wav==nullptr)
        return;

    PlaylistWAV::wav_audio_file_t wav_audio_file;
    //**** ALARM_SOUND
    {
        wav_audio_file.sound = ALARM_SOUND;
        wav_audio_file.type_sound = PlaylistWAV::TYPE_SOUND_ALARM;
        wav_audio_file.volume = 100;
        wav_audio_file.priority = 1;
        playlist_wav->add_wav(wav_audio_file);
    }

    //**** WARNING_SOUND
    {
        wav_audio_file.sound = WARNING_SOUND;
        wav_audio_file.type_sound = PlaylistWAV::TYPE_SOUND_WARNING;
        wav_audio_file.volume = 100;
        wav_audio_file.priority = 2;
        playlist_wav->add_wav(wav_audio_file);
    }

    //**** SOUND_TURN_SIGNALS
    {
        wav_audio_file.sound = SOUND_TURN_SIGNALS;
        wav_audio_file.type_sound = PlaylistWAV::TYPE_SOUND_TURN_SIGNALS;
        wav_audio_file.volume = 100;
        wav_audio_file.priority = 3;
        playlist_wav->add_wav(wav_audio_file);
    }

    map_wav = playlist_wav->get_map_wav();
    CATCH_BLOCK
}

void PlaylistHandlerWav::run(PlaylistWAV::wav_audio_file_t* wav_file)
{
    TRY_BLOCK
    if(wav_file == nullptr)
        return;

    switch(player->state()){
    case QMediaPlayer::StoppedState:

        prev_wav_audio_file = wav_file;
        play(wav_file->sound, wav_file->volume);
        break;

    case QMediaPlayer::PlayingState:

        if(wav_file->priority > prev_wav_audio_file->priority || wav_file->priority == prev_wav_audio_file->priority)
        {
            return;
        }else if(wav_file->priority < prev_wav_audio_file->priority)
        {
            player->stop();
            prev_wav_audio_file = wav_file;
            play(wav_file->sound, wav_file->volume);
        }
        break;

    case QMediaPlayer::PausedState:

        break;
    }
    CATCH_BLOCK
}

void PlaylistHandlerWav::find_wav_file(PlaylistWAV::types_sounds_e types_sounds)
{
    TRY_BLOCK
    if(map_wav == nullptr)
        return;

    auto it = map_wav->find(types_sounds);
    if(it != map_wav->end())
    {
        run(&it->second);
    }
    CATCH_BLOCK
}

void PlaylistHandlerWav::find_signal(PlaylistWAV::types_sounds_e types_sounds)
{
    TRY_BLOCK
    if(map_signals.empty())
        return;

    PlaylistWAV::playback_status_e playback_status{};

    auto it = map_signals.find(types_sounds);
    if(it != map_signals.end())
    {
        for(unsigned i=0; i< it->second.size(); i++)
        {
            if(!it->second[i].playback_req)
                it->second[i].playback_status = PlaylistWAV::PLAYBACK_STATUS_NOTACTIVE;

            if(it->second[i].playback_req && it->second[i].playback_status == PlaylistWAV::PLAYBACK_STATUS_NOTACTIVE && playback_status == PlaylistWAV::PLAYBACK_STATUS_NOTREQUIRED)
            {
                it->second[i].playback_status = PlaylistWAV::PLAYBACK_STATUS_NOTREQUIRED;
            } else if(it->second[i].playback_req && it->second[i].playback_status == PlaylistWAV::PLAYBACK_STATUS_NOTACTIVE)
            {
                find_wav_file(types_sounds);
                it->second[i].playback_status= PlaylistWAV::PLAYBACK_STATUS_NOTREQUIRED;
                playback_status = PlaylistWAV::PLAYBACK_STATUS_NOTREQUIRED;
            }
        }
    }
    CATCH_BLOCK
}

void PlaylistHandlerWav::init_map_signals()
{
    TRY_BLOCK
    std::vector<signal_par_t> _signals_par{};
    signal_par_t signal_par{};
    //ALARM SIGNAL
    signal_par.priority = 0;
    signal_par.type_sound = PlaylistWAV::TYPE_SOUND_ALARM;
    signal_par.playback_req = false;
    signal_par.playback_status = PlaylistWAV::PLAYBACK_STATUS_NOTACTIVE;

    _signals_par.clear();

    for(int i=0; i < MAX_NUM_ALARM_SIGNALS; i++)
    {
        _signals_par.push_back(signal_par);
    }
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM]=(_signals_par);

    //WARNING SIGNAL
    signal_par.priority = 0;
    signal_par.type_sound = PlaylistWAV::TYPE_SOUND_WARNING;
    signal_par.playback_req = false;
    signal_par.playback_status = PlaylistWAV::PLAYBACK_STATUS_NOTACTIVE;

    _signals_par.clear();

    for(int i=0; i < MAX_NUM_WARNING_SIGNALS; i++)
    {
        _signals_par.push_back(signal_par);
    }
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING]=(_signals_par);

    //TURN SIGNALS SIGNAL
    signal_par.priority = 0;
    signal_par.type_sound = PlaylistWAV::TYPE_SOUND_TURN_SIGNALS;
    signal_par.playback_req = false;
    signal_par.playback_status = PlaylistWAV::PLAYBACK_STATUS_NOTACTIVE;

    _signals_par.clear();

    for(int i=0; i < MAX_NUM_TURN_SIGNALS; i++)
    {
        _signals_par.push_back(signal_par);
    }
    map_signals[PlaylistWAV::TYPE_SOUND_TURN_SIGNALS]=(_signals_par);
    CATCH_BLOCK
}

void PlaylistHandlerWav::run_playlist()
{
    TRY_BLOCK
    qDebug("WAV audio");
    TT_GRP_A_t* msg_grpa = reinterpret_cast<TT_GRP_A_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_A_ID));
    TT_GRP_B_t* msg_grpb = reinterpret_cast<TT_GRP_B_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_B_ID));
    TT_GRP_E_t* msg_grpe = reinterpret_cast<TT_GRP_E_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_E_ID));
    TT_GRP_F_t* msg_grpf = reinterpret_cast<TT_GRP_F_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_F_ID));
    TT_GRP_G_t* msg_grpg = reinterpret_cast<TT_GRP_G_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_G_ID));
    TT_GRP_H_t* msg_grph = reinterpret_cast<TT_GRP_H_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_H_ID));
    TT_GRP_K_t* msg_grpk = reinterpret_cast<TT_GRP_K_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_K_ID));
    TT_GRP_M_t* msg_grpm = reinterpret_cast<TT_GRP_M_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_M_ID));
    TT_GRP_P_t* msg_grpp = reinterpret_cast<TT_GRP_P_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_P_ID));
    TT_GRP_I_t* msg_grpi = reinterpret_cast<TT_GRP_I_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_I_ID));

    //*********TYPE_SOUND_ALARM
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][0].playback_req = (msg_grpb->B01 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][1].playback_req = (msg_grpb->B02 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][2].playback_req = (msg_grpb->B03 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][3].playback_req = (msg_grpb->B04 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][4].playback_req = (msg_grpb->B15 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][5].playback_req = (msg_grpb->B22 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][6].playback_req = (msg_grpb->B23 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][7].playback_req = (msg_grpf->F03 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][9].playback_req = (msg_grpf->F05 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][10].playback_req = (msg_grpg->G21 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][11].playback_req = (msg_grpg->G22 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][12].playback_req = (msg_grpg->G26 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][13].playback_req = (msg_grph->H05 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][14].playback_req = (msg_grpk->K01 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][15].playback_req = (msg_grpk->K32 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][16].playback_req = (msg_grpk->K34 == 2);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][17].playback_req = (msg_grpk->K35 == 2);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][18].playback_req = (msg_grpm->M01 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][19].playback_req = (msg_grpp->P08 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][20].playback_req = (msg_grpb->B26 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][21].playback_req = (msg_grpf->F04 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][22].playback_req = (msg_grpf->F18 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][23].playback_req = (msg_grpg->G10 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_ALARM][24].playback_req = (msg_grpi->I30 == 2);
    find_signal(PlaylistWAV::TYPE_SOUND_ALARM);

    //*********TYPE_SOUND_WARNING
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][0].playback_req = (msg_grpb->B10 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][1].playback_req = (msg_grpe->E20 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][2].playback_req = (msg_grpf->F01 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][3].playback_req = (msg_grpf->F02 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][4].playback_req = (msg_grpf->F15 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][5].playback_req = (msg_grpg->G01 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][6].playback_req = (msg_grpk->K28 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][7].playback_req = (msg_grpk->K35 == 1);

    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][8].playback_req = (msg_grpf->F22 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][9].playback_req = (msg_grpg->G10 == 1);
    map_signals[PlaylistWAV::TYPE_SOUND_WARNING][10].playback_req = (msg_grpi->I30 == 1);
    find_signal(PlaylistWAV::TYPE_SOUND_WARNING);

    //*********TYPE_SOUND_TURN_SIGNALS
    map_signals[PlaylistWAV::TYPE_SOUND_TURN_SIGNALS][0].playback_req = ((msg_grpa->A40 == 1) || (msg_grpa->A41 == 1));
    find_signal(PlaylistWAV::TYPE_SOUND_TURN_SIGNALS);
    CATCH_BLOCK
}

