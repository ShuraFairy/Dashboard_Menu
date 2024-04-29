#include "soundplaylist.h"
#include <QDebug>
#include <thread>

#define MAX_NUM_TURN_SIGNALS 1
#define MAX_NUM_INFO_SIGNALS 1
#define FIND_NEX_SOUND_SIGNAL 0
#define CHECK_NEX_TYPE_SOUND 1
#define SIGNLE_READ_Mask2 0x03U

shared_ptr<SoundPlaylist> SoundPlaylist::m_ptr_instance(nullptr);
mutex SoundPlaylist::m_build_mutex;

SoundPlaylist::SoundPlaylist()
{
    prev_sound = new SoundHandler::sound_req_t;
    obj_sound_player = new SoundHandler(0,0);
    m_ptr_cached_msgs = HmiHandler::getInstance();
    init_playlist();
}

SoundPlaylist* SoundPlaylist::getInstance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = make_shared<SoundPlaylist>();
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

SoundPlaylist::~SoundPlaylist()
{
    qDebug()<<"Destructor SoundPlaylist\n";
}

void SoundPlaylist::init_playlist()
{
    TRY_BLOCK
    qDebug()<<"init_playlist\n";

    std::vector<SoundHandler::sound_req_t> sound_signals{};
    SoundHandler::sound_req_t set_sound;

    //**** ALARM_SOUND
    {
        set_sound.req_play_sound = PWM_ENABLE_OFF;
        set_sound.reccurence = 1;
        set_sound.priority = 1;
        set_sound.type_sound = TYPE_SOUND_ALARM;
        set_sound.playback_status = PLAYBACK_STATUS_NOTACTIVE;
        sound_signals.clear();

        for(uint8_t i = 0; i < TOTAL_ALARM_INDICATORS; i++)
        {
            sound_signals.push_back(set_sound);
        }
        list_sounds[TYPE_SOUND_ALARM]=(sound_signals);
    }

    //**** WARNING_SOUND
    {
        set_sound.req_play_sound = PWM_ENABLE_OFF;
        set_sound.reccurence = 1;
        set_sound.priority = 2;
        set_sound.type_sound = TYPE_SOUND_WARNING;
        set_sound.playback_status = PLAYBACK_STATUS_NOTACTIVE;
        sound_signals.clear();

        for(uint8_t i = 0; i<TOTAL_WARNING_INDICATORS; i++)
        {
            sound_signals.push_back(set_sound);
        }
       list_sounds[TYPE_SOUND_WARNING]=(sound_signals);
    }

    //**** TURN_SIGNALS_SOUND
    {
        set_sound.req_play_sound = PWM_ENABLE_OFF;
        set_sound.reccurence = 1;
        set_sound.priority = 3;
        set_sound.type_sound = TYPE_SOUND_TURN_SIGNALS;
        set_sound.playback_status = PLAYBACK_STATUS_NOTACTIVE;
        sound_signals.clear();

        for(uint8_t i = 0; i<MAX_NUM_TURN_SIGNALS; i++)
        {
            sound_signals.push_back(set_sound);
        }
        list_sounds[TYPE_SOUND_TURN_SIGNALS]=(sound_signals);
    }


    //**** INFO_SOUND
    {
        set_sound.req_play_sound = PWM_ENABLE_OFF;
        set_sound.reccurence = 1;
        set_sound.priority = 4;
        set_sound.type_sound = TYPE_SOUND_INFO;
        set_sound.playback_status = PLAYBACK_STATUS_NOTACTIVE;
        sound_signals.clear();

        for(uint8_t i = 0; i<MAX_NUM_INFO_SIGNALS; i++)
        {
            sound_signals.push_back(set_sound);
        }
        list_sounds[TYPE_SOUND_INFO]=(sound_signals);
    }
    // std::thread thread_player(&SoundPlaylist::run_playlist, this);
    // thread_player.detach();
    CATCH_BLOCK
}


