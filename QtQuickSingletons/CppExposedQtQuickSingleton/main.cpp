#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "singleton.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto singleton = AppSingleton(&engine);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("com.kdab.qmlsingleton", "Main");

    return app.exec();
}
