#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "rep_Sensors_replica.h"

int main(
    int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<SensorsReplica>("Sensors", 1, 0, "SensorsReplica");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qtro_ac_qml", "Main");

    return app.exec();
}
