#include "j1939_data_handler.h"

#define DM1_00_SOURCE "00"
#define DM1_03_SOURCE "03"
#define DM1_0B_SOURCE "0B"
#define DM1_12_SOURCE "12"
#define DM1_2F_SOURCE "2F"
#define DM1_33_SOURCE "33"
#define DM1_EE_SOURCE "EE"
#define DM1_FC_SOURCE "FC"

std::shared_ptr<J1939DataHandler> J1939DataHandler::m_ptr_instance = nullptr;
mutex J1939DataHandler::m_build_mutex;

J1939DataHandler::J1939DataHandler()
{
    m_ptr_notifer = subscribe_notifer::get_instance();
    can_msg_j1939_init();
}

J1939DataHandler::~J1939DataHandler()
{
}

void J1939DataHandler::can_msg_j1939_init()
{
    TRY_BLOCK
//      m_dtc_cached_data.reserve(g_DM1_pairs.size());
      for (auto& iterator: g_DM1_pairs)
          m_dtc_cached_data[iterator.second] = DM1_full_handler_t(iterator.first, iterator.second);

    CATCH_BLOCK
}

J1939DataHandler* J1939DataHandler::getInstance()
{
    TRY_BLOCK
    if(!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = shared_ptr<J1939DataHandler>(new J1939DataHandler);
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

dm_fault_data* J1939DataHandler::handle_dm1_get(uint32_t _can_id)
{
    TRY_BLOCK
    return (m_dtc_cached_data.find(_can_id) != m_dtc_cached_data.end()) ?
    &m_dtc_cached_data[_can_id].msg_data : nullptr;
    CATCH_BLOCK
}

void J1939DataHandler::update_dm1_details(uint32_t can_id)
{
    TRY_BLOCK
    auto ptr_msg = m_dtc_cached_data.find(can_id);
    string str_source;
    switch (can_id) {
    case HMIHANDLER_DM1_00_ID:
        str_source = DM1_00_SOURCE;
        break;
    case HMIHANDLER_DM1_03_ID:
        str_source = DM1_03_SOURCE;
        break;
    case HMIHANDLER_DM1_0B_ID:
        str_source = DM1_0B_SOURCE;
        break;
    case HMIHANDLER_DM1_2F_ID:
        str_source = DM1_2F_SOURCE;
        break;
    case HMIHANDLER_DM1_EE_ID:
        str_source = DM1_EE_SOURCE;
        break;
    case HMIHANDLER_DM1_33_ID:
        str_source = DM1_33_SOURCE;
        break;
    default:
        str_source = "";
        break;
    }
    if (ptr_msg != m_dtc_cached_data.end())
    {
        ptr_msg->second.init_dm1_array(&ptr_msg->second.msg_data);
        ptr_msg->second.update_dm1_data(*((DM1_data_t*)(ptr_msg->second.j1939_raw_data)), str_source);
    }
    CATCH_BLOCK
}


void J1939DataHandler::set_total_frames(uint32_t _can_id, uint8_t _total_frames)
{
    TRY_BLOCK
    m_dtc_cached_data[_can_id].no_of_frames_total = _total_frames;
    m_dtc_cached_data[_can_id].frame_count = 0;
    m_dtc_cached_data[_can_id].index_iterator = 0;
    CATCH_BLOCK
}

void* J1939DataHandler::get_data_from_msg(uint32_t _can_id)
{
    TRY_BLOCK
    return m_dtc_cached_data[_can_id].get_data();
    CATCH_BLOCK
}

DM1_full_handler_t* J1939DataHandler::get_ptr_to_msg(uint32_t _frame_id)
{
    TRY_BLOCK
    return (likely(m_dtc_cached_data.find(_frame_id) != m_dtc_cached_data.end())) ?
        &(m_dtc_cached_data.find(_frame_id)->second) : nullptr;
    CATCH_BLOCK
}

//GAG
void J1939DataHandler::add_new_data(uint32_t _can_id, can_msg_state_e _msg_state,  uint64_t _data)
{
//    TRY_BLOCK
//    if (m_dtc_m_id.find(_can_id) != m_dtc_m_id.end())
//    {
//        uint32_t message_id = m_dtc_m_id.find(_can_id)->second;
//        if((m_dtc_cached_data[message_id].add_new_data_to_buff(_msg_state, _data)) || ((message_id == HMIHANDLER_AUXIO4_75_ID) && (_data != 0x000003FFFF000000)))
//            m_ptr_notifer->update_mark(message_id, &m_dtc_cached_data.find(message_id)->second);
//    }
//    CATCH_BLOCK
}
