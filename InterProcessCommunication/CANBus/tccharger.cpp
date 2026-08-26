#include "tccharger.h"

#include <QCanBusFrame>
#include <QDebug>
#include <QTimer>

TcCharger::TcCharger(QCanBusFrame::FrameId frameIdReceiving, QCanBusFrame::FrameId frameIdSending,
                     QObject *parent)
    : QObject(parent)
    , m_frameIdReceiving(frameIdReceiving)
    , m_frameIdSending(frameIdSending)
{
    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &TcCharger::prepareAndSendFrame);
    t->start(1000);
}

double TcCharger::outputVoltage() const
{
    return m_outputVoltage / 10.0;
}

double TcCharger::outputCurrent() const
{
    return m_outputCurrent / 10.0;
}

double TcCharger::maxOutputVoltage() const
{
    return m_maxOutputVoltage / 10.0;
}

void TcCharger::setMaxOutputVoltage(double voltage)
{
    quint16 max = voltage * 10;
    if (max == m_maxOutputVoltage)
        return;
    m_maxOutputVoltage = max;
    Q_EMIT maxOutputVoltageChanged(maxOutputVoltage());
    prepareAndSendFrame();
}

double TcCharger::maxOutputCurrent() const
{
    return m_maxOutputCurrent / 10.;
}

void TcCharger::setMaxOutputCurrent(double current)
{
    quint16 max = current * 10;
    if (max == m_maxOutputCurrent)
        return;
    m_maxOutputCurrent = max;
    Q_EMIT maxOutputCurrentChanged(maxOutputCurrent());
    prepareAndSendFrame();
}

QCanBusFrame::FrameId TcCharger::frameIdReceiving() const
{
    return m_frameIdReceiving;
}

QCanBusFrame::FrameId TcCharger::frameIdSending() const
{
    return m_frameIdSending;
}

void TcCharger::setDevice(QCanBusDevice *device)
{
    m_canBusDevice = device;
}

TcCharger::StatusFlags TcCharger::status() const
{
    return m_status;
}

void TcCharger::prepareAndSendFrame()
{
    auto highByte = [](quint16 data) -> quint8 { return (data >> 8) & 0xff; };
    auto lowByte = [](quint16 data) -> quint8 { return data & 0xff; };
    QByteArray data(8, '\0');
    data[0] = highByte(m_maxOutputVoltage);
    data[1] = lowByte(m_maxOutputVoltage);
    data[2] = highByte(m_maxOutputCurrent);
    data[3] = lowByte(m_maxOutputCurrent);

    const QCanBusFrame frame(m_frameIdSending, data);
    m_canBusDevice->writeFrame(frame);
}

void TcCharger::receiveFrame(const QCanBusFrame &frame)
{
    Q_ASSERT(frame.frameId() == m_frameIdReceiving);

    const QByteArray data = frame.payload();

    const quint16 newOutputVoltage = data[0] * 255 + data[1];
    const quint16 newOutputCurrent = data[2] * 255 + data[3];
    StatusFlags newStatus = static_cast<StatusFlags>(data[4]);
    if (newOutputVoltage != m_outputVoltage) {
        m_outputVoltage = newOutputVoltage;
        Q_EMIT outputVoltageChanged(outputVoltage());
    }
    if (newOutputCurrent != m_outputCurrent) {
        m_outputCurrent = newOutputCurrent;
        Q_EMIT outputCurrentChanged(outputCurrent());
    }
    if (newStatus != m_status) {
        m_status = newStatus;
        Q_EMIT statusChanged(status());
    }
}
