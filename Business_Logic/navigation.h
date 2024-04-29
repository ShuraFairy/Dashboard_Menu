#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Qt_Framework/qtpopup.h"
#include "Common/menu_items.h"
#include "Interfaces/IMenuNavigation.h"
#include "subscribe_notifer.h"

#define BUTTON_REPEAT 2

typedef struct
{
    bool button_right   :1;
    bool button_left    :1;
    bool button_back    :1;
    bool button_ok      :1;
    bool button_up      :1;
    bool button_down    :1;
} ButtonOps;

class navigation : public ISubscriber
{
public:
    navigation(IMenuNavigation*);
    static navigation* get_instance(IMenuNavigation*);
    bool update_info(uint32_t) override;
    void set_popup(QtPopUpWindow* _popup) { m_ptr_popup = _popup; };

private:
    void init_subscribe() override;
    static mutex m_build_mutex;
    static navigation* m_ptr_instance;
    ButtonOps m_cached_state;
    QtPopUpWindow* m_ptr_popup;
    IMenuNavigation* m_ptr_menu;
    HmiHandler* m_ptr_msgs_handler;
    uint8_t button_repeat_msg;
};

#endif // NAVIGATION_H
