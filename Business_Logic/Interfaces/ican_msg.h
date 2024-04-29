#ifndef ICAN_MSG_H
#define ICAN_MSG_H

#include "../Common/apptypes.h"

//interface class for can messages
class can_msg_interface{
public:
    can_msg_interface() = default;
    virtual ~can_msg_interface() = default;
    virtual can_msg_state_e check_state() = 0;
    virtual can_msg_state_e get_state() = 0;
};

#endif // ICAN_MSG_H
