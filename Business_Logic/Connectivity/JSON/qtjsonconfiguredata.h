#pragma once
#ifndef QTJSONCONFIGUREDATA_H
#define QTJSONCONFIGUREDATA_H
#include <QtCore>
#include "../../Logger/exception_define.h"

#define CONFIGURATION_FILE_PATH "/etc/config_data.json"


using namespace std;
class QtJsonConfigureData {
public:
    ~QtJsonConfigureData();
    static QtJsonConfigureData* get_instance();

    QString get_config_data(QString);
    bool write_json_file(QString element_name, QString update_value);
    bool is_reachable() {return m_is_file_reachable;};

private:
    QtJsonConfigureData();
    bool read_configure_json_data();
    bool write_initial_data_json_file();

    static mutex m_build_mutex;
    static shared_ptr<QtJsonConfigureData> m_ptr_instance;

    QMap<QString, QString> _map_json_config_data;
    bool m_is_file_reachable;
};

#endif // QTJSONCONFIGUREDATA_H
