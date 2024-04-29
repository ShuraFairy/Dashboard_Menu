#include "qtjsonhandler.h"
#include "QDebug"

using namespace std;

mutex QtJsonHandler::m_build_mutex;
shared_ptr<QtJsonHandler> QtJsonHandler::m_ptr_instance(nullptr);

QtJsonHandler::QtJsonHandler()
    : _map_json_data()
    , _map_telltale_position()
{
}

QtJsonHandler::~QtJsonHandler()
{
}

QtJsonHandler* QtJsonHandler::get_instance()
{
    TRY_BLOCK
    if(!m_ptr_instance)
    {
        lock_guard<mutex> build_lock(m_build_mutex);
        m_ptr_instance = shared_ptr<QtJsonHandler>(new QtJsonHandler);
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

void QtJsonHandler::init()
{
    TRY_BLOCK
    read_json_file();
    CATCH_BLOCK
}

map<QString, QtJsonHandler::JsonData>* QtJsonHandler::get_json_data()
{
    TRY_BLOCK
    return &_map_json_data;
    CATCH_BLOCK
}

QtJsonHandler::JsonData* QtJsonHandler::get_symbol_data(QString str_symbol)
{
    TRY_BLOCK
    return &_map_json_data[str_symbol];
    CATCH_BLOCK
}

list<QtJsonHandler::TellTalesPositions> QtJsonHandler::get_telltale_positions(quint8 position)
{
    TRY_BLOCK
    map<quint8, list<TellTalesPositions>> telltales_position;

    auto positionIterator = _map_telltale_position.find(position);

    // Check if the position was found in the map
    if (positionIterator != _map_telltale_position.end()) {
        // Return the list of TellTalesPositions for the target position
        return positionIterator->second;
    } else {
        // If position not found, return an empty list
        return std::list<TellTalesPositions>();
    }
    CATCH_BLOCK
}

void QtJsonHandler::read_json_file()
{
    TRY_BLOCK
    uint8_t j;
    qint8 i = 1;
    QFile file(":/Json/tell-tales.json");
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
                QJsonArray data_color_array = json_obj.value(key).toObject().value("colors").toArray();
                _map_json_data[symbol_number].symbol_number = symbol_number;
                _map_json_data[symbol_number].description = json_obj.value(key).toObject().value("description").toString();
                _map_json_data[symbol_number].sound = json_obj.value(key).toObject().value("sound").toString();
                _map_json_data[symbol_number].position = (json_obj.value(key).toObject().value("position").toString()).toUInt();
                _map_json_data[symbol_number].telltale_priority = (json_obj.value(key).toObject().value("telltale_priority").toString()).toUInt();
                _map_json_data[symbol_number].sound_speed = json_obj.value(key).toObject().value("sound_speed").toString();
                _map_json_data[symbol_number].flash_freq_hz = json_obj.value(key).toObject().value("flash_freq_hz").toString();
                _map_json_data[symbol_number].telltale_color = json_obj.value(key).toObject().value("telltale_color").toString();
                _map_json_data[symbol_number].telltale_path = json_obj.value(key).toObject().value("telltale_path").toString();
                _map_json_data[symbol_number].telltale_category = json_obj.value(key).toObject().value("telltale_category").toString();
                _map_json_data[symbol_number].telltale_canid = json_obj.value(key).toObject().value("telltale_canid").toString();
                _map_json_data[symbol_number].json_file_pos = i;
                for (j = 0; j < data_color_array.size(); j++) {
                    _map_json_data[symbol_number].colors[j] = data_color_array[j].toString();
                }
                i++;
            }
            update_telltale_position();
        }
    }
    CATCH_BLOCK
}

void QtJsonHandler::update_telltale_position()
{
    TRY_BLOCK
    _map_telltale_position.clear();
    if (!_map_json_data.empty()) {
        for (const auto& pair : _map_json_data) {
            const JsonData& jsonData = pair.second;
            quint8 position = jsonData.position;
            QString telltale_names = jsonData.symbol_number;
            // Check if the position already exists in _map_telltale_position
            auto it = _map_telltale_position.find(position);
            if (it == _map_telltale_position.end()) {
                // If not found, create a new list and add the TellTalesPositions
                std::list<TellTalesPositions> telltaleList;
                telltaleList.push_back({ position, jsonData.telltale_priority, telltale_names });
                _map_telltale_position[position] = telltaleList;
            } else {
                // If found, append to the existing list
                it->second.push_back({ position, jsonData.telltale_priority, telltale_names });
            }
        }
    }
    CATCH_BLOCK
}
