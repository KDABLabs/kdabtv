#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QSerialPort>

class CommandInterface : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
    Q_PROPERTY(float voltage READ voltage NOTIFY voltageChanged FINAL)
    Q_PROPERTY(float speed READ speed NOTIFY speedChanged FINAL)

public:
    explicit CommandInterface(QObject *parent = nullptr);

    Q_INVOKABLE void increaseVoltage();
    Q_INVOKABLE void decreaseVoltage();

    [[nodiscard]] float voltage() const;
    [[nodiscard]] float speed() const;

signals:
    void voltageChanged();
    void speedChanged();

private:
    enum ReadValueType {
        Speed,
        Voltage,
        Invalid,
    };

    void updateValue(const QString &&str, const ReadValueType t);

    QSerialPort mSerial;
    float mVoltage;
    float mSpeed;
};
