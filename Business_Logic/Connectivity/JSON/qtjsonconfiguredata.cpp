#include "qtjsonconfiguredata.h"

mutex QtJsonConfigureData::m_build_mutex;
shared_ptr<QtJsonConfigureData> QtJsonConfigureData::m_ptr_instance(nullptr);

QtJsonConfigureData::QtJsonConfigureData()
    : _map_json_config_data()
    , m_is_file_reachable(false)
{
}

QtJsonConfigureData::~QtJsonConfigureData()
{
}

QtJsonConfigureData* QtJsonConfigureData::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard<mutex> build_lock(m_build_mutex);
        m_ptr_instance = shared_ptr<QtJsonConfigureData>(new QtJsonConfigureData);
        m_ptr_instance->m_is_file_reachable = m_ptr_instance->write_initial_data_json_file();
    }
    return m_ptr_instance.get();
    CATCH_BLOCK
}

QString QtJsonConfigureData::get_config_data(QString element_name)
{
    TRY_BLOCK
    if (_map_json_config_data.empty())
        read_configure_json_data();
    return _map_json_config_data[element_name];
    CATCH_BLOCK
}

bool QtJsonConfigureData::read_configure_json_data()
{
    TRY_BLOCK
    bool return_status = false;
    QJsonDocument jsonDoc;
    QByteArray jsonData;
    QJsonParseError json_error;
    QString file_path = CONFIGURATION_FILE_PATH;
    //TODO: json parameters to defines copy from qtmenuops
    _map_json_config_data["installation_temperature"] = "23"; //json_obj.value("installation_temperature").toString();
    QFile file(file_path);
    if (file.open(QIODevice::ReadOnly)) {
        jsonData = jsonDoc.toJson();
        jsonData = file.readAll();
        QJsonDocument document = QJsonDocument::fromJson(jsonData, &json_error);
        if (json_error.error != QJsonParseError::NoError) {
            qDebug() << "fromJson failed: " << json_error.errorString() << Qt::endl;
            return false;
        }
        if (document.isObject()) {
            QJsonObject json_obj = document.object();
            _map_json_config_data["installation_temperature"] = json_obj.value("installation_temperature").toString();
            _map_json_config_data["volume"] = json_obj.value("volume").toString();
            _map_json_config_data["automatic_adjustment_brightness"] = json_obj.value("automatic_adjustment_brightness").toString();
            _map_json_config_data["brightness"] = json_obj.value("brightness").toString();
            _map_json_config_data["language_change"] = json_obj.value("language_change").toString();
            _map_json_config_data["automatic_low_beam"] = json_obj.value("automatic_low_beam").toString();
            _map_json_config_data["automatic_wiper_operation"] = json_obj.value("automatic_wiper_operation").toString();
            _map_json_config_data["sensor_sensitivity_to_rain"] = json_obj.value("sensor_sensitivity_to_rain").toString();
            _map_json_config_data["sensor_sensitivity_to_light"] = json_obj.value("sensor_sensitivity_to_light").toString();
            _map_json_config_data["installation_temperature_DC"] = json_obj.value("installation_temperature_DC").toString();
            _map_json_config_data["automatic_opening"] = json_obj.value("automatic_opening").toString();
            _map_json_config_data["automatic_door_closing_by_sensors"] = json_obj.value("automatic_door_closing_by_sensors").toString();
            _map_json_config_data["automatic_door_closing_when_leaving_bus"] = json_obj.value("automatic_door_closing_when_leaving_bus").toString();
            _map_json_config_data["automatic_kneeling"] = json_obj.value("automatic_kneeling").toString();
            _map_json_config_data["automatic_on_of_alarm_system"] = json_obj.value("automatic_on_of_alarm_system").toString();
            _map_json_config_data["doorway_passenger_sensor"] = json_obj.value("doorway_passenger_sensor").toString();
            _map_json_config_data["brake_pads_wear_1_2"] = json_obj.value("brake_pads_wear_1_2").toString();
            _map_json_config_data["new_password"] = json_obj.value("new_password").toString();
            _map_json_config_data["parameterization"] = json_obj.value("parameterization").toString();
            _map_json_config_data["turbo_timer"] = json_obj.value("turbo_timer").toString();
            _map_json_config_data["subitem_menu_visibility"] = json_obj.value("subitem_menu_visibility").toString();
            return_status = true;
        }
        file.close();
    } else {
        return_status = false;
        qDebug() << "File already exists" << Qt::endl;
    }
    return return_status;
    CATCH_BLOCK
}

bool QtJsonConfigureData::write_json_file(QString element_name, QString update_value)
{
    TRY_BLOCK
    QJsonObject jsonObject;
    QString map_key;
    QString map_value;
    QMap<QString, QString>::iterator itterator_data;

    QString file_path = CONFIGURATION_FILE_PATH;
    read_configure_json_data();

    _map_json_config_data[element_name] = update_value;

    for (itterator_data = _map_json_config_data.begin(); itterator_data != _map_json_config_data.end(); ++itterator_data) {
        map_key = itterator_data.key();
        map_value = itterator_data.value();
        jsonObject.insert(map_key, map_value);
    }

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();
    QFile file(file_path);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonData);
        file.close();
        return true;
    } else {
        return false;
    }
    CATCH_BLOCK
}

bool QtJsonConfigureData::write_initial_data_json_file()
{
    TRY_BLOCK
    bool initial_write_status = false;
    QJsonObject json_object;
    QString file_path = CONFIGURATION_FILE_PATH;

    json_object["new_password"] = "1252";
    json_object["installation_temperature"] = "21";
    json_object["volume"] = "100";
    json_object["automatic_adjustment_brightness"] = "OFF";
    json_object["brightness"] = "100";
    json_object["language_change"] = "RUSSIAN";
    json_object["automatic_low_beam"] = "OFF";
    json_object["automatic_wiper_operation"] = "OFF";
    json_object["sensor_sensitivity_to_rain"] = "1";
    json_object["sensor_sensitivity_to_light"] = "1";
    json_object["installation_temperature_DC"] = "21";
    json_object["automatic_opening"] = "OFF";
    json_object["automatic_door_closing_by_sensors"] = "OFF";
    json_object["automatic_door_closing_when_leaving_bus"] = "OFF";
    json_object["automatic_kneeling"] = "OFF";
    json_object["automatic_on_of_alarm_system"] = "OFF";
    json_object["doorway_passenger_sensor"] = "OFF";
    json_object["brake_pads_wear_1_2"] = "CAN";
    json_object["parameterization"] = "01";
    json_object["turbo_timer"] = "OFF";
    json_object["subitem_menu_visibility"] = "0xFFFFFFFFFFFFFFFF";

    QJsonDocument json_doc(json_object);
    QByteArray json_data = json_doc.toJson();
    QFile file_handle(file_path);

    if (file_handle.exists() == false) {
        if (file_handle.open(QIODevice::WriteOnly)) {
            file_handle.write(json_data);
            file_handle.close();
            initial_write_status = true;
        } else {
            initial_write_status = false;
        }
    } else {
        initial_write_status = true;
    }

    return initial_write_status;
    CATCH_BLOCK
}