void SoundPlaylist::update_playback_status()
{
    TRY_BLOCK
    bool _reset_all = false;
    uint8_t i{}, j{};
    uint8_t number_signals{};
    std::map<types_sounds_e, std::vector<SoundHandler::sound_req_t>>::iterator it_list_sounds;

    for (it_list_sounds = list_sounds.begin(); it_list_sounds != list_sounds.end(); it_list_sounds++)
    {
        if(it_list_sounds->second.empty())
            continue;

        switch(it_list_sounds->second[0].type_sound){
        case TYPE_SOUND_NOTDEFINED:
            number_signals = 0;
            break;
        case TYPE_SOUND_ALARM:
            number_signals = TOTAL_ALARM_INDICATORS;
            break;
        case TYPE_SOUND_WARNING:
            number_signals = TOTAL_WARNING_INDICATORS;
            break;
        case TYPE_SOUND_TURN_SIGNALS:
            number_signals = MAX_NUM_TURN_SIGNALS;
            break;
        case TYPE_SOUND_INFO:
            number_signals = MAX_NUM_INFO_SIGNALS;
            break;
        }

        for(i = 0; i < number_signals; i++)
        {
            if(!it_list_sounds->second[i].req_play_sound)
            it_list_sounds->second[i].playback_status = PLAYBACK_STATUS_NOTACTIVE;

            if(_reset_all)
            {
                if(it_list_sounds->second[i].req_play_sound)
                    it_list_sounds->second[i].playback_status = PLAYBACK_STATUS_NOTREQUIRED;
            } else {
                //if at least one sound is being played at the moment, then it is unnecessary to play the rest of the sounds
                if(it_list_sounds->second[i].playback_status == PLAYBACK_STATUS_ACTIVE)
                {
                    _reset_all = true;

                    for(j = i+1; j < number_signals; j++)
                    {
                        if(it_list_sounds->second[j].req_play_sound)
                        it_list_sounds->second[j].playback_status = PLAYBACK_STATUS_NOTREQUIRED;
                    }
                }
            }
        }
    }
    CATCH_BLOCK
}

int SoundPlaylist::request_handler(std::map<types_sounds_e, std::vector<SoundHandler::sound_req_t>>::iterator it_list_sounds, uint8_t number_signals)
{
    TRY_BLOCK
    if(it_list_sounds==list_sounds.end() || number_signals < 1)
        return CHECK_NEX_TYPE_SOUND;

    for(uint8_t i = 0; i < number_signals; i++)
    {
        //if at least one sound is being played at the moment, then it is unnecessary to play the rest of the sounds
         if(it_list_sounds->second[i].playback_status == PLAYBACK_STATUS_ACTIVE)
             return FIND_NEX_SOUND_SIGNAL;
    }

    for(uint8_t i =   0; i < number_signals; i++)
    {
        if(it_list_sounds->second[i].req_play_sound && it_list_sounds->second[i].playback_status == PLAYBACK_STATUS_NOTACTIVE)
        {
            switch(obj_sound_player->get_audio_player_status()){

                case AUDIO_PLAYER_OFF:
                        obj_sound_player->set_sound(&it_list_sounds->second[i]);
                        obj_sound_player->ctrl_audio_player(AUDIO_PLAYER_ON);
                        obj_sound_player->audio_player();

                        prev_sound = (&it_list_sounds->second[i]);

                        qDebug()<<"AUDIO_PLAYER_OFF\n";
                        break;

                case AUDIO_PLAYER_ON:
                        qDebug()<<"AUDIO_PLAYER_ON\n";
                        break;
                case AUDIO_PLAYER_START:

                        if((it_list_sounds->second[i].priority) < prev_sound->priority   && prev_sound->type_sound != TYPE_SOUND_NOTDEFINED)
                        {
                            qDebug()<<"prev_sound"<<prev_sound->playback_status<<"\n";
                            obj_sound_player->ctrl_audio_player(AUDIO_PLAYER_OFF);
                            obj_sound_player->audio_player();

                            prev_sound->playback_status = PLAYBACK_STATUS_INTERRUPTED;
                            prev_sound = (&it_list_sounds->second[i]);

                            obj_sound_player->set_sound(&it_list_sounds->second[i]);
                            obj_sound_player->ctrl_audio_player(AUDIO_PLAYER_ON);
                            obj_sound_player->audio_player();
                        }else{
                            it_list_sounds->second[i].playback_status = PLAYBACK_STATUS_NOTREQUIRED;
                        }

                        qDebug()<<"AUDIO_PLAYER_START\n";
                        break;

                case AUDIO_PLAYER_STOP:
                        obj_sound_player->ctrl_audio_player(AUDIO_PLAYER_OFF);
                        obj_sound_player->audio_player();
                        qDebug()<<"AUDIO_PLAYER_STOP\n";
                        break;

                case AUDIO_PLAYER_ERROR:
                        obj_sound_player->ctrl_audio_player(AUDIO_PLAYER_OFF);
                        obj_sound_player->audio_player();
                        qDebug()<<"AUDIO_PLAYER_ERROR\n";
                        break;
            }
            return FIND_NEX_SOUND_SIGNAL;
         }
    }
    return CHECK_NEX_TYPE_SOUND;
    CATCH_BLOCK
}

void SoundPlaylist::run_playlist()
{
    TRY_BLOCK
   /* while(play)
    {*/
        if(!list_sounds.empty())
        {
            update_playlist();
            update_playback_status();
            playlist_handler();
            obj_sound_player->audio_player();
        }
   // }
    CATCH_BLOCK
}

