#include "replaycanbusdevice.h"

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QTimer>

ReplayCanBusDevice::ReplayCanBusDevice(const QString &filename, QObject *parent)
    : QCanBusDevice(parent)
    , m_file(filename)
    , m_stream(&m_file)
{
}

ReplayCanBusDevice::~ReplayCanBusDevice() { }

bool ReplayCanBusDevice::open()
{
    setState(ConnectingState);
    bool opened = m_file.open(QFile::ReadOnly);
    if (!opened) {
        setState(UnconnectedState);
        return false;
    }

    // drop header
    m_stream.readLine();

    m_openingTimeStamp = QDateTime::currentDateTime().toMSecsSinceEpoch();

    setState(ConnectedState);

    QTimer::singleShot(0, this, [this] { readLineAndReceive(); });
    return true;
}

void ReplayCanBusDevice::close()
{
    setState(ClosingState);
    m_file.close();
    setState(UnconnectedState);
}

bool ReplayCanBusDevice::writeFrame(const QCanBusFrame &)
{
    return true;
}

QString ReplayCanBusDevice::interpretErrorFrame(const QCanBusFrame &frame)
{
    Q_UNUSED(frame)
    // we don't know about the actual contents...
    return {};
}

QList<QCanBusDeviceInfo> ReplayCanBusDevice::interfaces()
{
    QDir dir(":/logs");
    QList<QCanBusDeviceInfo> devices;
    for (const auto &entry : dir.entryInfoList()) {
        devices.append(
            QCanBusDevice::createDeviceInfo("replaycan", entry.absoluteFilePath(), true, false));
    }
    return devices;
}

void ReplayCanBusDevice::readLineAndReceive()
{
    if (m_stream.atEnd())
        return;

    auto line = m_stream.readLine();
    auto parts = line.split(",");
    qint64 timeStamp = parts[0].toInt() / 1000;
    QCanBusFrame::FrameId id = parts[1].toInt(nullptr, 16);
    int length = std::min<int>(parts[4].toInt(), parts.count() - 6);

    QByteArray payload;
    for (int i = 0; i < length; ++i) {
        payload += parts[5 + i].toInt(nullptr, 16);
    }

    qint64 msecsSinceOpening =
        QDateTime::currentDateTime().toMSecsSinceEpoch() - m_openingTimeStamp;
    qint64 msecsFromNow = std::max<qint64>(0, timeStamp - msecsSinceOpening);
    QCanBusFrame frame(id, payload);
    QTimer::singleShot(msecsFromNow, this, [frame, this] {
        enqueueReceivedFrames({frame});
        readLineAndReceive();
    });
}
