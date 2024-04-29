#ifndef PLAYLISTFACTORY_H
#define PLAYLISTFACTORY_H

#include "./playlisthandlerwav.h"
#include "./soundplaylist.h"
#include "./Logger/exception_define.h"

class Playlistfactory{
public:
    //передаем сообщение об ошибке и получаем instance объекта
    static IPlaylist* get_playlist();
private:
    //если есть звуковая карта - true, если нет - false
    static bool check_devices();
};

#endif // PLAYLISTFACTORY_H