void SoundPlaylist::playlist_handler()
{
    TRY_BLOCK
    //**** ALARM_SOUND
    if(!request_handler(list_sounds.find(TYPE_SOUND_ALARM), TOTAL_ALARM_INDICATORS))
        return;

    //**** WARNING_SOUND
    if(!request_handler(list_sounds.find(TYPE_SOUND_WARNING), TOTAL_WARNING_INDICATORS))
        return;

    //**** TURN_SIGNALS_SOUND
    if(!request_handler(list_sounds.find(TYPE_SOUND_TURN_SIGNALS), MAX_NUM_TURN_SIGNALS))
        return;

    //**** INFO_SOUND
    if(!request_handler(list_sounds.find(TYPE_SOUND_INFO), MAX_NUM_INFO_SIGNALS))
        return;
    CATCH_BLOCK
}

void SoundPlaylist::update_playlist()
{
    TRY_BLOCK
//    qDebug("Playlist audio");
    TT_GRP_A_t* msg_grpa = nullptr;
    TT_GRP_B_t* msg_grpb = nullptr;
    TT_GRP_E_t* msg_grpe = nullptr;
    TT_GRP_F_t* msg_grpf = nullptr;
    TT_GRP_G_t* msg_grpg = nullptr;
    TT_GRP_H_t* msg_grph = nullptr;
    TT_GRP_I_t* msg_grpi = nullptr;
    TT_GRP_K_t* msg_grpk = nullptr;
    TT_GRP_M_t* msg_grpm = nullptr;
    TT_GRP_P_t* msg_grpp = nullptr;


    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_A_ID)->is_updated())
    {
        msg_grpa = reinterpret_cast<TT_GRP_A_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_A_ID));
        //*********TYPE_SOUND_TURN_SIGNALS
        list_sounds[TYPE_SOUND_TURN_SIGNALS][0].req_play_sound = (pwm_enable_e)((msg_grpa->A40 == 1) || (msg_grpa->A41 == 1));
    }
    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_B_ID)->is_updated())
    {
        msg_grpb = reinterpret_cast<TT_GRP_B_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_B_ID));
        //*********TYPE_SOUND_ALARM
        list_sounds[TYPE_SOUND_ALARM][B01_ALARM].req_play_sound = (pwm_enable_e)(msg_grpb->B01 == 1);
        list_sounds[TYPE_SOUND_ALARM][B02_ALARM].req_play_sound = (pwm_enable_e)(msg_grpb->B02 == 1);
        list_sounds[TYPE_SOUND_ALARM][B03_ALARM].req_play_sound = (pwm_enable_e)(msg_grpb->B03 == 1);
        list_sounds[TYPE_SOUND_ALARM][B04_ALARM].req_play_sound = (pwm_enable_e)(msg_grpb->B04 == 1);
        list_sounds[TYPE_SOUND_ALARM][B15_ALARM].req_play_sound = (pwm_enable_e)(msg_grpb->B15 == 1);
        list_sounds[TYPE_SOUND_ALARM][B22_ALARM].req_play_sound = (pwm_enable_e)(msg_grpb->B22 == 1);
        list_sounds[TYPE_SOUND_ALARM][B23_ALARM].req_play_sound = (pwm_enable_e)(msg_grpb->B23 == 1);
        list_sounds[TYPE_SOUND_ALARM][B26_ALARM].req_play_sound = (pwm_enable_e)(msg_grpb->B26 == 1);

        //*********TYPE_SOUND_WARNING
        list_sounds[TYPE_SOUND_WARNING][B10_WARNING].req_play_sound = (pwm_enable_e)(msg_grpb->B10 == 1);
    }
    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_E_ID)->is_updated())
    {
        msg_grpe = reinterpret_cast<TT_GRP_E_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_E_ID));
        //*********TYPE_SOUND_WARNING
        list_sounds[TYPE_SOUND_WARNING][E20_WARNING].req_play_sound = (pwm_enable_e)(msg_grpe->E20 == 1);
    }
    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_F_ID)->is_updated())
    {
        msg_grpf = reinterpret_cast<TT_GRP_F_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_F_ID));
        //*********TYPE_SOUND_ALARM
        list_sounds[TYPE_SOUND_ALARM][F03_ALARM].req_play_sound = (pwm_enable_e)(msg_grpf->F03 == 1);
        list_sounds[TYPE_SOUND_ALARM][F04_ALARM].req_play_sound = (pwm_enable_e)(msg_grpf->F04 == 1);
        list_sounds[TYPE_SOUND_ALARM][F05_ALARM].req_play_sound = (pwm_enable_e)(msg_grpf->F05 == 1);
        list_sounds[TYPE_SOUND_ALARM][F18_ALARM].req_play_sound = (pwm_enable_e)(msg_grpf->F18 == 1);

        //*********TYPE_SOUND_WARNING
        list_sounds[TYPE_SOUND_WARNING][F01_WARNING].req_play_sound = (pwm_enable_e)(msg_grpf->F01 == 1);
        list_sounds[TYPE_SOUND_WARNING][F02_WARNING].req_play_sound = (pwm_enable_e)(msg_grpf->F02 == 1);
        list_sounds[TYPE_SOUND_WARNING][F15_WARNING].req_play_sound = (pwm_enable_e)(msg_grpf->F15 == 1);
        list_sounds[TYPE_SOUND_WARNING][F22_WARNING].req_play_sound = (pwm_enable_e)(msg_grpf->F22 == 1);
    }
    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_G_ID)->is_updated())
    {
        msg_grpg = reinterpret_cast<TT_GRP_G_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_G_ID));
        //*********TYPE_SOUND_ALARM
        list_sounds[TYPE_SOUND_ALARM][G21_ALARM].req_play_sound = (pwm_enable_e)(msg_grpg->G21 == 1);
        list_sounds[TYPE_SOUND_ALARM][G22_ALARM].req_play_sound = (pwm_enable_e)(msg_grpg->G22 == 1);
        list_sounds[TYPE_SOUND_ALARM][G26_ALARM].req_play_sound = (pwm_enable_e)(msg_grpg->G26 == 1);
        list_sounds[TYPE_SOUND_ALARM][G10_ALARM].req_play_sound = (pwm_enable_e)(msg_grpg->G10 == 1);

        //*********TYPE_SOUND_WARNING
        list_sounds[TYPE_SOUND_WARNING][G01_WARNING].req_play_sound = (pwm_enable_e)(msg_grpg->G01 == 1);
    }
    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_H_ID)->is_updated())
    {
        msg_grph = reinterpret_cast<TT_GRP_H_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_H_ID));
        //*********TYPE_SOUND_ALARM
        list_sounds[TYPE_SOUND_ALARM][H05_ALARM].req_play_sound = (pwm_enable_e)(msg_grph->H05 == 1);
    }

    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_I_ID)->is_updated())
    {
        msg_grpi = reinterpret_cast<TT_GRP_I_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_I_ID));
        //*********TYPE_SOUND_ALARM
        list_sounds[TYPE_SOUND_ALARM][I30_ALARM].req_play_sound = (pwm_enable_e)(msg_grpi->I30 ==2);
        //*********TYPE_SOUND_WARNING
        list_sounds[TYPE_SOUND_WARNING][I30_WARNING].req_play_sound = (pwm_enable_e)(msg_grpi->I30 == 1);
    }

    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_K_ID)->is_updated())
    {
        msg_grpk = reinterpret_cast<TT_GRP_K_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_K_ID));
        //*********TYPE_SOUND_ALARM
        list_sounds[TYPE_SOUND_ALARM][K01_ALARM].req_play_sound = (pwm_enable_e)(msg_grpk->K01 == 1);
        list_sounds[TYPE_SOUND_ALARM][K32_ALARM].req_play_sound = (pwm_enable_e)(msg_grpk->K32 == 1);
        list_sounds[TYPE_SOUND_ALARM][K34_ALARM].req_play_sound = (pwm_enable_e)(msg_grpk->K34 == 2);
        list_sounds[TYPE_SOUND_ALARM][K35_ALARM].req_play_sound = (pwm_enable_e)(msg_grpk->K35 == 2);
        //*********TYPE_SOUND_WARNING
        list_sounds[TYPE_SOUND_WARNING][K28_WARNING].req_play_sound = (pwm_enable_e)(msg_grpk->K28 == 1);
        list_sounds[TYPE_SOUND_WARNING][K35_WARNING].req_play_sound = (pwm_enable_e)(msg_grpk->K35 == 1);
    }

    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_M_ID)->is_updated())
    {
        msg_grpm = reinterpret_cast<TT_GRP_M_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_M_ID));
        list_sounds[TYPE_SOUND_ALARM][M01_ALARM].req_play_sound = (pwm_enable_e)(msg_grpm->M01 == 1);
    }
    if (m_ptr_cached_msgs->get_ptr_to_msg(HMIHANDLER_TT_GRP_P_ID)->is_updated())
    {
        msg_grpp = reinterpret_cast<TT_GRP_P_t*>(m_ptr_cached_msgs->get_data_from_msg(HMIHANDLER_TT_GRP_P_ID));
        //*********TYPE_SOUND_ALARM
        list_sounds[TYPE_SOUND_ALARM][P08_ALARM].req_play_sound = (pwm_enable_e)(msg_grpp->P08 == 1);
    }
    CATCH_BLOCK
}


