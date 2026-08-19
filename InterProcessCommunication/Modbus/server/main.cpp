#include <QCoreApplication>
#include <QModbusTcpServer>
#include <QDebug>

#include "modbusexampleserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ModbusExampleServer modbusServer;
    modbusServer.setConnectionParameter(QModbusServer::NetworkAddressParameter, "127.0.0.1");
    modbusServer.setConnectionParameter(QModbusServer::NetworkPortParameter, 1502);
    modbusServer.setServerAddress(1);

    /*
     Could also used fixed data mapping... (if the example server didn't override read/writeData)
    */
    /*QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10 });
    reg.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 10 });
    reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 10 });
    reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 10 });
    modbusServer->setMap(reg);
    */

    if (!modbusServer.connectDevice()) {
        qDebug() << "Could not start ModbusExampleServer";
        return -1;
    }

    return a.exec();
}
