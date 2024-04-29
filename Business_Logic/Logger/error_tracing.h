#ifndef ERROR_TRACING_H
#define ERROR_TRACING_H

#include <fstream>
#include <memory>
#include <mutex>

#include "../Connectivity/JSON/qtjsonconfiguredata.h"

#define ERROR_REPORT_PATH "./home/root/error_report"

class OriginalTracer{
public:
    static std::shared_ptr<OriginalTracer> get_instance();
    void catch_error(std::string);
    void clean_catcher();
    void close_catcher();
    ~OriginalTracer()=default;
private:
    OriginalTracer()=default;
    void write_error(std::string);

    static std::mutex m_build_mutex;
    static std::shared_ptr<OriginalTracer> instance;
    std::ofstream error_report;
};

//ADD THREAD-SAFETY

#endif // ERROR_TRACING_H
