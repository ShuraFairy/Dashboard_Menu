#ifndef LOGGER_H
#define LOGGER_H

// C++ Header File(s)
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "./exception_define.h"

#ifdef WIN32
// Win Socket Header File(s)
#include <Windows.h>
#include <process.h>
#else
// POSIX Socket Header File(s)
#include <errno.h>
#include <pthread.h>
#endif

namespace CPlusPlusLogging {
// Direct Interface for logging into log file or console using MACRO(s)
#define LOG_ERROR(x) Logger::get_instance()->verbose_error(x)
#define LOG_ALARM(x) Logger::get_instance()->verbose_alarm(x)
#define LOG_ALWAYS(x) Logger::get_instance()->verbose_always(x)
#define LOG_INFO(x) Logger::get_instance()->verbose_info(x)
#define LOG_BUFFER(x) Logger::get_instance()->verbose_buffer(x)
#define LOG_TRACE(x) Logger::get_instance()->verbose_trace(x)
#define LOG_DEBUG(x) Logger::get_instance()->verbose_debug(x)

// enum for LOG_LEVEL
typedef enum {
    LOG_LEVEL_DISABLE_LOG = 1,
    LOG_LEVEL_INFO = 2,
    LOG_LEVEL_BUFFER = 3,
    LOG_LEVEL_TRACE = 4,
    LOG_LEVEL_DEBUG = 5,
    LOG_LEVEL_ENABLE_LOG = 6,
} LogLevel;

// enum for LOG_TYPE
typedef enum {
    LOG_TYPE_NO_LOG = 1,
    LOG_TYPE_CONSOLE = 2,
    LOG_TYPE_FILE_LOG = 3,
} LogType;

class Logger {
public:
    static Logger* get_instance() throw();

    // Interface for Error Log
    void verbose_error(const char* text) throw();
    void verbose_error(std::string& text) throw();
    void verbose_error(std::ostringstream& stream) throw();

    // Interface for Alarm Log
    void verbose_alarm(const char* text) throw();
    void verbose_alarm(std::string& text) throw();
    void verbose_alarm(std::ostringstream& stream) throw();

    // Interface for Always Log
    void verbose_always(const char* text) throw();
    void verbose_always(std::string& text) throw();
    void verbose_always(std::ostringstream& stream) throw();

    // Interface for Buffer Log
    void verbose_buffer(const char* text) throw();
    void verbose_buffer(std::string& text) throw();
    void verbose_buffer(std::ostringstream& stream) throw();

    // Interface for Info Log
    void verbose_info(const char* text) throw();
    void verbose_info(std::string& text) throw();
    void verbose_info(std::ostringstream& stream) throw();

    // Interface for Trace log
    void verbose_trace(const char* text) throw();
    void verbose_trace(std::string& text) throw();
    void verbose_trace(std::ostringstream& stream) throw();

    // Interface for Debug log
    void verbose_debug(const char* text) throw();
    void verbose_debug(std::string& text) throw();
    void verbose_debug(std::ostringstream& stream) throw();

    // Error and Alarm log must be always enable
    // Hence, there is no interfce to control error and alarm logs

    // Interfaces to control log levels
    void update_log_level(LogLevel log_level);
    void enable_log(); // Enable all log levels
    void disable_log(); // Disable all log levels, except error and alarm

    // Interfaces to control log Types
    void update_log_type(LogType log_type);
    void enable_console_logging();
    void enable_file_logging();

protected:
    Logger();
    ~Logger();

    // Wrapper function for lock/unlock
    // For Extensible feature, lock and unlock should be in protected
    void lock();
    void unlock();

    std::string get_current_time();

private:
    void log_into_file(std::string& data);
    void log_on_console(std::string& data);
    // Logger(const Logger& obj) {}
    // void operator=(const Logger& obj) {}

private:
    static Logger* _instance;
    std::ofstream _file;

#ifdef WIN32
    CRITICAL_SECTION _mutex;
#else
    pthread_mutexattr_t _attr;
    pthread_mutex_t _mutex;
#endif

    LogLevel _log_level;
    LogType _log_type;
};

} // End of namespace

#endif // LOGGER_H
