#include "navigation.h"
#include "Business_Logic/Common/menu_defines.h"

mutex navigation::m_build_mutex;
navigation* navigation::m_ptr_instance = nullptr;
navigation::navigation(IMenuNavigation* _menu)
    : m_cached_state()
    , m_ptr_menu(_menu)
    , button_repeat_msg(0)
{
    m_ptr_msgs_handler = HmiHandler::getInstance();
    init_subscribe();
}

navigation* navigation::get_instance(IMenuNavigation* _menu)
{
    TRY_BLOCK
        if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
            m_ptr_instance = new navigation(_menu);
    }
    return m_ptr_instance;
    CATCH_BLOCK
}

bool navigation::update_info(uint32_t _id)
{
    TRY_BLOCK
    if (_id == HMIHANDLER_AUXIO4_75_ID)
    {
        if (m_ptr_msgs_handler->get_ptr_to_msg(HMIHANDLER_AUXIO4_75_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
            AUXIO4_75_t* button_data = reinterpret_cast<AUXIO4_75_t*>(m_ptr_msgs_handler->get_data_from_msg(HMIHANDLER_AUXIO4_75_ID));
            if (!m_cached_state.button_ok && button_data->auxi_O92_button05_ok_state)
            {
                if (!(m_ptr_popup->update_popup_close()))
                    m_ptr_menu->change_level(true);
            }
            else if (button_data->auxi_O85_button03_up_state && !m_ptr_popup->get_state_popup())
            {
                if (m_cached_state.button_up)
                {
                    if (button_repeat_msg < BUTTON_REPEAT)
                        button_repeat_msg++;
                    else
                    {
                        button_repeat_msg = 0;
                        m_ptr_menu->change_focus_item(E_D_UP);
                    }
                }
                else
                {
                    button_repeat_msg = 0;
                    m_ptr_menu->change_focus_item(E_D_UP);
                }
            }
            else if (!m_cached_state.button_back && button_data->auxi_O86_button01_back_state && !m_ptr_popup->get_state_popup())
            {
                m_ptr_menu->change_level(false);
            }
            else if (button_data->auxi_O91_button04_down_state && !m_ptr_popup->get_state_popup())
            {
                if (m_cached_state.button_down)
                {
                    if (button_repeat_msg < BUTTON_REPEAT)
                        button_repeat_msg++;
                    else
                    {
                        button_repeat_msg = 0;
                        m_ptr_menu->change_focus_item(E_D_DOWN);
                    }
                }
                else
                {
                    button_repeat_msg = 0;
                    m_ptr_menu->change_focus_item(E_D_DOWN);
                }
            }
            else if (button_data->auxi_O88_button06_right_state && !m_ptr_popup->get_state_popup())
            {
                if (m_cached_state.button_right)
                {
                    if (button_repeat_msg < BUTTON_REPEAT)
                        button_repeat_msg++;
                    else
                    {
                        button_repeat_msg = 0;
                        m_ptr_menu->change_focus_item(E_D_RIGHT);
                    }
                }
                else
                {
                    button_repeat_msg = 0;
                    m_ptr_menu->change_focus_item(E_D_RIGHT);
                }
            }
            else if (button_data->auxi_O87_button02_left_state && !m_ptr_popup->get_state_popup())
            {
                if (m_cached_state.button_left)
                {
                    if (button_repeat_msg < BUTTON_REPEAT)
                        button_repeat_msg++;
                    else
                    {
                        button_repeat_msg = 0;
                        m_ptr_menu->change_focus_item(E_D_LEFT);
                    }
                }
                else
                {
                    button_repeat_msg = 0;
                    m_ptr_menu->change_focus_item(E_D_LEFT);
                }
            }
            m_cached_state.button_back = (button_data->auxi_O86_button01_back_state == 1);
            m_cached_state.button_down = (button_data->auxi_O91_button04_down_state == 1);
            m_cached_state.button_left = (button_data->auxi_O87_button02_left_state == 1);
            m_cached_state.button_ok = (button_data->auxi_O92_button05_ok_state == 1);
            m_cached_state.button_right = (button_data->auxi_O88_button06_right_state == 1);
            m_cached_state.button_up = (button_data->auxi_O85_button03_up_state);
        }
    }
    return true;
    CATCH_BLOCK
}


void navigation::init_subscribe()
{
    TRY_BLOCK
    auto ptr_notifier = subscribe_notifer::get_instance();
    ptr_notifier->subscribe(HMIHANDLER_AUXIO4_75_ID, this);
    CATCH_BLOCK
}
