#include "qtpopup.h"
#include "QDebug"
#include <QFileInfo>
#include <QImage>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QTimer>
#include <string.h>
#include <unistd.h>

using std::vector;

mutex QtPopUpWindow::m_build_mutex;
QtPopUpWindow* QtPopUpWindow::m_ptr_instance(nullptr);

QtPopUpWindow::QtPopUpWindow(QObject* parent)
    : QObject{ parent }
    , _map_popup_data()
    , _state_popup(QTPOPUP_RESET)
{
    if (!m_ptr_instance)
        m_ptr_instance = this;
    json_handler = QtJsonPopUpHandler::get_instance();
    json_handler->init();

    init_popups();
    update_map_popup_data();
    init_static_text();

    if(update_popup_visiblity(false, MESSAGE_ALL))
        emit popup_state_changed();

    init_subscribe();
}

QtPopUpWindow::~QtPopUpWindow()
{
    qDebug() << "QtPopup Destructor called!!!" << Qt::endl;
}

QtPopUpWindow* QtPopUpWindow::get_instance()
{
    TRY_BLOCK
    if (!m_ptr_instance)
    {
        lock_guard build_lock(m_build_mutex);
        m_ptr_instance = new QtPopUpWindow;
    }
    return m_ptr_instance;
    CATCH_BLOCK
}

void QtPopUpWindow::update_map_popup_data() //тут в классе появляются данные из json файла
{
    TRY_BLOCK
    auto map_json_data = json_handler->get_json_data();
    for (auto& itterator : *map_json_data)
    {
        PopupDataInit temp_popup_data { .popup_symbol_number = itterator.second.symbol_number,
                                        .popup_type = itterator.second.type,
                                        .popup_text = itterator.second.text,
                                        .popup_sound = itterator.second.sound,
                                        .popup_color = itterator.second.color,
                                        .popup_priority = itterator.second.popup_priority,
                                        .popup_visible = false};
        //Заполнение контейнера map со свойствами сообщения. Ключ - приоритет
        _map_popup_data.insert(itterator.second.popup_priority, temp_popup_data);
        //Добавление элемента в вектор, которые отслеживает повторное включение каждого сообщения
        switcher.push_back(false);
    }
    CATCH_BLOCK
}

bool QtPopUpWindow::update_popup_visiblity(bool visibility, int number)
{
    TRY_BLOCK
    bool need_to_emit = false;

    for (auto& itterator : _map_popup_data)
    {
        if (itterator.popup_symbol_number == number || number == MESSAGE_ALL) //выбираем текущий номер, если -1 - значит нужно открыть все
        {
            if(!visibility)
            {
                if(number == MESSAGE_ALL)
                    itterator.popup_visible = false;
                else if(itterator.popup_type == 2 )
                {
                    itterator.popup_visible = false;
                    _state_popup--;
                }
            }
            else if (!itterator.popup_visible && number != MESSAGE_ALL)
            {
                itterator.popup_visible = true;
                _state_popup++;
            }
            m_popup_state[itterator.popup_symbol_number] = itterator.popup_visible;
            need_to_emit = true;
        }
    }
    return need_to_emit;
    CATCH_BLOCK
}

bool QtPopUpWindow::update_popup_close(/*bool visibility, int number*/)
{
    TRY_BLOCK
    if (_state_popup <= 0)
        return false;

//    popup_slot functptr;
    bool need_to_emit = false;

    for (auto itterator = _map_popup_data.end() - 1; itterator != _map_popup_data.begin() - 1; itterator--)
    {
        if (itterator.value().popup_visible)
        {
            if(itterator.value().popup_type == 2)
                return true;

            m_popup_state[itterator.value().popup_symbol_number] = false;
            itterator.value().popup_visible = false;
            _state_popup--;
            need_to_emit = true;
            break;
        }
    }
    if(need_to_emit)
        emit popup_state_changed();

    return need_to_emit;
    CATCH_BLOCK
}

