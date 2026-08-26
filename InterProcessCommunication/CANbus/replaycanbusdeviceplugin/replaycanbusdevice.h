#pragma once

#include <QCanBusDevice>
#include <QFile>
#include <QTextStream>

class ReplayCanBusDevice : public QCanBusDevice
{
    Q_OBJECT
public:
    explicit ReplayCanBusDevice(const QString &filename, QObject *parent = nullptr);
    ~ReplayCanBusDevice();

    bool writeFrame(const QCanBusFrame &frame) override;

    QString interpretErrorFrame(const QCanBusFrame &frame) override;

    static QList<QCanBusDeviceInfo> interfaces();

protected:
    bool open() override;
    void close() override;

    void readLineAndReceive();

private:
    qint64 m_openingTimeStamp = -1;
    QFile m_file;
    QTextStream m_stream;
};
