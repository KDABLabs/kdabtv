#include "ledcontroller.h"

#include <QColor>
#include <QtSerialPort>

LedController::LedController(const QString& deviceName, QObject *parent) : QObject(parent) {

    m_serialPort = new QSerialPort(deviceName);
    m_serialPort->setBaudRate(QSerialPort::Baud115200);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
    if (!m_serialPort->open(QSerialPort::ReadWrite)) {
        qWarning() << "cannot open serialport: " << m_serialPort->errorString();
    } else {
        qWarning() << "opened serialport";
    }

    initLEDs();
}

void LedController::setLED(int number, QColor color) {

    const QByteArray starterByte = "\xb4";
    m_serialPort->write(starterByte, 1);

    QByteArray ledID ;
    ledID[0] = number;
    m_serialPort->write(ledID, 1);

    QByteArray colorData;
    colorData.push_back(color.red());
    colorData.push_back(color.green());
    colorData.push_back(color.blue());
    m_serialPort->write(colorData, 3);
    m_serialPort->flush();

    m_serialPort->waitForBytesWritten(0);
}

void LedController::allOff()
{
    initLEDs();
}

void LedController::initLEDs() {
    for (int i = 0; i < 100; i++) {
        setLED(i % 12, QColor(0, 0, 0));
    }
}
