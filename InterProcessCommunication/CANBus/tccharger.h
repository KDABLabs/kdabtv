#ifndef TCCHARGER_H
#define TCCHARGER_H

#include <QCanBusDevice>
#include <QCanBusFrame>

class TcCharger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double outputVoltage READ outputVoltage NOTIFY outputVoltageChanged)
    Q_PROPERTY(double outputCurrent READ outputCurrent NOTIFY outputCurrentChanged)
    Q_PROPERTY(double maxOutputVoltage READ maxOutputVoltage WRITE setMaxOutputVoltage NOTIFY
                   maxOutputVoltageChanged)
    Q_PROPERTY(double maxOutputCurrent READ maxOutputCurrent WRITE setMaxOutputCurrent NOTIFY
                   maxOutputCurrentChanged)
    Q_PROPERTY(StatusFlags status READ status NOTIFY statusChanged)
public:
    TcCharger(QCanBusFrame::FrameId frameIdReceiving, QCanBusFrame::FrameId frameIdSending,
              QObject *parent = nullptr);
    ~TcCharger() = default;

    enum StatusFlag {
        Normal = 0x0,
        HardwareFailure = 0x1,
        OverTemperatureProtection = 0x2,
        IncorrectInputVoltage = 0x04,
        BatteryDisconnectedOrReversed = 0x08,
        CommunicationTimeout = 0x10
    };
    Q_DECLARE_FLAGS(StatusFlags, StatusFlag)
    Q_FLAG(StatusFlag)

    double outputVoltage() const;
    double outputCurrent() const;

    double maxOutputVoltage() const;
    void setMaxOutputVoltage(double voltage);

    double maxOutputCurrent() const;
    void setMaxOutputCurrent(double current);

    StatusFlags status() const;

    QCanBusFrame::FrameId frameIdReceiving() const;
    QCanBusFrame::FrameId frameIdSending() const;

Q_SIGNALS:
    void outputVoltageChanged(double voltage);
    void outputCurrentChanged(double current);
    void maxOutputVoltageChanged(double voltage);
    void maxOutputCurrentChanged(double current);
    void statusChanged(StatusFlags status);

protected:
    void setDevice(QCanBusDevice *device);
    void prepareAndSendFrame();
    void receiveFrame(const QCanBusFrame &frame);

private:
    QCanBusDevice *m_canBusDevice = nullptr;
    QCanBusFrame::FrameId m_frameIdReceiving = 0;
    QCanBusFrame::FrameId m_frameIdSending = 0;

    quint16 m_outputVoltage = 0;
    quint16 m_outputCurrent = 0;
    quint16 m_maxOutputVoltage = 0;
    quint16 m_maxOutputCurrent = 0;

    StatusFlags m_status = CommunicationTimeout;

    friend class TcChargerController;
};

#endif
