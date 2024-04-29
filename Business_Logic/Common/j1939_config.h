#ifndef J1939_CONFIG_H
#define J1939_CONFIG_H

#include <stdint.h>
#include <optional>
#include <string>
#include <mutex>
#include <memory>

#define J1939_RAW_DATA_SIZE 28

#include "../Logger/exception_define.h"
#include "../Interfaces/ican_msg.h"

typedef struct
{
    string source_message; //с какого ECU пришло это сообщение
    uint32_t SPN_no;  //место возникновения ошибки
    uint8_t FMI_no;  // идентификатор ошибки
    string recommendations; //Если SPN_conversion_method = 1, это означает, что коды неисправностей диагностики выравниваются с использованием более нового метода преобразования. Если SPN_conversion_method = 0, это означает, что используется один из трех методов преобразования диагностических кодов неисправностей, и производитель ЭБУ должен знать, какой из трех методов используется.
    uint8_t no_of_repetations; //количество раз, которое возникала ошибка (max 126)
} DtcData;

typedef struct {
    uint8_t protect_lamp_status;
    uint8_t amber_warning_lamp_status;
    uint8_t red_stop_lamp_state;
    uint8_t malfunction_indicator_lamp_status;
    uint8_t flash_protect_lamp;
    uint8_t flash_amber_warning_lamp;
    uint8_t flash_red_stop_lamp;
    uint8_t flash_malfunction_indicator_lamp;
    DtcData dtc_data[5];
} dm_fault_data;


class DM1_full_handler_t: public can_msg_interface{
public:
    uint8_t frame_count;
    uint8_t no_of_frames_total;
    uint8_t index_iterator;
    dm_fault_data msg_data;
    uint8_t j1939_raw_data[J1939_RAW_DATA_SIZE];

    DM1_full_handler_t(uint32_t, uint32_t);
    DM1_full_handler_t();
    DM1_full_handler_t(const DM1_full_handler_t& _copy)
        : frame_count(_copy.frame_count)
        , no_of_frames_total(_copy.no_of_frames_total)
        , index_iterator(_copy.index_iterator)
        , msg_data(_copy.msg_data)
        , msg_state(_copy.msg_state)
        , receive_time_buff(_copy.receive_time_buff)
        , has_new_data(_copy.has_new_data)
        , can_id(_copy.can_id)
        , message_id(_copy.message_id)
        , m_ptr_actuall_data(_copy.m_ptr_actuall_data)
    {
         for (uint8_t i = 0; i < J1939_RAW_DATA_SIZE; ++i)
            j1939_raw_data[i] = _copy.j1939_raw_data[i];
    }

    DM1_full_handler_t& operator=(const DM1_full_handler_t& _copy)
    {
        frame_count = _copy.frame_count;
        no_of_frames_total = _copy.no_of_frames_total;
        index_iterator = _copy.index_iterator;
        msg_data = _copy.msg_data;
        msg_state = _copy.msg_state;
        receive_time_buff = _copy.receive_time_buff;
        has_new_data = _copy.has_new_data;
        can_id = _copy.can_id;
        message_id = _copy.message_id;
        m_ptr_actuall_data = _copy.m_ptr_actuall_data;

        for (uint8_t i = 0; i < J1939_RAW_DATA_SIZE; ++i)
            j1939_raw_data[i] = _copy.j1939_raw_data[i];

        return *this;
    }

    //bool add_new_data_to_buff(can_msg_state_e, uint64_t);
    void init_dm1_array(dm_fault_data* dm_type);
    void update_dm1_dtc_data(uint32_t dtc_data, uint8_t dtc_type, string source_name);
    void update_dm1_data(DM1_data_t dm1_data, string source_name);

    inline bool is_updated(){ return has_new_data; };
    inline void update_state(){ has_new_data = false; };

    virtual can_msg_state_e check_state() override;
    virtual can_msg_state_e get_state() override {return msg_state;};

    //узнать адрес начала сообщения
    inline uint64_t* get_data(){ return &m_ptr_actuall_data; };

private:

    can_msg_state_e msg_state;//Состояние сообщения для приложения
    chrono::time_point<chrono::steady_clock> receive_time_buff;//Время, когда сообщение было получено последний раз
    bool has_new_data;//Есть новые данные для
    uint32_t can_id; //id, в котором хранится количество can фреймов
    uint32_t message_id; //id сообщения

    mutex m_state_locker;
    uint64_t m_ptr_actuall_data;//Это указатель на актуальные данные CAN-сообщения.
};

#endif // J1939_CONFIG_H
