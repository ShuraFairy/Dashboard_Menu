#include "error_tracing.h"

std::mutex OriginalTracer::m_build_mutex;
std::shared_ptr<OriginalTracer> OriginalTracer::instance(nullptr);

void OriginalTracer::write_error(std::string error){
    error_report<<error<<std::endl;
//    error_report.flush();
}

std::shared_ptr<OriginalTracer> OriginalTracer::get_instance(){
    if (!instance){
        std::lock_guard build_lock(m_build_mutex);
        instance.reset(new OriginalTracer);
    }
    return instance;
}

void OriginalTracer::catch_error(std::string error){
    if (!error_report.is_open())
        error_report.open(ERROR_REPORT_PATH, std::ios_base::app);
    write_error(error);
}

void OriginalTracer::clean_catcher(){
    error_report.open(ERROR_REPORT_PATH, std::ios_base::trunc);
    error_report.close();
}

void OriginalTracer::close_catcher(){
    error_report.close();
}
