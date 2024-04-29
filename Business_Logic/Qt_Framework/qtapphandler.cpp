#include "qtapphandler.h"
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

QtAppHandler::QtAppHandler(void (*thread_instance_ptr)(), QObject* parent)
    : QObject { parent }
    , disable_threadhandler(*thread_instance_ptr)
{
}

QtAppHandler::~QtAppHandler()
{
    qDebug() << "AppHandler Destructor called!!!" << Qt::endl;
}

bool QtAppHandler::eventFilter(QObject* obj, QEvent* event)
{
    TRY_BLOCK
    bool ret_status = false;
    qDebug() << "Inside eventFilter" << Qt::endl;
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key() == Qt::Key_Q)
        {
            // Enter or return was pressed
            qDebug() << "Enter key pressed*****" << Qt::endl;
            disable_threadhandler();
            emit quit();
            ret_status = true;
        }
    }
    ret_status = QObject::eventFilter(obj, event);
    return ret_status;
    CATCH_BLOCK
}
