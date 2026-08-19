#ifndef MODBUSDEVICECONNECTOR_H
#define MODBUSDEVICECONNECTOR_H

#include <QObject>

#ifdef QT_SERIALPORT_LIB
#include <QSerialPort>
#endif

class QModbusClient;

class ModbusDeviceConnector : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
    Q_PROPERTY(int serverAddress READ serverAddress WRITE setServerAddress NOTIFY serverAddressChanged)
    Q_PROPERTY(QString errorString READ errorString)
public:
    ModbusDeviceConnector(const QString& address, int port, QObject* parent = nullptr);
#ifdef QT_SERIALPORT_LIB
    ModbusDeviceConnector(const QString& serialPort, QSerialPort::Parity parity, QSerialPort::BaudRate baudrate, QSerialPort::DataBits databits, QSerialPort::StopBits stopbits, QObject* parent = nullptr);
#endif
    ~ModbusDeviceConnector();

    bool isConnected() const;

    bool connectToDevice();

    int serverAddress() const;
    void setServerAddress(int serverAddress);

    QString errorString() const;

signals:
    void connectedChanged(bool connected);
    void serverAddressChanged(int serverAddress);

protected:
    void requestHoldingRegisterValues(int address, int size);
    void setHoldingRegisterValues(int address, const QList<quint16>& values);

signals:
    void receivedHoldingRegisterValues(const QList<quint16>& values, int address, int size);
    void receiveHoldingRegisterValuesFailed(const QString& errorString);

private:
    QModbusClient* m_modbusClient;
    int m_serverAddress = 1;
};

#endif
