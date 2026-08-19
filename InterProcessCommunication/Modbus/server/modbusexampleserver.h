#ifndef MODBUSEXAMPLESERVER_H
#define MODBUSEXAMPLESERVER_H


#include <QModbusTcpServer>

class ModbusExampleServer : public QModbusTcpServer
{
    Q_OBJECT
public:
    explicit ModbusExampleServer(QObject* parent = nullptr);
    ~ModbusExampleServer();

protected:
    bool readData(QModbusDataUnit* newData) const override;
    bool writeData(const QModbusDataUnit& newData) override;

    bool readDataFromValue(QModbusDataUnit* newData, quint32 value, int size) const;
    bool writeDataToValue(const QModbusDataUnit& newData, quint32& value, int size);

private:
    const int m_maxCurrent = 32;
    int m_chargingCurrent = 16;
    qreal m_actualChargingCurrent = 7.2;
};

#endif
