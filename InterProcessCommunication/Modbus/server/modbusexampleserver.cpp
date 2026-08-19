#include "modbusexampleserver.h"

ModbusExampleServer::ModbusExampleServer(QObject *parent)
    : QModbusTcpServer(parent)
{
}

ModbusExampleServer::~ModbusExampleServer()
{
}

bool ModbusExampleServer::readData(QModbusDataUnit *newData) const
{
    // Provide the data for the holding registers.
    // Altenatively could use QModbusServer::setData to set a mapping
    switch (newData->registerType()) {
    case QModbusDataUnit::HoldingRegisters:
    {
        const int startAddress = newData->startAddress();
        const int length = newData->valueCount();
        QList<quint16> values(length, 0);

        switch (startAddress) {
        case 1100:
            return readDataFromValue(newData, m_chargingCurrent * 1000, 2);
        case 1110:
            return readDataFromValue(newData, m_maxCurrent * 1000, 2);
        case 1008:
            return readDataFromValue(newData, m_actualChargingCurrent * 1000, 2);
        default:
            return false;
        }
    }
    default:
        return false;
    }
}

bool ModbusExampleServer::writeData(const QModbusDataUnit &newData)
{
    switch (newData.registerType()) {
    case QModbusDataUnit::HoldingRegisters:
    {
        const int startAddress = newData.startAddress();
        const int length = newData.valueCount() - 1;
        const QList<quint16> values = newData.values();

        // setting charging current - 5004
        if (startAddress == 5004 && length == 1) {
            m_chargingCurrent = values[0];
            return true;
        }
        break;
    }
    default:
        return false;
    }
    return false;
}

bool ModbusExampleServer::readDataFromValue(QModbusDataUnit *newData, quint32 value, int size) const
{
    if (newData->valueCount() != size) {
        return false;
    }

    QList<quint16> values(size, 0);
    if (size == 2) {
        values[0] = (value & 0xffff0000) >> 16;
        values[1] = value & 0x0000ffff;
    }
    else {
        // other sizes currently not needed
        return false;
    }

    newData->setValues(values);
    return true;
}

bool ModbusExampleServer::writeDataToValue(const QModbusDataUnit &newData, quint32 &value, int size)
{
    if (newData.valueCount() != size) {
        return false;
    }

    const auto values = newData.values();

    if (size == 1) {
        value = values[0];
        return true;
    }
    else if (value == 2) {
        value = static_cast<quint32>(values[0]) << 16 | values[1];
        return true;
    }
    else {
        // other sizes current not needed
        return false;
    }
}
