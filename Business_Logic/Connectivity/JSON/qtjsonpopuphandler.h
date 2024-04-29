#pragma once
#ifndef QTJSONPOPUPHANDLER_H
#define QTJSONPOPUPHANDLER_H

#include <QtCore>
#include <iostream>
#include "../../Logger/exception_define.h"

#define MAX_PRIORITY 19

using namespace std;

class QtJsonPopUpHandler {

public:
    typedef struct {
        quint8 symbol_number;
        quint8 type;
        QString text;
        QString sound;
        QString color;
        quint8 popup_priority;
    } JsonData;

    ~QtJsonPopUpHandler();
    static QtJsonPopUpHandler* get_instance();

    void init();
    map<QString, QtJsonPopUpHandler::JsonData>* get_json_data();

private:
    QtJsonPopUpHandler();
    void read_json_popup_file();

    static mutex m_build_mutex;
    static shared_ptr<QtJsonPopUpHandler> m_ptr_instance;

    map<QString, JsonData> _map_json_popup_data;
};

#endif // QTJSONPOPUPHANDLER_H
