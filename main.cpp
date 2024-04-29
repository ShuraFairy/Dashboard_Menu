#include "Business_Logic/Logger/logger.h"
#include "Business_Logic/Qt_Framework/qtairpressure1.h"
#include "Business_Logic/Qt_Framework/qtairpressure2.h"
#include "Business_Logic/Qt_Framework/qtapphandler.h"
#include "Business_Logic/Qt_Framework/qtcentraldashboard.h"
#include "Business_Logic/Qt_Framework/qtenginemeter.h"
#include "Business_Logic/Qt_Framework/qtmenuops.h"
#include "Business_Logic/Qt_Framework/qtpopup.h"
#include "Business_Logic/Qt_Framework/qtspeedometer.h"
#include "Business_Logic/Qt_Framework/qttelltales.h"
#include "Business_Logic/Connectivity/can_handler.h"
#include "Business_Logic/playlisthandlerwav.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QtQuick>
#include <unistd.h>
#include "Business_Logic/soundplaylist.h"
#include "Business_Logic/Logger/error_tracing.h"
#include "Business_Logic/Logger/exception_define.h"

#include "Business_Logic/Interfaces/iplaylist.h"
#include "Business_Logic/playlistfactory.h"


using namespace CPlusPlusLogging;

/*********** Main entry to Buissness logic ***************/
int main(int argc, char* argv[])
{
    TRY_MAIN_BLOCK
#if 1
    QLoggingCategory::setFilterRules("*.debug=true\n"
                                     "*.info=false\n"
                                     "*.warning=false\n"
                                     "*.critical=true");
    fprintf(stderr, "Disabling QML logging in release build.\n");
#endif

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);  
    QGuiApplication app(argc, argv);
    /********* Register Event Handler and abdd a callback for receive thread exit **********/
/*    qmlRegisterUncreatableMetaObject(
        DataContractsNamespace::staticMetaObject, // meta object created by Q_NAMESPACE macro
        "datacontract.namespace", // import statement (can be any string)
        1, 0, // major and minor version of the import
        "DataContractIds", // name in QML (does not have to match C++ name)
        "Error: only enums" // error in case someone tries to create a MyNamespace object
    );
    */
    subscribe_notifer* notifer = subscribe_notifer::get_instance();
    CanDataHandler* obj_can = CanDataHandler::getInstance();

    qmlRegisterType<QtMenuOps>("com.mettem.menuops", 1, 0, "Qtmenuops");
    qmlRegisterType<QtSpeedometer>("com.mettem.speedometer", 1, 0, "Qtspeedometer");
    qmlRegisterType<QtEngineMeter>("com.mettem.enginemeter", 1, 0, "Qtenginemeter");
    qmlRegisterType<QtAirPressure1>("com.mettem.airpressure1", 1, 0, "Qtairpressure1");
    qmlRegisterType<QtAirPressure2>("com.mettem.airpressure2", 1, 0, "Qtairpressure2");
    qmlRegisterType<QtCentralDashboard>("com.mettem.centraldashboard", 1, 0, "Qtcentraldashboard");
    qmlRegisterType<QtTelltales>("com.mettem.telltales", 1, 0, "Qttelltales");
    qmlRegisterType<QtPopUpWindow>("com.mettem.popupwindow", 1, 0, "Qtpopupwindow");
    qmlRegisterType<PlaylistHandlerWav>("com.mettem.playlisthandlerwav", 1, 0, "PlaylistHandlerWav");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl) {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);
    engine.load(url);
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    QObject* object = engine.rootObjects()[0];

    QtMenuOps* ptrmenuops = QtMenuOps::getInstance();
    engine.rootContext()->setContextProperty("obj_menuops", ptrmenuops);
    QtSpeedometer* ptrspeedometer = QtSpeedometer::get_instance();
    engine.rootContext()->setContextProperty("obj_speedometer", (QObject*)ptrspeedometer);
    QtEngineMeter* ptrenginemeter = QtEngineMeter::get_instance();
    engine.rootContext()->setContextProperty("obj_enginemeter", (QObject*)ptrenginemeter);
    QtAirPressure1* ptrairpressure1 = QtAirPressure1::get_instance();
    engine.rootContext()->setContextProperty("obj_airpressure1", (QObject*)ptrairpressure1);
    QtAirPressure2* ptrairpressure2 = QtAirPressure2::get_instance();
    engine.rootContext()->setContextProperty("obj_airpressure2", (QObject*)ptrairpressure2);
    QtCentralDashboard* ptrcentraldashboard = QtCentralDashboard::get_instance();
    engine.rootContext()->setContextProperty("obj_centraldashboard", (QObject*)ptrcentraldashboard);

    QtTelltales* ptrtelltales = QtTelltales::get_instance();
    engine.rootContext()->setContextProperty("obj_telltale", ptrtelltales);

    QtPopUpWindow* ptrpopupwindow = QtPopUpWindow::get_instance();
    engine.rootContext()->setContextProperty("obj_popupwindow", (QObject*)ptrpopupwindow);

    IPlaylist* obj_playlist = Playlistfactory::get_playlist();
    engine.rootContext()->setContextProperty("obj_playlist", obj_playlist);

    ptrspeedometer->qml_responses(QmlState::QMLSTATE_INPROGRESS);
    ptrenginemeter->qml_responses(QmlState::QMLSTATE_INPROGRESS);
    ptrairpressure1->qml_responses(QmlState::QMLSTATE_INPROGRESS);
    ptrairpressure2->qml_responses(QmlState::QMLSTATE_INPROGRESS);
    ptrtelltales->qml_responses(QmlState::QMLSTATE_INPROGRESS);

    //ptrpopupwindow->qml_responses(QmlState::QMLSTATE_INPROGRESS);

    ptrmenuops->set_popup(ptrpopupwindow);

    ptrcentraldashboard->update_central_dashboard_text();
/*    QObject::connect(ptrairpressure1, &QtAirPressure1::air_pressure1_telltale, ptrtelltales, &QtTelltales::get_airpressure1_data);
    QObject::connect(ptrairpressure2, &QtAirPressure2::air_pressure2_telltale, ptrtelltales, &QtTelltales::get_airpressure2_data);*/
    QObject::connect(ptrmenuops, &QtMenuOps::update_central_dashboard_data, ptrcentraldashboard, &QtCentralDashboard::update_central_dashboard_text);

    if (argc > 1) {
        qDebug() << "The 1st argument passed is " << argv[0] << Qt::endl;
        qDebug() << "The 2nd argument passed is " << argv[1] << Qt::endl;
        // Set a property in the QML context with the value from argv[1]
        engine.rootContext()->setContextProperty("commandLineArgument", QString(argv[1]));
    }
    obj_can->can_init();

    qDebug("Start thread");
    thread gui_update((*notifer));
    thread send_dd(can_write_data);
//    thread gui_update(subject);

    thread sound_play([&](){
        while(true){
            obj_playlist->run_playlist();
            this_thread::sleep_for(chrono::milliseconds(5));
        }
    });

    bool ret = app.exec();
    notifer->send_thread_exit();

    if (sound_play.joinable())
        sound_play.join();

    if (gui_update.joinable())
        gui_update.join();

    return ret;
    CATCH_MAIN_BLOCK
}

