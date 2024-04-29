#ifndef HMI_HANDLER_H
#define HMI_HANDLER_H

#include "../Common/hmi_config.h"
#include "../subscribe_notifer.h"
#include "../Logger/exception_define.h"
#include <QMutex>
#include <QMutexLocker>

using namespace std;

class HmiHandler
{
public:
    ~HmiHandler();

    static HmiHandler* getInstance();
    void add_new_data(uint32_t, can_msg_state_e,  uint64_t);
    void* get_data_from_msg(uint32_t);
    can_msg_rx_t* get_ptr_to_msg(uint32_t);

private:
    HmiHandler();
    void can_msg_rx_init();

    static std::mutex m_build_mutex;
    static std::shared_ptr<HmiHandler> m_ptr_instance;
    subscribe_notifer* m_ptr_notifer;

    std::unordered_map<uint32_t, can_msg_rx_t> map_can_msg_rx;
};

#endif // HMI_HANDLER_H
