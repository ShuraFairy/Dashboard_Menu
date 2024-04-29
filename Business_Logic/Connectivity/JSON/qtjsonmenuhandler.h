#ifndef QTJSONMENUHANDLER_H
#define QTJSONMENUHANDLER_H

#include <QtCore>
#include <iostream>
#include "../../Logger/exception_define.h"

using namespace std;
class QtJsonMenuHandler {
public:
    typedef struct {
        QString menu_name;
        QString sub_item;
        QString parameter_no;
        QString parameter_name;
        QString image_path;
        QString min_value;
        QString mid_value;
        QString max_value;
        QString flag;
    } JsonMenuData;

    ~QtJsonMenuHandler();
    static QtJsonMenuHandler* get_instance();
    void init();
    QtJsonMenuHandler::JsonMenuData* get_menu_data(QString, QString, QString);

private:
    QtJsonMenuHandler();
    void read_json_menu_file();

    static mutex m_build_mutex;
    static shared_ptr<QtJsonMenuHandler> m_ptr_instance;

    map<tuple<QString, QString, QString>, JsonMenuData> _map_json_menu_data;
};

#endif // QTJSONMENUHANDLER_H
