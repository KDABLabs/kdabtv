#include "ledcontroller.h"
#include "hotreload.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QThread>
#include <QtSerialPort/QSerialPort>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    LedController ledController("ttyUSB0");
    engine.rootContext()->setContextProperty("_ledController", &ledController);

    Hotreload hotreload(engine, "qml/");
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

    return app.exec();
}
