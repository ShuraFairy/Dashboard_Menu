#include "qtjsonpopuphandler.h"

using namespace std;

mutex QtJsonPopUpHandler::m_build_mutex;
shared_ptr<QtJsonPopUpHandler> QtJsonPopUpHandler::m_ptr_instance;

QtJsonPopUpHandler::QtJsonPopUpHandler()
    : _map_json_popup_data()
{
}

QtJsonPopUpHandler::~QtJsonPopUpHandler()
{
}

QtJsonPopUpHandler* QtJsonPopUpHandler::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = shared_ptr<QtJsonPopUpHandler>(new QtJsonPopUpHandler);
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

void QtJsonPopUpHandler::init()
{
    TRY_BLOCK
    read_json_popup_file();
    CATCH_BLOCK
}

map<QString, QtJsonPopUpHandler::JsonData>* QtJsonPopUpHandler::get_json_data()
{
    TRY_BLOCK
    return &_map_json_popup_data;
    CATCH_BLOCK
}

void QtJsonPopUpHandler::read_json_popup_file()
{
    TRY_BLOCK
    QFile file(":/Json/pop_up.json");
    QJsonParseError json_error;

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray bytes = file.readAll();
        file.close();
        QJsonDocument document = QJsonDocument::fromJson(bytes, &json_error);
        if (json_error.error != QJsonParseError::NoError) {
            cout << "fromJson failed: " << json_error.errorString().toStdString() << endl;
            return;
        }
        if (document.isObject()) {
            QJsonObject json_obj = document.object();
            foreach (const QString& key, json_obj.keys()) {
                QJsonObject json_obj_value(json_obj.value(key).toObject());
                QString symbol_number = json_obj.value(key).toObject().value("symbol_number").toString();
                _map_json_popup_data[symbol_number].symbol_number = (json_obj.value(key).toObject().value("symbol_number").toString()).toUInt() - 1;
                _map_json_popup_data[symbol_number].type = (json_obj.value(key).toObject().value("type").toString()).toUInt();
                _map_json_popup_data[symbol_number].text = json_obj.value(key).toObject().value("text").toString();
                _map_json_popup_data[symbol_number].sound = json_obj.value(key).toObject().value("sound").toString();
                _map_json_popup_data[symbol_number].color = json_obj.value(key).toObject().value("color").toString();
                _map_json_popup_data[symbol_number].popup_priority = MAX_PRIORITY - (json_obj.value(key).toObject().value("priority").toString()).toUInt();
            }
        }
    }
    CATCH_BLOCK
}
