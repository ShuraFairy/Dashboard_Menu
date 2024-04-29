#ifndef SUBSCRIBE_NOTIFER_H
#define SUBSCRIBE_NOTIFER_H
#include "Interfaces/ISubscriber.h"
#include "Common/hmi_config.h"
#include "QDebug"
#include <unordered_map>
#include <memory>
#include <mutex>
#include <queue>
#include <list>
#include <thread>
#include "QGuiApplication"
#include "./Logger/exception_define.h"

using namespace std;

class subscribe_notifer
{
public:
    subscribe_notifer();
    static subscribe_notifer* get_instance();
    ~subscribe_notifer() = default;
    void operator()()
    {
        this_thread::sleep_for(5s);
        subscribe_notifer* instance = subscribe_notifer::get_instance();
        while (!is_exit)
        {
            for (auto& it : instance->m_updates)
            {
                if (it.second.second)
                {
                    auto update_status = send_update(it.first);
                    scoped_lock update_lock(m_build_mutex);
                    it.second.second = !update_status;
                }
                else if (it.second.first->get_state() == CAN_MESSAGE_STATE_OK)
                {
                    if (it.second.first->check_state() == CAN_MESSAGE_STATE_TIMEOUT)
                    {
                        scoped_lock update_lock(m_build_mutex);
                        it.second.second = true;
                    }
                }
            }
            this_thread::sleep_for(chrono::milliseconds(50));
        }
    };
    void update_mark(uint32_t _id, can_msg_interface* _ptr);
    bool subscribe(uint32_t, ISubscriber*);
    void send_thread_exit(){is_exit = true;};

private:
    bool send_update(uint32_t);

    static shared_ptr<subscribe_notifer> m_ptr_instance;
    static mutex m_build_mutex;

    unordered_map<uint32_t, list<ISubscriber*>> m_subscribers;
    unordered_map<uint32_t, pair<can_msg_interface*, bool>> m_updates;
    bool is_exit;
};

#endif // SUBSCRIBE_NOTIFER_H
