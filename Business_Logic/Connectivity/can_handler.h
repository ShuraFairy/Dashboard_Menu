#ifndef CAN_HANDLER_H
#define CAN_HANDLER_H

#include "j1939_data_handler.h"
#include "hmi_handler.h"
#include <QDateTime>
#include <QDebug>
#include <QtCore>
#include <cstdint>
#include <linux/can.h>
#include <linux/can/error.h>
#include <linux/if.h>
#include <linux/can/raw.h>
#include <chrono>
#include <condition_variable>
#include <exception>
#include <iostream>
#include <pthread.h>
#include <map>
#include <mutex>
//#include <net/if.h>
#include <pthread.h>
#include <queue>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include "../Logger/exception_define.h"



using namespace std;
void can_write_data();

class CanDataHandler : public QThread{
    friend void* can_read_thread_function(void*);
    friend void* process_can_data_function(void*);
public:

    typedef struct {
        uint32_t can_id;
        uint8_t can_data[8];

    } UDSDetails;
    ~CanDataHandler();
    int can_init();
    static CanDataHandler* getInstance();
    /* Qthread Function */
    //    void run();
    inline void* get_msg_from_cache(uint32_t _message_id){return m_ptr_msg_holder->get_ptr_to_msg(_message_id);};

    int* can_fd_get();
    bool send_can_msg(can_frame);

    UDSDetails* get_uds_can_response();
    int m_can_fd;
    shared_ptr<QSocketNotifier> m_ptr_notifer;
    bool exit_status(){return is_exit;};

private:
    CanDataHandler();
    //struct can_frame _frame_rx;
    void update_filter_can_messages_array();
    //QmlState _state;
    static mutex m_build_mutex;
    static shared_ptr<CanDataHandler> m_ptr_instance;

    bool is_exit;
    mutex m_queue_access_mutex; // Only if 2+ threads reading from queue
    HmiHandler* m_ptr_msg_holder;
    J1939DataHandler* m_ptr_dm_data_holder;
    can_filter m_filter_can_messages[TOTAL_CAN_IDS];
};

#endif // CAN_HANDLER_H

