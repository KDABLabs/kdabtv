#include <QCoreApplication>

#include <QCanBus>
#include <QVariant>

#include "tccharger.h"
#include "tcchargercontroller.h"

// for development purposes, use fake device replaying a log
#define USE_REPLAY_DEVICE

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCanBusDevice *device = nullptr;

    // Try to load each and every supported CAN plugin, create devices and connect
    auto canbus = QCanBus::instance();
    QString errorMessage;
#ifdef USE_REPLAY_DEVICE
    device = canbus->createDevice("replaycan", ":/logs/can1.csv", &errorMessage);
#else
    device = canbus->createDevice("socket", "can0", &errorMessage);
#endif

    if (device == nullptr) {
        qWarning() << "Could not create a CAN bus device:" << errorMessage;
        return 1;
    }

    // initialize the bus with 250kBit/s
    device->setConfigurationParameter(QCanBusDevice::DataBitRateKey, 250000);

    // connnect the CAN bus device
    if (!device->connectDevice()) {
        qWarning() << "Could not connect to CAN bus device:" << device->errorString();
        return 2;
    }

    // TC charger controller, tells the TC charges how much to charge
    TcChargerController tcController(device);

    TcCharger charger1(0x18ff50e7, 0x1806e7f4);
    TcCharger charger2(0x18ff50e5, 0x1806e5f4);

    // Add two chargers, using different CAN IDs:
    tcController.addCharger(&charger1);
    tcController.addCharger(&charger2);

    // Simply charge with 4000W for this short demo.
    // Normally you would listen to a battery management system.
    tcController.setTotalChargingPower(4000);

    return app.exec();
}
