#include "hmi_config.h"

//--------------------can_msg_rx_t methods-------------------------------------
can_msg_rx_t::can_msg_rx_t(uint32_t _message_id, uint32_t _timeout)
    : m_ptr_actuall_data()
    , msg_state(CAN_MESSAGE_STATE_NOT_RECEIVED)
    , receive_time_buff()
    , has_new_data(false)
    , id(_message_id)
    , data_size (CAN_MSG_DATA_SIZE)
    , cycle_time_ms(_timeout)
{
}

can_msg_rx_t::can_msg_rx_t()
{
}

bool can_msg_rx_t::add_new_data_to_buff(can_msg_state_e _msg_state,  uint64_t data)
{
    TRY_BLOCK
    bool is_changed = false;
    is_changed = (msg_state != _msg_state && _msg_state == CAN_MESSAGE_STATE_OK);
    scoped_lock state_lock(m_state_locker);
    msg_state = _msg_state;
    if (msg_state == CAN_MESSAGE_STATE_OK)
    {
        if(m_ptr_actuall_data != data)
        {
            m_ptr_actuall_data = data;
            is_changed = true;
            has_new_data = true;
        }
    }
    receive_time_buff = chrono::steady_clock::now();
    return is_changed;
    CATCH_BLOCK
}

can_msg_state_e can_msg_rx_t::check_state()
{
    TRY_BLOCK
    using namespace std::chrono;
    if (steady_clock::now() >= receive_time_buff + milliseconds(cycle_time_ms))
    {
        scoped_lock state_lock(m_state_locker);
        msg_state = CAN_MESSAGE_STATE_TIMEOUT;
        has_new_data = false;
    }

    return msg_state;
    CATCH_BLOCK
}
