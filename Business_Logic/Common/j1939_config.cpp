#include "j1939_config.h"

DM1_full_handler_t::DM1_full_handler_t(uint32_t _can_id, uint32_t _message_id)
    : frame_count()
    , no_of_frames_total()
    , index_iterator()
    , msg_data()
    , j1939_raw_data()
    , msg_state(CAN_MESSAGE_STATE_NOT_RECEIVED)
    , receive_time_buff()
    , has_new_data(false)
    , can_id(_can_id)
    , message_id(_message_id)
{
}

DM1_full_handler_t::DM1_full_handler_t()
{
}

void DM1_full_handler_t::init_dm1_array(dm_fault_data* dm_type)
{
    TRY_BLOCK
    dm_type->amber_warning_lamp_status = 0;
    dm_type->protect_lamp_status = 0;
    dm_type->amber_warning_lamp_status = 0;
    dm_type->red_stop_lamp_state = 0;
    dm_type->malfunction_indicator_lamp_status = 0;
    dm_type->flash_protect_lamp = 0;
    dm_type->flash_amber_warning_lamp = 0;
    dm_type->flash_red_stop_lamp = 0;
    dm_type->flash_malfunction_indicator_lamp = 0;

    for (int i = 0; i < 5; ++i) {
        dm_type->dtc_data[i].source_message = "NA";
        dm_type->dtc_data[i].SPN_no = 0;
        dm_type->dtc_data[i].FMI_no = 0;
        dm_type->dtc_data[i].recommendations = "Please Contact Service Center";
        dm_type->dtc_data[i].no_of_repetations = 0;
    }
    CATCH_BLOCK
}

void DM1_full_handler_t::update_dm1_data(DM1_data_t dm1_data, string source_name)
{
    TRY_BLOCK
    this->msg_data.protect_lamp_status = dm1_data.protect_lamp_status;
    this->msg_data.amber_warning_lamp_status = dm1_data.amber_warning_lamp_status;
    this->msg_data.red_stop_lamp_state = dm1_data.red_stop_lamp_state;
    this->msg_data.malfunction_indicator_lamp_status = dm1_data.malfunction_indicator_lamp_status;
    this->msg_data.flash_protect_lamp = dm1_data.flash_protect_lamp;
    this->msg_data.flash_amber_warning_lamp = dm1_data.flash_amber_warning_lamp;
    this->msg_data.flash_red_stop_lamp = dm1_data.flash_red_stop_lamp;
    this->msg_data.flash_malfunction_indicator_lamp = dm1_data.flash_malfunction_indicator_lamp;
    this->update_dm1_dtc_data(dm1_data.dtc1, 0, source_name);
    this->update_dm1_dtc_data(dm1_data.dtc2, 1, source_name);
    this->update_dm1_dtc_data(dm1_data.dtc3, 2, source_name);
    this->update_dm1_dtc_data(dm1_data.dtc4, 3, source_name);
    this->update_dm1_dtc_data(dm1_data.dtc5, 4, source_name);
    CATCH_BLOCK
}

void DM1_full_handler_t::update_dm1_dtc_data(uint32_t dtc_data, uint8_t dtc_type, string source_name)
{
    TRY_BLOCK
    uint32_t spn_bit_mask;
    uint32_t fmi_bit_mask;
    uint32_t no_of_repetations_mask;
    spn_bit_mask = (1 << 19) - 1;
    this->msg_data.dtc_data[dtc_type].SPN_no = (dtc_data & spn_bit_mask);
    fmi_bit_mask = (1 << 6) - 1;
    this->msg_data.dtc_data[dtc_type].FMI_no = ((dtc_data >> 19) & fmi_bit_mask);
    this->msg_data.dtc_data[dtc_type].source_message = source_name;
    no_of_repetations_mask = (1 << 8) - 1;
    this->msg_data.dtc_data[dtc_type].no_of_repetations = ((dtc_data >> 26) & no_of_repetations_mask);
    CATCH_BLOCK
}

can_msg_state_e DM1_full_handler_t::check_state()
{
    TRY_BLOCK
    using namespace std::chrono;
    //GAG
    uint32_t cycle_time_ms = 0;
    //GAG
    if (steady_clock::now() >= receive_time_buff + milliseconds(cycle_time_ms))
    {
        scoped_lock state_lock(m_state_locker);
        msg_state = CAN_MESSAGE_STATE_TIMEOUT;
        has_new_data = false;
    }
    return msg_state;
    CATCH_BLOCK
}
//GAG
//bool DM1_full_handler_t::add_new_data_to_buff(can_msg_state_e _msg_state,  uint64_t data)
//{
//    TRY_BLOCK
//    bool is_changed = false;
//    is_changed = (msg_state != _msg_state && _msg_state == CAN_MESSAGE_STATE_OK);
//    scoped_lock state_lock(m_state_locker);
//    msg_state = _msg_state;
//    if (msg_state == CAN_MESSAGE_STATE_OK)
//    {
//        if(m_ptr_actuall_data != data)
//        {
//            m_ptr_actuall_data = data;
//            is_changed = true;
//            has_new_data = true;
//        }
//    }
//    receive_time_buff = chrono::steady_clock::now();
//    return is_changed;
//    CATCH_BLOCK
//}
//GAG
