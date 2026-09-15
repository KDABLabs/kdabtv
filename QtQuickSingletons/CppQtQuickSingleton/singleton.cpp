#include "singleton.h"

AppSingleton::AppSingleton(QObject *parent)
    : QObject{parent},
    m_ready(false),
    m_boundProperty("#000000"),
    m_logo("kdab.svg")
{}

bool AppSingleton::ready() const
{
    return m_ready;
}

void AppSingleton::setReady(bool newReady)
{
    if (m_ready == newReady)
        return;
    m_ready = newReady;
    emit readyChanged();
}

QColor AppSingleton::boundProperty() const
{
    return m_boundProperty;
}

void AppSingleton::setBoundProperty(const QColor &newBoundProperty)
{
    if (m_boundProperty == newBoundProperty)
        return;
    m_boundProperty = newBoundProperty;
    emit boundPropertyChanged();
}

int AppSingleton::margin() const
{
    return m_ready ? 0 : 100;
}

QString AppSingleton::logo() const
{
    return m_logo;
}
