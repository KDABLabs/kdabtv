#include "sensors.h"

Sensors::Sensors(QObject *parent)
: SensorsSimpleSource(parent)
{
    connect(&m_timer, &QTimer::timeout, this, [this]{
        if (std::abs(targetTemperature() - currentTemperature()) < 0.25) {
            setCurrentTemperature(targetTemperature());
            setStatus(Sensors::Idle);
            m_timer.stop();
            return;
        }
        if (targetTemperature() < currentTemperature()) {
            setCurrentTemperature(currentTemperature() - 0.25);
        } else {
            setCurrentTemperature(currentTemperature() + 0.25);
        }
    }, Qt::QueuedConnection);
    m_timer.start(500); // Update every second
}

void Sensors::setTargetTemperature(double val)
{
    if (val < 16 || val > 30)
        return;
    SensorsSimpleSource::setTargetTemperature(val);
    if (std::abs(targetTemperature() - currentTemperature()) >= 0.25) {
        setStatus(targetTemperature() > currentTemperature() ? Sensors::Heating : Sensors::Cooling);
        m_timer.start();
    }
}

