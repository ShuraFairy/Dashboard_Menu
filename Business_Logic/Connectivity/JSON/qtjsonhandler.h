#pragma once
#ifndef QTJSONHANDLER_H
#define QTJSONHANDLER_H

#include <QtCore>
#include <iostream>
#include "../../Logger/exception_define.h"

#define QTJSONHANDLER_MAX_COLORS 5

using namespace std;

class QtJsonHandler {

public:
    typedef struct {
        QString symbol_number;
        QString colors[QTJSONHANDLER_MAX_COLORS];
        QString sound;
        QString sound_speed;
        QString flash_freq_hz;
        QString description;
        QString telltale_color;
        QString telltale_path;
        QString telltale_category;
        QString telltale_canid;
        quint8 telltale_priority;
        quint8 position;
        quint8 json_file_pos;
    } JsonData;

    typedef struct {
        quint8 telltale_position;
        quint8 telltale_priority;
        QString telltale_names;
    } TellTalesPositions;

    ~QtJsonHandler();
    static QtJsonHandler* get_instance();

    void init();
    map<QString, QtJsonHandler::JsonData>* get_json_data();

private:
    QtJsonHandler();
    void read_json_file();
    void update_telltale_position();

    QtJsonHandler::JsonData* get_symbol_data(QString str_symbol);
    list<TellTalesPositions> get_telltale_positions(quint8 position);

    static mutex m_build_mutex;
    static shared_ptr<QtJsonHandler> m_ptr_instance;

    map<QString, JsonData> _map_json_data;
    map<quint8, list<TellTalesPositions>> _map_telltale_position;
};

#endif // QTJSONHANDLER_H
