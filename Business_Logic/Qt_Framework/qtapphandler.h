#ifndef QTAPPHANDLER_H
#define QTAPPHANDLER_H

#include <QObject>
//#include <QVariant>
#include "../Logger/exception_define.h"

class QtAppHandler : public QObject {
    Q_OBJECT
public:
    explicit QtAppHandler(void (*thread_instance_ptr)(), QObject* parent = nullptr);
    ~QtAppHandler();

    /* Naming Convention is not changed as the function is used to override the QObject Function */
    bool eventFilter(QObject* obj, QEvent* event) override;
    void (*disable_threadhandler)();

signals:
    void quit();
};

#endif // QTAPPHANDLER_H
