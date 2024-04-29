#pragma once
#ifndef J1939DATAHANDLER_H
#define J1939DATAHANDLER_H

#include <cstdint>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <string>
#include "../Common/apptypes.h"
#include "../Logger/exception_define.h"
#include "../Common/j1939_config.h"
#include "../subscribe_notifer.h"

#define J1939_RAW_DATA_SIZE 28

using namespace std;
class J1939DataHandler {
public:
    ~J1939DataHandler();

    static J1939DataHandler* getInstance();
    void add_new_data(uint32_t, can_msg_state_e,  uint64_t);
    void* get_data_from_msg(uint32_t);
    DM1_full_handler_t* get_ptr_to_msg(uint32_t);

    void set_total_frames(uint32_t, uint8_t);
    dm_fault_data* handle_dm1_get(uint32_t);
    void update_dm1_details(uint32_t can_id);

private:
    J1939DataHandler();
    void can_msg_j1939_init();

    static mutex m_build_mutex;
    static shared_ptr<J1939DataHandler> m_ptr_instance;
    subscribe_notifer* m_ptr_notifer;

    unordered_map<uint32_t, DM1_full_handler_t> m_dtc_cached_data;
};

#endif // J1939DATAHANDLER_H
