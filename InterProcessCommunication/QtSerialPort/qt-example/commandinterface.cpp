#include "commandinterface.h"

#include <QRegularExpression>

using namespace Qt::StringLiterals;

CommandInterface::CommandInterface(QObject *parent)
    : QObject{parent}
    , mSerial{"tnt1"}
    , mVoltage{0.0}
    , mSpeed{0.0}
{
    if (!mSerial.open(QIODevice::ReadWrite))
        qWarning() << "Can't open" << mSerial.portName() << "error code" << mSerial.error();

    connect(&mSerial, &QSerialPort::readyRead, this, [this]() {
        if (!mSerial.canReadLine())
            return;

        const auto buf = mSerial.read(1024);
        const auto str = QString::fromUtf8(buf);

        qDebug() << str;

        const auto readValueType
            = str.contains(u"SPEED"_s) ? ReadValueType::Speed
                                       : (str.contains(u"VOLTAGE"_s) ? ReadValueType::Voltage
                                                                     : ReadValueType::Invalid);
        updateValue(std::move(str), readValueType);
    });
}

void CommandInterface::increaseVoltage()
{
    mSerial.write("+");
    mSerial.flush();
}

void CommandInterface::decreaseVoltage()
{
    mSerial.write("-");
    mSerial.flush();
}

float CommandInterface::voltage() const
{
    return mVoltage;
}

float CommandInterface::speed() const
{
    return mSpeed;
}

void CommandInterface::updateValue(const QString &&str, const ReadValueType t)
{
    static const QRegularExpression speedRegex{u"SPEED: (?<num>\\d+\\.\\d+)"_s};
    static const QRegularExpression voltageRegex{u"VOLTAGE: (?<num>\\d+\\.\\d+)"_s};

    if (t == ReadValueType::Invalid)
        return;

    const bool isSpeed{t == ReadValueType::Speed};

    const auto match = (isSpeed ? speedRegex : voltageRegex).match(str);

    if (match.hasMatch()) {
        const auto matchstr = match.captured(u"num"_s);
        const auto newValue = matchstr.toFloat();

        if (qFuzzyCompare((isSpeed ? mSpeed : mVoltage), newValue))
            return;

        (isSpeed ? mSpeed : mVoltage) = newValue;
        (isSpeed ? emit speedChanged() : emit voltageChanged());
    }
}
