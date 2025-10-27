#include "ledcontroller.h"
#include "hotreload.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QWindow>

#include <Spix/AnyRpcServer.h>
#include <Spix/QtQmlBot.h>


int main(int argc, char *argv[]) {
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    LedController ledController("ttyUSB0");
    engine.rootContext()->setContextProperty("_ledController", &ledController);

    Hotreload hotreload(engine, "../../qml/");
    engine.rootContext()->setContextProperty("_hotreload", &hotreload);
    engine.rootContext()->setContextProperty("_qmlPath", QGuiApplication::applicationDirPath() + "/qml/");

    //set all off after hotreload
    QObject::connect(&hotreload, &Hotreload::watchedSourceChanged, &ledController, [&ledController](){ledController.allOff();});

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    //Start the actual Runner/Server
    spix::AnyRpcServer server;
    auto bot = new spix::QtQmlBot();
    bot->runTestServer(server);

    //Name the MainWindow "root" to be found
    QWindow* window = qobject_cast<QWindow*>(engine.rootObjects().at(0));
    window->setObjectName("mainWindow");

    return app.exec();
}
