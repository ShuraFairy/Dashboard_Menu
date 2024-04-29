#include "subscribe_notifer.h"

shared_ptr<subscribe_notifer> subscribe_notifer::m_ptr_instance(nullptr);
mutex subscribe_notifer::m_build_mutex;

subscribe_notifer::subscribe_notifer()
    :   m_subscribers()
    ,   m_updates()
    ,   is_exit(false)
{
}

subscribe_notifer* subscribe_notifer::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = make_shared<subscribe_notifer>();
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

bool subscribe_notifer::send_update(uint32_t _id)
{
    TRY_BLOCK
    if (m_subscribers.find(_id) != m_subscribers.end() && !m_subscribers[_id].empty())
    {
        bool return_value = true;
        for (auto& it : m_subscribers.find(_id)->second)
        {
            if(!it->update_info(_id))
                return_value = false;
        }
        return return_value;
    }
    return true;
    CATCH_BLOCK
}
void subscribe_notifer::update_mark(uint32_t _id, can_msg_interface* _ptr)
{
    TRY_BLOCK
    scoped_lock update_lock(m_build_mutex);
    m_updates.insert_or_assign(_id, make_pair(_ptr, true));
    CATCH_BLOCK
};

bool subscribe_notifer::subscribe(uint32_t _id, ISubscriber* _ptrsubscriber)
{
    TRY_BLOCK
    try
    {
        m_subscribers[_id].push_back(_ptrsubscriber);
        return true;
    }
    catch(...)
    {
        return false;
    }
    CATCH_BLOCK
}
