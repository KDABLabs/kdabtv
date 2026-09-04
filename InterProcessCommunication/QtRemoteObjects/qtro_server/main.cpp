#include <QCoreApplication>
#include <QRemoteObjectHost>

#include "sensors.h"

using namespace Qt::StringLiterals;

int main(
    int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Sensors sensors;
    QRemoteObjectHost localServer{QUrl{u"local:replica"_s}};
    localServer.enableRemoting<SensorsSourceAPI>(&sensors);
    QRemoteObjectHost tcpServer{QUrl{u"tcp://172.16.224.82:4321"_s}};
    tcpServer.enableRemoting<SensorsSourceAPI>(&sensors);
    return a.exec();
}
