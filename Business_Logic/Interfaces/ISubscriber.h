#ifndef ISUBSCRIBER_H
#define ISUBSCRIBER_H
#include <cstdint>
#include <unordered_map>

class ISubscriber
{
public:
    ISubscriber() = default;
    virtual ~ISubscriber() = default;
    virtual void init_subscribe() = 0;
    virtual bool update_info(uint32_t _id) = 0;
};

#endif // ISUBSCRIBER_H
