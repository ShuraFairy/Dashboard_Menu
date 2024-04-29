#ifndef IPLAYLIST_H
#define IPLAYLIST_H

#include <QObject>

class IPlaylist: public QObject{
    Q_OBJECT
public:
    IPlaylist() = default;
    virtual ~IPlaylist() = default;
    virtual void run_playlist() = 0;
private:
    virtual void init_playlist() = 0;
};

#endif // IPLAYLIST_H
