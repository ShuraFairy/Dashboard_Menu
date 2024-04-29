#ifndef IMENUDRAWER_H
#define IMENUDRAWER_H

class IMenuDrawer
{
public:
    IMenuDrawer()=default;
    virtual ~IMenuDrawer()=default;
    virtual void set_language()=0;
    virtual void set_values(bool)=0;
    virtual void set_new_focus(int, int, int)=0;
    virtual bool set_new_screen(int)=0;
};

#endif // IMENUDRAWER_H
