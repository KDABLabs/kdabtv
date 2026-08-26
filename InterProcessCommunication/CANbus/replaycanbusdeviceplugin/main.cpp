#include <QCanBusFactory>
#include <QObject>

#include <QFileInfo>

#include "replaycanbusdevice.h"

class ReplayCanBusDevicePlugin : public QObject, public QCanBusFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCanBusFactory" FILE "plugin.json")
    Q_INTERFACES(QCanBusFactory)

public:
    QList<QCanBusDeviceInfo> availableDevices(QString *) const override
    {
        return ReplayCanBusDevice::interfaces();
    }

    QCanBusDevice *createDevice(const QString &interfaceName, QString *errorMessage) const override
    {
        Q_UNUSED(errorMessage)
        if (!QFile(interfaceName).exists()) {
            if (errorMessage)
                *errorMessage = tr("No such file or directory file: '%1'").arg(interfaceName);
            return nullptr;
        }
        return new ReplayCanBusDevice(interfaceName);
    }
};

#include "main.moc"
