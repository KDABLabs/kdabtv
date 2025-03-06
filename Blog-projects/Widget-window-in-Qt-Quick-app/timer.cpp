#include "timer.h"

Timer::Timer(QObject *parent)
    : QObject(parent)
{
    m_timer.start();
}

int Timer::deltaTime() const
{
    return m_timer.elapsed();
}
