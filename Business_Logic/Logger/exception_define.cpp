#include "exception_define.h"

std::shared_ptr<OriginalTracer> ptr = OriginalTracer::get_instance();

void catch_exception(std::string exception){
    ptr->catch_error(exception);
}

void clean_error_report(){
    ptr->clean_catcher();
}

void close_error_report(){
    ptr->close_catcher();
}

