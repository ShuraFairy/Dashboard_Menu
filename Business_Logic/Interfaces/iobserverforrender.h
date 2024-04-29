#ifndef IOBSERVERFORRENDER_H
#define IOBSERVERFORRENDER_H
#include <QGuiApplication>
#include <iostream>
#include <list>
#include <string>

typedef enum {
    LANGUAGE_ENG = QLocale::English,
    LANGUAGE_RUS = QLocale::Russian,
} Language;

class IObserverForRender {
public:
    IObserverForRender()            = default;
    virtual ~IObserverForRender()   = default;
    virtual void update_gui()       = 0;
    virtual void qml_responses(int) = 0;
};

#endif // IOBSERVERFORRENDER_H
