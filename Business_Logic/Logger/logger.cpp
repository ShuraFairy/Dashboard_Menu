#include <QDebug>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Code Specific Header Files(s)
#include "logger.h"

using namespace std;
using namespace CPlusPlusLogging;

Logger* Logger::_instance = 0;

// Log file name. File name should be change from here only
const string log_file_name = "MyLogFile.log";

Logger::Logger()
{
    _file.open(log_file_name.c_str(), ios::out | ios::app);
    _log_level = LOG_LEVEL_TRACE;
    _log_type = LOG_TYPE_FILE_LOG;

    // Initialize mutex
#ifdef WIN32
    InitializeCriticalSection(&_mutex);
#else
    int ret = 0;
    ret = pthread_mutexattr_settype(&_attr, PTHREAD_MUTEX_ERRORCHECK_NP);
    if (ret != 0) {
        qDebug() << "Logger::Logger() -- Mutex attribute not initialize!!" << Qt::endl;
        exit(0);
    }
    ret = pthread_mutex_init(&_mutex, &_attr);
    if (ret != 0) {
        qDebug() << "Logger::Logger() -- Mutex not initialize!!" << Qt::endl;
        exit(0);
    }
#endif
}

Logger::~Logger()
{
    _file.close();
#ifdef WIN32
    DeleteCriticalSection(&m_Mutex);
#else
    pthread_mutexattr_destroy(&_attr);
    pthread_mutex_destroy(&_mutex);
#endif
}

Logger* Logger::get_instance() throw()
{
    if (_instance == 0) {
        _instance = new Logger();
    }
    return _instance;
}

void Logger::lock()
{
    TRY_BLOCK
#ifdef WIN32
    EnterCriticalSection(&m_Mutex);
#else
    pthread_mutex_lock(&_mutex);
#endif
    CATCH_BLOCK
}

void Logger::unlock()
{
    TRY_BLOCK
#ifdef WIN32
    LeaveCriticalSection(&m_Mutex);
#else
    pthread_mutex_unlock(&_mutex);
#endif
    CATCH_BLOCK
}

void Logger::log_into_file(std::string& data)
{
    TRY_BLOCK
    lock();
    _file << get_current_time() << "  " << data << endl;
    unlock();
    CATCH_BLOCK
}

void Logger::log_on_console(std::string& data)
{
    TRY_BLOCK
    cout << get_current_time() << "  " << data << endl;
    CATCH_BLOCK
}

string Logger::get_current_time()
{
    TRY_BLOCK
    string curr_time;
    // Current date/time based on current time
    time_t now = time(0);
    // Convert current time to string
    curr_time.assign(ctime(&now));

    // Last charactor of currentTime is "\n", so remove it
    string current_time = curr_time.substr(0, curr_time.size() - 1);
    return current_time;
    CATCH_BLOCK
}

// Interface for Error Log
void Logger::verbose_error(const char* text) throw()
{
    string data;
    data.append("[ERROR]: ");
    data.append(text);

    // ERROR must be capture
    if (_log_type == LOG_TYPE_FILE_LOG) {
        log_into_file(data);
    } else if (_log_type == LOG_TYPE_CONSOLE) {
        log_on_console(data);
    }
}

void Logger::verbose_error(std::string& text) throw()
{
    verbose_error(text.data());
}

void Logger::verbose_error(std::ostringstream& stream) throw()
{
    string text = stream.str();
    verbose_error(text.data());
}

// Interface for Alarm Log
void Logger::verbose_alarm(const char* text) throw()
{
    string data;
    data.append("[ALARM]: ");
    data.append(text);

    // ALARM must be capture
    if (_log_type == LOG_TYPE_FILE_LOG) {
        log_into_file(data);
    } else if (_log_type == LOG_TYPE_CONSOLE) {
        log_on_console(data);
    }
}

void Logger::verbose_alarm(std::string& text) throw()
{
    verbose_alarm(text.data());
}

void Logger::verbose_alarm(std::ostringstream& stream) throw()
{
    string text = stream.str();
    verbose_alarm(text.data());
}

// Interface for Always Log
void Logger::verbose_always(const char* text) throw()
{
    string data;
    data.append("[ALWAYS]: ");
    data.append(text);

    // No check for ALWAYS logs
    if (_log_type == LOG_TYPE_FILE_LOG) {
        log_into_file(data);
    } else if (_log_type == LOG_TYPE_CONSOLE) {
        log_on_console(data);
    }
}

