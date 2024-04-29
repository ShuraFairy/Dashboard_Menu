#ifndef QTPOPUPWINDOW_H
#define QTPOPUPWINDOW_H

#include "../Connectivity/JSON/qtjsonpopuphandler.h"
#include "../Connectivity/hmi_handler.h"
#include "../Interfaces/iobserverforrender.h"
#include "../subscribe_notifer.h"
#include <QObject>
#include <QStringList>
#include <vector>
#include <unordered_map>
#include "../Logger/exception_define.h"

#define QTPOPUP_RESET 0
#define MESSAGE_ALL (-1)

using std::vector;

class QtPopUpWindow : public QObject, public IObserverForRender, public ISubscriber {
    Q_OBJECT
    Q_PROPERTY(QList<QStringList> static_popup_text READ get_static_popup_text WRITE set_static_popup_text NOTIFY static_popup_text_changed);
    Q_PROPERTY(QList<bool> popup_state READ get_popup_state WRITE set_popup_state NOTIFY popup_state_changed);
public:
    QtJsonPopUpHandler* json_handler;

    typedef struct {
        uint8_t popup_symbol_number;
        uint8_t popup_type;
        QString popup_text;
        QString popup_sound;
        QString popup_color;
        uint8_t popup_priority;
        bool popup_visible;
    } PopupDataInit;

    QtPopUpWindow(QObject* parent = nullptr);
    ~QtPopUpWindow();
    static QtPopUpWindow* get_instance();

    /******************************/
    void update_gui() override; //Функция вызывается при получении сигнала по can
    bool update_info(uint32_t _id) override;
    void qml_responses(int) override {};
    inline const QList<QStringList>& get_static_popup_text() const { return m_popups_list; } ;
    inline void set_static_popup_text(const QList<QStringList>& value)
    {
        if (value != m_popups_list)
        {
            m_popups_list = value;
            emit static_popup_text_changed();
        }
    }
    inline const QList<bool>& get_popup_state() const { return m_popup_state; } ;
    inline void set_popup_state(const QList<bool>& value)
    {
        if (value != m_popup_state)
        {
            m_popup_state = value;
            emit popup_state_changed();
        }
    }
    const int& get_state_popup() const;

    //Закрытие окна, находящегося выше остальных(наиболее приоритетного)
    //Вызывается из класса меню при нажатии кнопки ОК
    bool update_popup_close();
signals:
    void static_popup_text_changed();
    void popup_state_changed();

private:
    void init_static_text();
    void init_subscribe() override;

    void update_map_popup_data(); //Заполнение контейнера элементами json фала

    //Изменение видимости сообщение(открытие/закрытие)
    //Вызывается из других классов
    bool update_popup_visiblity(bool visibility, int number);

    void init_popups(void); //Инициализация popup_pos

    static mutex m_build_mutex;
    static QtPopUpWindow* m_ptr_instance;

    QMap<uint8_t, PopupDataInit> _map_popup_data;
    QList<bool> m_popup_state;
    QList<QStringList> m_popups_list;
    vector<bool> switcher;

    int _state_popup; //Количество открытых окон
};

#endif // QTPOPUPWINDOW_H
