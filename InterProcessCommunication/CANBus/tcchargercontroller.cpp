#include "tcchargercontroller.h"

#include "tccharger.h"

#include <QCanBusDevice>
#include <QDebug>
#include <QTimer>

TcChargerController::TcChargerController(QCanBusDevice *device, QObject *parent)
    : QObject(parent)
    , m_device(device)
    , m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &TcChargerController::controlChargers);

    // TcChargerController will receive the CAN frames and will forward them to the respective
    // charger
    connect(device, &QCanBusDevice::framesReceived, this, &TcChargerController::readCanFrames);
}

TcChargerController::~TcChargerController()
{
    shutdown();
}

void TcChargerController::addCharger(TcCharger *charger)
{
    m_tcChargers[charger->frameIdReceiving()] = charger;
    charger->setDevice(m_device);
    controlChargers();
    if (!m_timer->isActive())
        m_timer->start(1000);
}

int TcChargerController::totalChargingPower() const
{
    return m_totalChargingPower;
}

void TcChargerController::setTotalChargingPower(int power)
{
    if (m_totalChargingPower == power)
        return;
    m_totalChargingPower = power;
    Q_EMIT totalChargingPowerChanged(power);
    controlChargers();
}

void TcChargerController::readCanFrames()
{
    // Read all available CAN frames and forward them
    const QList<QCanBusFrame> allFrames = m_device->readAllFrames();
    for (const QCanBusFrame &frame : allFrames) {
        TcCharger *charger = m_tcChargers.value(frame.frameId());
        if (charger != nullptr) {
            charger->receiveFrame(frame);
        }
    }
}

void TcChargerController::shutdown()
{
    m_timer->stop();
    for (auto charger : std::as_const(m_tcChargers)) {
        charger->setMaxOutputVoltage(0);
        charger->setMaxOutputCurrent(0);
    }
}

void TcChargerController::controlChargers()
{
    if (m_tcChargers.isEmpty()) {
        shutdown();
        return;
    }

    const quint32 tcChargerPower = m_totalChargingPower / m_tcChargers.count();

    qDebug() << "Max total charging power: " << m_totalChargingPower << "W";
    qDebug() << "Setting TC charger(s) (" << m_tcChargers.count() << ") power to" << tcChargerPower
             << "W each";
    qDebug() << "";

    for (auto charger : std::as_const(m_tcChargers)) {
        if (charger->status() != TcCharger::Normal)
            qDebug() << "Charger state not normal:" << charger << charger->status();

        // Set the new charger parameters - the TcCharger class will send CAN frames to the device
        charger->setMaxOutputVoltage(435);
        charger->setMaxOutputCurrent(tcChargerPower / charger->outputVoltage());
    }
}
