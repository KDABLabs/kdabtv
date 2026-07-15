#include <StreamingPipeline.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QTemporaryDir>
#include <QFont>
#include <QDirIterator>


namespace {

QString extractWebRoot()
{
    QTemporaryDir dir;
    dir.setAutoRemove(false);

    QDirIterator it(QStringLiteral(":res/"));
    while (it.hasNext()) {
        it.next();
        const auto targetPath = dir.filePath(it.fileName());
        QFile::copy(it.filePath(), targetPath);
    }

    return dir.path();
}

void cleanupWebRoot(const QString& webRootPath)
{
    QDir(webRootPath).removeRecursively();
}

} // namespace

int main(int argc, char* argv[])
{
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QFont font("Poppins");
    font.setStyleHint(QFont::SansSerif);
    app.setFont(font);

    auto quickWindow = static_cast<QQuickWindow*>(engine.rootObjects().first());

    const auto webRootPath = extractWebRoot();

    StreamingPipeline pipeline(quickWindow, webRootPath);
    pipeline.start();

    const auto exitCode = app.exec();

    cleanupWebRoot(webRootPath);

    return exitCode;
}












