#include "p30evseconnector.h"

#include <QDebug>
#include <QEventLoop>
#include <QTimer>

// See https://www.keba.com/download/x/dea7ae6b84/kecontactp30modbustcp_pgen.pdf
enum class P30EVSEDataField {
    ChargingState = 1000,
    CableState = 1004,
    ErrorCode = 1006,
    CurrentL1 = 1008,
    CurrentL2 = 1010,
    CurrentL3 = 1012,
    SerialNumber = 1014,
    FirmwareVersion = 1018,
    ActivePower = 1020,
    TotalEnergy = 1036,
    VoltageL1 = 1040,
    VoltageL2 = 1042,
    VoltageL3 = 1044,
    PowerFactor = 1046,
    MaxChargingCurrent = 1100,
    MaxSupportedCurrent = 1110,
    ChargedEnergy = 1502
};

P30EVSEConnector::P30EVSEConnector(const QString& networkAddress, int networkPort, QObject* parent)
    : ModbusDeviceConnector(networkAddress, networkPort, parent)
{
    auto collectTimer = new QTimer(this);
    connect(collectTimer, &QTimer::timeout, this, &P30EVSEConnector::collectValues);

    connect(this, &ModbusDeviceConnector::connectedChanged, this, [this, collectTimer](bool connected) {
        if (connected) {
            collectValues();
            collectTimer->start(1000);
        }
        else {
            collectTimer->stop();
        }
    });

    connect(this, &ModbusDeviceConnector::receivedHoldingRegisterValues, this, &P30EVSEConnector::receivedValues);
    connect(this, &ModbusDeviceConnector::receiveHoldingRegisterValuesFailed, this, &P30EVSEConnector::receiveFailed);
}

P30EVSEConnector::~P30EVSEConnector()
{
}

P30EVSEConnector::ChargingState P30EVSEConnector::chargingState() const
{
    return m_chargingState;
}

P30EVSEConnector::CableState P30EVSEConnector::cableState() const
{
    return m_cableState;
}

int P30EVSEConnector::errorCode() const
{
    return m_errorCode;
}

qreal P30EVSEConnector::currentL1() const
{
    return m_currentL1;
}

qreal P30EVSEConnector::currentL2() const
{
    return m_currentL2;
}

qreal P30EVSEConnector::currentL3() const
{
    return m_currentL3;
}

quint32 P30EVSEConnector::serialNumber() const
{
    return m_serialNumber;
}

QString P30EVSEConnector::firmwareVersion() const
{
    return m_firmwareVersion;
}

qreal P30EVSEConnector::activePower() const
{
    return m_activePower;
}

qreal P30EVSEConnector::totalEnergy() const
{
    return m_totalEnergy;
}

quint32 P30EVSEConnector::voltageL1() const
{
    return m_voltageL1;
}

quint32 P30EVSEConnector::voltageL2() const
{
    return m_voltageL2;
}

quint32 P30EVSEConnector::voltageL3() const
{
    return m_voltageL3;
}

qreal P30EVSEConnector::powerFactor() const
{
    return m_powerFactor;
}

qreal P30EVSEConnector::maxChargingCurrent() const
{
    return m_maxChargingCurrent;
}

void P30EVSEConnector::setMaxChargingCurrent(qreal maxChargingCurrent)
{
    setHoldingRegisterValues(5004, { static_cast<quint16>(maxChargingCurrent * 1000) });
}

qreal P30EVSEConnector::maxSupportedCurrent() const
{
    return m_maxSupportedCurrent;
}

qreal P30EVSEConnector::chargedEnergy() const
{
    return m_chargedEnergy;
}

void P30EVSEConnector::collectValues()
{
    m_requestedValues = true;
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::ChargingState), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::CableState), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::ErrorCode), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::CurrentL1), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::CurrentL2), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::CurrentL3), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::SerialNumber), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::FirmwareVersion), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::ActivePower), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::TotalEnergy), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::VoltageL1), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::VoltageL2), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::VoltageL3), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::PowerFactor), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::MaxChargingCurrent), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::MaxSupportedCurrent), 2);
    requestHoldingRegisterValues(static_cast<int>(P30EVSEDataField::ChargedEnergy), 2);

    emit receivedNewValues();
}


namespace {

quint32 readUint32(const QList<quint16>& rawValues)
{
    Q_ASSERT(rawValues.count() == 2);
    return quint32(rawValues[0]) << 16 | rawValues[1];
}

qreal readDouble(const QList<quint16>& rawValues, int factor)
{
    return readUint32(rawValues) / qreal(factor);
}

QString readFirmwareVersion(const QList<quint16>& rawValues)
{
    Q_ASSERT(rawValues.count() == 2);
    const quint32 value = readUint32(rawValues);
    return QString("%1.%2.%3").arg((value & 0xff000000) >> 24)
        .arg((value & 0x00ff0000) >> 16)
        .arg((value & 0x0000ff00) >> 8);
}

}

