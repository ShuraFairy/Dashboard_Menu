#pragma once
#ifndef HMI_CONFIG_H
#define HMI_CONFIG_H
#include "QString"
#include <stdint.h>
#include <string>
#include <optional>
#include <string>
#include <mutex>
#include <memory>

#define TD_DAY_FACTOR 0.25
#define TD_YEAR_OFFSET 1985
#define TD_HOURS_OFFSET -125
#define ENGINE_COOLANT_OFFSET -40
#define OFFSET_MINUS_40 -40
#define D1_CANID_TEMPSENSPASSENGERCOMPARTMENT_MAXIMUM 210
#define D1_CANID_TEMPSENSPASSENGERCOMPARTMENT_OFFSET -40
#define D1_CANID_TEMPSENSCABIN_MAXIMUM 210
#define D1_CANID_TEMPSENSCABIN_OFFSET -40
#define ETC2_CANID_CURRENT_GEAR_OFFSET -125
#define UPPER_LIMIT_VALID_SIGNAL_1_BYTE 250

#include "../Logger/exception_define.h"
#include "../Interfaces/ican_msg.h"

using namespace std;

class can_msg_rx_t: public can_msg_interface{
public:
    can_msg_rx_t(uint32_t, uint32_t);
    can_msg_rx_t();
    can_msg_rx_t(const can_msg_rx_t& _copy)
        : m_ptr_actuall_data(_copy.m_ptr_actuall_data)
        , msg_state(_copy.msg_state)
        , receive_time_buff(_copy.receive_time_buff)
        , has_new_data(_copy.has_new_data)
        , id(_copy.id)
        , data_size(_copy.data_size)
        , cycle_time_ms(_copy.cycle_time_ms)
    {
    }

    can_msg_rx_t& operator=(const can_msg_rx_t& _copy)
    {
        m_ptr_actuall_data = _copy.m_ptr_actuall_data;
        msg_state = _copy.msg_state;
        receive_time_buff = _copy.receive_time_buff;
        has_new_data = _copy.has_new_data;
        id = _copy.id;
        data_size = _copy.data_size;
        cycle_time_ms = _copy.cycle_time_ms;

        return *this;
    }

    bool add_new_data_to_buff(can_msg_state_e, uint64_t);
    inline bool is_updated(){ return has_new_data; };
    inline void update_state(){ has_new_data = false; };
    virtual can_msg_state_e check_state() override;
    virtual can_msg_state_e get_state() override {return msg_state;};
    inline uint64_t* get_data(){ return &m_ptr_actuall_data; };

private:
    uint64_t m_ptr_actuall_data;//Это указатель на актуальные данные CAN-сообщения.
    can_msg_state_e msg_state;//Состояние сообщения для приложения
    chrono::time_point<chrono::steady_clock> receive_time_buff;//Время, когда сообщение было получено последний раз
    bool has_new_data;//Есть новые данные для
    mutex m_state_locker;
    uint32_t id;
    uint8_t data_size;
    uint32_t cycle_time_ms;//Периодичность отправки сообщения. Эта переменная используется для расчета статуса сообщения
};

#endif
