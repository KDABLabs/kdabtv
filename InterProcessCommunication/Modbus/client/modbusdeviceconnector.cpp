#include "modbusdeviceconnector.h"

#include <QEventLoop>
#include <QModbusTcpClient>
#include <QTimer>
#include <QVariant>

#ifdef QT_SERIALPORT_LIB
#include <QModbusRtuSerialClient>
#endif


ModbusDeviceConnector::ModbusDeviceConnector(const QString& networkAddress, int networkPort, QObject* parent)
    : QObject(parent),
    m_modbusClient(new QModbusTcpClient(this))
{
    connect(m_modbusClient, &QModbusClient::stateChanged, [this] { emit connectedChanged(isConnected()); });

    m_modbusClient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, networkAddress);
    m_modbusClient->setConnectionParameter(QModbusDevice::NetworkPortParameter, networkPort);
}

#ifdef QT_SERIALPORT_LIB
ModbusDeviceConnector::ModbusDeviceConnector(const QString& serialPort, QSerialPort::Parity parity, QSerialPort::BaudRate baudRate, QSerialPort::DataBits dataBits, QSerialPort::StopBits stopBits, QObject* parent)
    : QObject(parent),
      m_modbusClient(new QModbusRtuSerialClient(this))
{
    connect(m_modbusClient, &QModbusClient::stateChanged, [this] { emit connectedChanged(isConnected()); });

    m_modbusClient->setConnectionParameter(QModbusDevice::SerialPortNameParameter, serialPort);
    m_modbusClient->setConnectionParameter(QModbusDevice::SerialParityParameter, parity);
    m_modbusClient->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, baudRate);
    m_modbusClient->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, dataBits);
    m_modbusClient->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, stopBits);
}
#endif

ModbusDeviceConnector::~ModbusDeviceConnector()
{
}

bool ModbusDeviceConnector::isConnected() const
{
    return m_modbusClient->state() == QModbusDevice::ConnectedState;
}

bool ModbusDeviceConnector::connectToDevice()
{
    return m_modbusClient->connectDevice();
}

int ModbusDeviceConnector::serverAddress() const
{
    return m_serverAddress;
}

void ModbusDeviceConnector::setServerAddress(int serverAddress)
{
    if (m_serverAddress == serverAddress)
        return;
    m_serverAddress = serverAddress;
    emit serverAddressChanged(serverAddress);
}

QString ModbusDeviceConnector::errorString() const
{
    return m_modbusClient->errorString();
}

void ModbusDeviceConnector::requestHoldingRegisterValues(int address, int size)
{
    QModbusDataUnit request(QModbusDataUnit::HoldingRegisters, address, size);
    QModbusReply* reply = m_modbusClient->sendReadRequest(request, m_serverAddress);
    QEventLoop loop;
    connect(reply, &QModbusReply::finished, this, [reply, this, address, &loop] {
        loop.quit();
        if (reply->result().isValid()) {
            emit receivedHoldingRegisterValues(reply->result().values(), address, reply->result().valueCount());
        }
        else {
            emit receiveHoldingRegisterValuesFailed(reply->errorString());
        }
        reply->deleteLater();
    });
    loop.exec();
}

void ModbusDeviceConnector::setHoldingRegisterValues(int address, const QList<quint16> &values)
{
    QModbusDataUnit request(QModbusDataUnit::HoldingRegisters, address, values.size());
    request.setValues(values);
    QModbusReply* reply = m_modbusClient->sendWriteRequest(request, m_serverAddress);
    connect(reply, &QModbusReply::finished, this, [reply] {
        //qDebug() << reply->errorString();
        reply->deleteLater();
    });
}

