#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    QFontDatabase::addApplicationFont(":/qt/qml/WidgetWindowsInQtQuickApp/fonts/OpenSans-Regular.ttf");
    engine.loadFromModule("WidgetWindowsInQtQuickApp", "Main");

    return app.exec();
}
