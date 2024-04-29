#include "qtjsonmenuhandler.h"

mutex QtJsonMenuHandler::m_build_mutex;
shared_ptr<QtJsonMenuHandler> QtJsonMenuHandler::m_ptr_instance;

QtJsonMenuHandler::QtJsonMenuHandler()
    : _map_json_menu_data()
{
}

QtJsonMenuHandler::~QtJsonMenuHandler()
{
}

QtJsonMenuHandler* QtJsonMenuHandler::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = shared_ptr<QtJsonMenuHandler>(new QtJsonMenuHandler);
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

void QtJsonMenuHandler::init()
{
    TRY_BLOCK
    read_json_menu_file();
    CATCH_BLOCK
}

QtJsonMenuHandler::JsonMenuData* QtJsonMenuHandler::get_menu_data(QString menu_name, QString sub_item, QString field_no)
{
    TRY_BLOCK
    tuple<QString, QString, QString> keys(menu_name, sub_item, field_no);
    return &_map_json_menu_data[keys];
    CATCH_BLOCK
}

void QtJsonMenuHandler::read_json_menu_file()
{
    TRY_BLOCK
    QFile file_menu(":/Json/menu_items_3.json");
    QJsonParseError json_error;

    if (file_menu.open(QIODevice::ReadOnly)) {
        QByteArray bytes = file_menu.readAll();
        file_menu.close();
        QJsonDocument document = QJsonDocument::fromJson(bytes, &json_error);
        if (json_error.error != QJsonParseError::NoError) {
            cout << "fromJson failed: " << json_error.errorString().toStdString() << endl;
            return;
        }
        if (document.isObject()) {

            QJsonObject json_obj = document.object();
            foreach (const QString& key, json_obj.keys()) {

                QJsonObject json_obj_value(json_obj.value(key).toObject());
                QString menu_name = json_obj.value(key).toObject().value("menu_name").toString();
                QString sub_item = json_obj.value(key).toObject().value("sub_item").toString();
                QString parameter_no = json_obj.value(key).toObject().value("parameter_no").toString();
                tuple<QString, QString, QString> keys(menu_name, sub_item, parameter_no);
                _map_json_menu_data[keys].menu_name = menu_name;
                _map_json_menu_data[keys].sub_item = sub_item;
                _map_json_menu_data[keys].parameter_no = parameter_no;
                _map_json_menu_data[keys].parameter_name = json_obj.value(key).toObject().value("parameter_name").toString();
                _map_json_menu_data[keys].image_path = json_obj.value(key).toObject().value("image_path").toString();
                _map_json_menu_data[keys].min_value = json_obj.value(key).toObject().value("item_min_value").toString();
                _map_json_menu_data[keys].mid_value = json_obj.value(key).toObject().value("item_mid_value").toString();
                _map_json_menu_data[keys].max_value = json_obj.value(key).toObject().value("item_max_value").toString();
                _map_json_menu_data[keys].flag = json_obj.value(key).toObject().value("flag").toString();
            }
        }
    }
    CATCH_BLOCK
}