void QtPopUpWindow::update_gui()
{
    TRY_BLOCK
    //if (_state/* == QmlState::QMLSTATE_NORMAL*/) {
        HmiHandler* msg_handler = HmiHandler::getInstance();
        if (msg_handler->get_ptr_to_msg(HMIHANDLER_DD_INFO1_ID)->get_state() == CAN_MESSAGE_STATE_OK)
        {
             DD_INFO1_t* dd_info1_data = reinterpret_cast<DD_INFO1_t*>(msg_handler->get_data_from_msg(HMIHANDLER_DD_INFO1_ID));
             bool need_to_emit = false;
             uint8_t i = 0;
             if (dd_info1_data->msg_01 != switcher[i])
             {
                switcher[i] = dd_info1_data->msg_01;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_01,  i);
             }
             if (dd_info1_data->msg_02 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_02;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_02, i);
             }
             if (dd_info1_data->msg_03 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_03;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_03, i);
             }
             if (dd_info1_data->msg_04 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_04;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_04, i);
             }
             if (dd_info1_data->msg_05 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_05;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_05, i);
             }
             if (dd_info1_data->msg_06 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_06;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_06, i);
             }
             if (dd_info1_data->msg_07 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_07;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_07, i);
             }
             if (dd_info1_data->msg_08 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_08;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_08, i);
             }
             if (dd_info1_data->msg_09 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_09;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_09, i);
             }
             if (dd_info1_data->msg_10 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_10;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_10, i);
             }
             if (dd_info1_data->msg_11 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_11;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_11, i);
             }
             if (dd_info1_data->msg_12 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_12;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_12, i);
             }
             if (dd_info1_data->msg_13 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_13;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_13, i);
             }
             if (dd_info1_data->msg_14 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_14;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_14, i);
             }
             if (dd_info1_data->msg_15 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_15;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_15, i);
             }
             if (dd_info1_data->msg_16 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_16;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_16, i);
             }
             if (dd_info1_data->msg_17 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_17;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_17, i);
             }
             if (dd_info1_data->msg_18 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_18;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_18, i);
             }
             if (dd_info1_data->msg_19 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_19;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_19, i);
             }
             if (dd_info1_data->msg_20 != switcher[++i])
             {
                switcher[i] = dd_info1_data->msg_20;
                need_to_emit = update_popup_visiblity(dd_info1_data->msg_20, i);
             }

             if (need_to_emit)
                 emit popup_state_changed();
        }
    //}
        CATCH_BLOCK

}

bool QtPopUpWindow::update_info(uint32_t _id)
{
    TRY_BLOCK
    if (_id == HMIHANDLER_DD_INFO1_ID)
        update_gui();
    return true;
    CATCH_BLOCK
}

void QtPopUpWindow::init_popups()
{
    TRY_BLOCK
    for (int i = 0; i < 20; i++)
    {
        m_popups_list.append(QStringList({ "NA", "NA", "NA" }));
        m_popup_state.append(false);
    }
    CATCH_BLOCK
}

const int& QtPopUpWindow::get_state_popup() const
{
    TRY_BLOCK
    return _state_popup;
    CATCH_BLOCK
}

void QtPopUpWindow::init_static_text()
{
    TRY_BLOCK
    for (auto& itterator : _map_popup_data)
    {
            auto number = itterator.popup_symbol_number;
            m_popups_list[number][0] = itterator.popup_text;
            m_popups_list[number][1] = itterator.popup_color;
            m_popups_list[number][2] = QString::number(itterator.popup_priority);
    }
    emit static_popup_text_changed();
    CATCH_BLOCK
}

void QtPopUpWindow::init_subscribe()
{
    TRY_BLOCK
    auto ptrnotifer = subscribe_notifer::get_instance();
    ptrnotifer->subscribe(HMIHANDLER_DD_INFO1_ID, this);
    CATCH_BLOCK
}
