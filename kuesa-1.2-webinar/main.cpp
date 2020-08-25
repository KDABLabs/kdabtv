#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <projectcoordinateshelper.h>
#include <QDir>

int main(int ac, char **av)
{
    // Set OpenGL requirements for Qt3D
    {
        QSurfaceFormat format = QSurfaceFormat::defaultFormat();
        format.setVersion(4, 1);
        format.setProfile(QSurfaceFormat::CoreProfile);
        // Requests Anti Aliasing
        format.setSamples(4);
        QSurfaceFormat::setDefaultFormat(format);
    }

    QGuiApplication app(ac, av);
    QQuickView view;

    qmlRegisterType<ProjectCoordinatesHelper>("Helpers", 1, 0, "ProjectionHelper");
    view.rootContext()->setContextProperty(QStringLiteral("_assetPath"), QDir(ASSETS).path());

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    view.resize(1920, 1080);
    view.show();

    return app.exec();
}
