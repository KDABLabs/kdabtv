#include <QCoreApplication>

#include "p30evseconnector.h"

#include <QDebug>
#include <QMetaProperty>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    // Connect to the EVSE running here:
    P30EVSEConnector evse("127.0.0.1", 1502);
    if (!evse.connectToDevice()) {
        qDebug() << "Could not connect to EVSE. The error message was:" << evse.errorString();
        return -1;
    }

    // Let's wait for the connection and the first values to be fetched
    QMetaObject::Connection connection = QObject::connect(&evse, &P30EVSEConnector::receivedNewValues, [&] {
        // now print all known values
        for (int i = 0; i < evse.metaObject()->propertyCount(); ++i) {
            const auto prop = evse.metaObject()->property(i);
            const auto propname = prop.name();
            qDebug() << propname << evse.property(propname).toString();
        }
        // just once, for demonstration purposes. Disconnect afterwards.
        QObject::disconnect(connection);
    });


    // connect to the actual charging current (L1) and print on each change
    QObject::connect(&evse, &P30EVSEConnector::currentL1Changed, [](qreal current) {
        qDebug() << "Charging current L1 (A)" << current;
    });

    return app.exec();
}
