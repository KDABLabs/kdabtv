#ifndef SENSORS_H
#define SENSORS_H

#include <QTimer>
#include <rep_Sensors_source.h>

class Sensors : public SensorsSimpleSource
{
    Q_OBJECT
public:
    Sensors(QObject *parent = nullptr);
    void setTargetTemperature(double val) final;

private:
    QTimer m_timer;
};

#endif // SENSORS_H
