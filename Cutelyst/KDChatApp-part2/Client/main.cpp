#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "firebase.h"

#include <QLoggingCategory>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setOrganizationDomain("com.kdab");
    QCoreApplication::setOrganizationName("kdab");
    QCoreApplication::setApplicationName("KDChatApp");

    Firebase fb;
    qmlRegisterSingletonInstance("com.kdab", 1, 0, "Firebase", &fb);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
