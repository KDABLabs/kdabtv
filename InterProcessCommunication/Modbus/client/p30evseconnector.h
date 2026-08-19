#ifndef P30EVSECONNECTOR_H
#define P30EVSECONNECTOR_H

#include "modbusdeviceconnector.h"

class P30EVSEConnector : public ModbusDeviceConnector
{
    Q_OBJECT
    Q_PROPERTY(ChargingState chargingState READ chargingState NOTIFY chargingStateChanged)
    Q_PROPERTY(CableState cableState READ cableState NOTIFY cableStateChanged)
    Q_PROPERTY(int errorCode READ errorCode NOTIFY errorCodeChanged)
    Q_PROPERTY(qreal currentL1 READ currentL1 NOTIFY currentL1Changed)
    Q_PROPERTY(qreal currentL2 READ currentL2 NOTIFY currentL2Changed)
    Q_PROPERTY(qreal currentL3 READ currentL3 NOTIFY currentL3Changed)
    Q_PROPERTY(quint32 serialNumber READ serialNumber NOTIFY serialNumberChanged)
    Q_PROPERTY(QString firmwareVersion READ firmwareVersion NOTIFY firmwareVersionChanged)
    Q_PROPERTY(qreal activePower READ activePower NOTIFY activePowerChanged)
    Q_PROPERTY(qreal totalEnergy READ totalEnergy NOTIFY totalEnergyChanged)
    Q_PROPERTY(quint32 voltageL1 READ voltageL1 NOTIFY voltageL1Changed)
    Q_PROPERTY(quint32 voltageL2 READ voltageL1 NOTIFY voltageL2Changed)
    Q_PROPERTY(quint32 voltageL3 READ voltageL1 NOTIFY voltageL3Changed)
    Q_PROPERTY(qreal powerFactor READ powerFactor NOTIFY powerFactorChanged)
    Q_PROPERTY(qreal maxChargingCurrent READ maxChargingCurrent WRITE setMaxChargingCurrent NOTIFY maxChargingCurrentChanged)
    Q_PROPERTY(qreal maxSupportedCurrent READ maxSupportedCurrent NOTIFY maxSupportedCurrentChanged)
    Q_PROPERTY(qreal chargedEnergy READ chargedEnergy NOTIFY chargedEnergyChanged)

public:
    enum class ChargingState {
        Startup = 0,
        NotReady = 1,
        Ready = 2,
        Charging = 3,
        Error = 4,
        Suspended = 5
    };
    Q_ENUM(ChargingState)
    enum class CableState {
        NotConnected = 0,
        CableConnected = 1,
        CableConnectedAndLocked = 3,
        EVConnected = 5,
        EVConnectedAndLocked = 7
    };
    Q_ENUM(CableState)

    P30EVSEConnector(const QString& address, int port, QObject* parent = nullptr);
    ~P30EVSEConnector();

    ChargingState chargingState() const;
    CableState cableState() const;
    int errorCode() const;
    qreal currentL1() const;
    qreal currentL2() const;
    qreal currentL3() const;
    quint32 serialNumber() const;
    QString firmwareVersion() const;
    qreal activePower() const;
    qreal totalEnergy() const;
    quint32 voltageL1() const;
    quint32 voltageL2() const;
    quint32 voltageL3() const;
    qreal powerFactor() const;
    qreal maxChargingCurrent() const;
    void setMaxChargingCurrent(qreal maxChargingCurrent);
    qreal maxSupportedCurrent() const;
    qreal chargedEnergy() const;

signals:
    void chargingStateChanged(ChargingState chargingState);
    void cableStateChanged(CableState cableState);
    void errorCodeChanged(int errorCode);
    void currentL1Changed(qreal currentL1);
    void currentL2Changed(qreal currentL2);
    void currentL3Changed(qreal currentL3);
    void serialNumberChanged(quint32 serialNumber);
    void firmwareVersionChanged(const QString& firmwareVersion);
    void activePowerChanged(qreal activePower);
    void totalEnergyChanged(qreal totalEnergy);
    void voltageL1Changed(quint32 voltageL1);
    void voltageL2Changed(quint32 voltageL2);
    void voltageL3Changed(quint32 voltageL3);
    void powerFactorChanged(qreal powerFactor);
    void maxChargingCurrentChanged(qreal maxChargingCurrent);
    void maxSupportedCurrentChanged(qreal maxSupportedCurrent);
    void chargedEnergyChanged(qreal chargedEnergy);

    void receivedNewValues();

protected:
    void collectValues();
    void receivedValues(const QList<quint16>& values, int address);
    void receiveFailed(const QString& error);

private:
    bool m_requestedValues = false;

    ChargingState m_chargingState = ChargingState::NotReady;
    CableState m_cableState = CableState::NotConnected;
    int m_errorCode = 0;
    qreal m_currentL1 = 0.0;
    qreal m_currentL2 = 0.0;
    qreal m_currentL3 = 0.0;
    quint32 m_serialNumber = 0;
    QString m_firmwareVersion;
    qreal m_activePower = 0.0;
    qreal m_totalEnergy = 0.0;
    quint32 m_voltageL1 = 0;
    quint32 m_voltageL2 = 0;
    quint32 m_voltageL3 = 0;
    qreal m_powerFactor = 0.0;
    qreal m_maxChargingCurrent = 0.0;
    qreal m_maxSupportedCurrent = 0.0;
    qreal m_chargedEnergy = 0.0;
};

#endif
