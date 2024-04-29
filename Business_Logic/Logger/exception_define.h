#ifndef EXCEPTION_DEFINE_H
#define EXCEPTION_DEFINE_H

#include <execinfo.h>
#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include "error_tracing.h"
#include "../Connectivity/JSON/qtjsonconfiguredata.h"

void catch_exception(std::string);
void clean_error_report();
void close_error_report();

#define TRY_BLOCK \
    try{
#define CATCH_BLOCK \
    } catch(std::exception& e){ \
        catch_exception("Exception caught at line " + std::to_string(__LINE__) + " in file: " + std::string(__FILE__) + " : " + e.what() + "\n"); \
        throw e;\
   } catch(...){ \
        catch_exception("Exception caught at line " + std::to_string(__LINE__) + " in file: " + std::string(__FILE__) + " : " + "unknown exception" + "\n"); \
        throw;\
   }
  //add custom exceptions


#define TRY_MAIN_BLOCK try{ \
    clean_error_report();
#define CATCH_MAIN_BLOCK \
    } catch(...){ \
        close_error_report(); \
    }

#endif // EXCEPTION_DEFINE_H
