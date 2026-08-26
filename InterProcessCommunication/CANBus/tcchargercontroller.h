#ifndef TCCHARGERCONTROLLER_H
#define TCCHARGERCONTROLLER_H

#include <QCanBusFrame>
#include <QMap>
#include <QObject>

class QCanBusDevice;
class QTimer;

class TcCharger;

class TcChargerController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int totalChargingPower READ totalChargingPower WRITE setTotalChargingPower NOTIFY
                   totalChargingPowerChanged)
public:
    TcChargerController(QCanBusDevice *device, QObject *parent = nullptr);
    ~TcChargerController();

    void addCharger(TcCharger *charger);

    int totalChargingPower() const;
    void setTotalChargingPower(int power);

Q_SIGNALS:
    void totalChargingPowerChanged(int power);

protected:
    void readCanFrames();

    void controlChargers();
    void shutdown();

private:
    QCanBusDevice *m_device = nullptr;
    int m_totalChargingPower = 0;
    QTimer *m_timer;
    QMap<QCanBusFrame::FrameId, TcCharger *> m_tcChargers;
};

#endif
