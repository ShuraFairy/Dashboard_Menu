#include "playlistfactory.h"

std::string exec(const char* cmd) {
    TRY_BLOCK
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
    CATCH_BLOCK
}

IPlaylist* Playlistfactory::get_playlist(){
   TRY_BLOCK
   IPlaylist* playlist = nullptr;
    //если ошибки нет - PlaylistHandlerWav(), если ошибка - SoundPlaylist()
   return (check_devices()) ? playlist = PlaylistHandlerWav::getInstance() : playlist = SoundPlaylist::getInstance();
   CATCH_BLOCK
}

bool Playlistfactory::check_devices(){
    TRY_BLOCK
    std::string soundcard_list = exec("aplay -l");
    return (soundcard_list.empty()) ? false : true;
    CATCH_BLOCK
}