void P30EVSEConnector::receivedValues(const QList<quint16> &values, int address)
{
    switch (static_cast<P30EVSEDataField>(address)) {
    case P30EVSEDataField::ChargingState:
    {
        const auto state = static_cast<ChargingState>(readUint32(values));
        if (m_chargingState != state) {
            m_chargingState = state;
            emit chargingStateChanged(state);
        }
        break;
    }

    case P30EVSEDataField::CableState:
    {
        const auto state = static_cast<CableState>(readUint32(values));
        if (m_cableState != state) {
            m_cableState = state;
            emit cableStateChanged(state);
        }
        break;
    }

    case P30EVSEDataField::ErrorCode:
    {
        const auto errorCode = readUint32(values);
        if (m_errorCode != errorCode) {
            m_errorCode = errorCode;
            emit errorCodeChanged(errorCode);
        }
        break;
    }

    case P30EVSEDataField::CurrentL1:
    {
        const auto current = readDouble(values, 1000);
        if (m_currentL1 != current) {
            m_currentL1 = current;
            emit currentL1Changed(current);
        }
        break;
    }

    case P30EVSEDataField::CurrentL2:
    {
        const auto current = readDouble(values, 1000);
        if (m_currentL2 != current) {
            m_currentL2 = current;
            emit currentL2Changed(current);
        }
        break;
    }

    case P30EVSEDataField::CurrentL3:
    {
        const auto current = readDouble(values, 1000);
        if (m_currentL3 != current) {
            m_currentL3 = current;
            emit currentL3Changed(current);
        }
        break;
    }

    case P30EVSEDataField::SerialNumber:
    {
        const auto serialNumber = readUint32(values);
        if (m_serialNumber != serialNumber) {
            m_serialNumber = serialNumber;
            emit serialNumberChanged(serialNumber);
        }
        break;
    }

    case P30EVSEDataField::FirmwareVersion:
    {
        const auto firmwareVersion = readFirmwareVersion(values);
        if (m_firmwareVersion != firmwareVersion) {
            m_firmwareVersion = firmwareVersion;
            emit firmwareVersionChanged(firmwareVersion);
        }
        break;
    }

    case P30EVSEDataField::ActivePower:
    {
        const auto activePower = readDouble(values, 1000);
        if (m_activePower != activePower) {
            m_activePower = activePower;
            emit activePowerChanged(activePower);
        }
    }

    case P30EVSEDataField::TotalEnergy:
    {
        const auto totalEnergy = readDouble(values, 10000);
        if (m_totalEnergy != totalEnergy) {
            m_totalEnergy = totalEnergy;
            emit totalEnergyChanged(totalEnergy);
        }
        break;
    }

    case P30EVSEDataField::VoltageL1:
    {
        const auto voltage = readUint32(values);
        if (m_voltageL1 != voltage) {
            m_voltageL1 = voltage;
            emit voltageL1Changed(voltage);
        }
        break;
    }

    case P30EVSEDataField::VoltageL2:
    {
        const auto voltage = readUint32(values);
        if (m_voltageL2 != voltage) {
            m_voltageL2 = voltage;
            emit voltageL2Changed(voltage);
        }
        break;
    }

    case P30EVSEDataField::VoltageL3:
    {
        const auto voltage = readUint32(values);
        if (m_voltageL3 != voltage) {
            m_voltageL3 = voltage;
            emit voltageL3Changed(voltage);
        }
        break;
    }

    case P30EVSEDataField::PowerFactor:
    {
        const auto powerFactor = readDouble(values, 10);
        if (m_powerFactor != powerFactor) {
            m_powerFactor = powerFactor;
            emit powerFactorChanged(powerFactor);
        }
        break;
    }

    case P30EVSEDataField::MaxChargingCurrent:
    {
        const auto maxChargingCurrent = readDouble(values, 1000);
        if (m_maxChargingCurrent != maxChargingCurrent) {
            m_maxChargingCurrent = maxChargingCurrent;
            emit maxChargingCurrentChanged(maxChargingCurrent);
        }
        break;
    }

    case P30EVSEDataField::MaxSupportedCurrent:
    {
        const auto maxSupportedCurrent = readDouble(values, 1000);
        if (m_maxSupportedCurrent != maxSupportedCurrent) {
            m_maxSupportedCurrent = maxSupportedCurrent;
            emit maxSupportedCurrentChanged(maxSupportedCurrent);
        }
        break;
    }

    case P30EVSEDataField::ChargedEnergy:
    {
        const auto chargedEnergy = readDouble(values, 10000);
        if (m_chargedEnergy != chargedEnergy) {
            m_chargedEnergy = chargedEnergy;
            emit chargedEnergyChanged(chargedEnergy);
        }
        break;
    }
    }
}

void P30EVSEConnector::receiveFailed(const QString &error)
{
    qDebug() << "P30EVSEConnector received failed:" << error;
}
