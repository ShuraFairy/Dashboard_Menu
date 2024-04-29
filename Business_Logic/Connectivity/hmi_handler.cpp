#include "hmi_handler.h"
#include <QDebug>

std::shared_ptr<HmiHandler> HmiHandler::m_ptr_instance = nullptr;
std::mutex HmiHandler::m_build_mutex;

//--------------------HmiHandler methods-------------------------------------
HmiHandler::HmiHandler()
{
    m_ptr_notifer = subscribe_notifer::get_instance();
    can_msg_rx_init();
}

HmiHandler::~HmiHandler()
{

}

HmiHandler* HmiHandler::getInstance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        std::lock_guard<std::mutex> lock_build(m_build_mutex);
        m_ptr_instance = shared_ptr<HmiHandler>(new HmiHandler);
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

void HmiHandler::add_new_data(uint32_t _id, can_msg_state_e _msg_state,  uint64_t _data)
{
    TRY_BLOCK
    if (map_can_msg_rx.find(_id) != map_can_msg_rx.end())
    {
        if((map_can_msg_rx[_id].add_new_data_to_buff(_msg_state, _data)) || ((_id == HMIHANDLER_AUXIO4_75_ID) && (_data != 0x000003FFFF000000)))
            m_ptr_notifer->update_mark(_id, &map_can_msg_rx.find(_id)->second);
    }
    CATCH_BLOCK
}

void HmiHandler::can_msg_rx_init()
{
    TRY_BLOCK
    map_can_msg_rx.reserve(g_CAN_msg_ids.size());
    for (auto& iterator : g_CAN_msg_ids)
        map_can_msg_rx.insert_or_assign(iterator.first, can_msg_rx_t(iterator.first, iterator.second));
    CATCH_BLOCK
}

void* HmiHandler::get_data_from_msg(uint32_t _message_id)
{
    TRY_BLOCK
    return map_can_msg_rx[_message_id].get_data();
    CATCH_BLOCK
}

can_msg_rx_t* HmiHandler::get_ptr_to_msg(uint32_t _message_id)
{
    TRY_BLOCK
    return (likely(map_can_msg_rx.find(_message_id) != map_can_msg_rx.end())) ?
        &(map_can_msg_rx.find(_message_id)->second) : nullptr;
    CATCH_BLOCK
}