void Logger::verbose_always(std::string& text) throw()
{
    verbose_always(text.data());
}

void Logger::verbose_always(std::ostringstream& stream) throw()
{
    string text = stream.str();
    verbose_always(text.data());
}

// Interface for Buffer Log
void Logger::verbose_buffer(const char* text) throw()
{
    // Buffer is the special case. So don't add log level
    // and timestamp in the buffer message. Just log the raw bytes.
    if ((_log_type == LOG_TYPE_FILE_LOG) && (_log_level >= LOG_LEVEL_BUFFER)) {
        lock();
        _file << text << endl;
        unlock();
    } else if ((_log_type == LOG_TYPE_CONSOLE) && (_log_level >= LOG_LEVEL_BUFFER)) {
        cout << text << endl;
    }
}

void Logger::verbose_buffer(std::string& text) throw()
{
    verbose_buffer(text.data());
}

void Logger::verbose_buffer(std::ostringstream& stream) throw()
{
    string text = stream.str();
    verbose_buffer(text.data());
}

// Interface for Info Log
void Logger::verbose_info(const char* text) throw()
{
    string data;
    data.append("[INFO]: ");
    data.append(text);

    if ((_log_type == LOG_TYPE_FILE_LOG) && (_log_level >= LOG_LEVEL_INFO)) {
        log_into_file(data);
    } else if ((_log_type == LOG_TYPE_CONSOLE) && (_log_level >= LOG_LEVEL_INFO)) {
        log_on_console(data);
    }
}

void Logger::verbose_info(std::string& text) throw()
{
    verbose_info(text.data());
}

void Logger::verbose_info(std::ostringstream& stream) throw()
{
    string text = stream.str();
    verbose_info(text.data());
}

// Interface for Trace Log
void Logger::verbose_trace(const char* text) throw()
{
    string data;
    data.append("[TRACE]: ");
    data.append(text);

    if ((_log_type == LOG_TYPE_FILE_LOG) && (_log_level >= LOG_LEVEL_TRACE)) {
        log_into_file(data);
    } else if ((_log_type == LOG_TYPE_CONSOLE) && (_log_level >= LOG_LEVEL_TRACE)) {
        log_on_console(data);
    }
}

void Logger::verbose_trace(std::string& text) throw()
{
    verbose_trace(text.data());
}

void Logger::verbose_trace(std::ostringstream& stream) throw()
{
    string text = stream.str();
    verbose_trace(text.data());
}

// Interface for Debug Log
void Logger::verbose_debug(const char* text) throw()
{
    string data;
    data.append("[DEBUG]: ");
    data.append(text);

    if ((_log_type == LOG_TYPE_FILE_LOG) && (_log_level >= LOG_LEVEL_DEBUG)) {
        log_into_file(data);
    } else if ((_log_type == LOG_TYPE_CONSOLE) && (_log_level >= LOG_LEVEL_DEBUG)) {
        log_on_console(data);
    }
}

void Logger::verbose_debug(std::string& text) throw()
{
    verbose_debug(text.data());
}

void Logger::verbose_debug(std::ostringstream& stream) throw()
{
    string text = stream.str();
    verbose_debug(text.data());
}

// Interfaces to control log levels
void Logger::update_log_level(LogLevel log_level)
{
    TRY_BLOCK
    _log_level = log_level;
    CATCH_BLOCK
}

// Enable all log levels
void Logger::enable_log()
{
    TRY_BLOCK
    _log_level = LOG_LEVEL_ENABLE_LOG;
    CATCH_BLOCK
}

// Disable all log levels, except error and alarm
void Logger::disable_log()
{
    TRY_BLOCK
    _log_level = LOG_LEVEL_DISABLE_LOG;
    CATCH_BLOCK
}

// Interfaces to control log Types
void Logger::update_log_type(LogType log_type)
{
    TRY_BLOCK
    _log_type = log_type;
    CATCH_BLOCK
}

void Logger::enable_console_logging()
{
    TRY_BLOCK
    _log_type = LOG_TYPE_CONSOLE;
    CATCH_BLOCK
}

void Logger::enable_file_logging()
{
    TRY_BLOCK
    _log_type = LOG_TYPE_FILE_LOG;
    CATCH_BLOCK
}
