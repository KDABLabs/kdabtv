#include "cppsingleton.h"

std::shared_ptr<CppSingleton> CppSingleton::instance()
{
    static std::shared_ptr<CppSingleton> sharedPtr{new CppSingleton};
    return sharedPtr;
}

QColor CppSingleton::sharedColor()
{
    return m_sharedColor;
}

void CppSingleton::setSharedColor(QColor color)
{
    m_sharedColor = color;
    emit sharedColorChanged(color);
}
