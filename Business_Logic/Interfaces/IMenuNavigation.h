#ifndef IMENUNAVIGATION_H
#define IMENUNAVIGATION_H

enum eDirrection
{
    E_D_UP = 0,
    E_D_DOWN,
    E_D_LEFT,
    E_D_RIGHT
};

class IMenuNavigation
{
public:
    IMenuNavigation() = default;
    virtual ~IMenuNavigation() = default;

    virtual void change_level(bool) = 0;
    virtual void change_focus_item(eDirrection) = 0;
};

#endif // IMENUNAVIGATION_H
