#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <QColor>
#include <QObject>

class QSerialPort;

class LedController : public QObject {

    Q_OBJECT

public:
    explicit LedController(const QString &deviceName, QObject *parent = nullptr);
    Q_INVOKABLE void setLED(int number, QColor color);
    Q_INVOKABLE void allOff();

private:
    void initLEDs();
    QSerialPort *m_serialPort;
};

#endif // LEDCONTROLLER_H
