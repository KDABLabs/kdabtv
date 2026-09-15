#include "cppinterface.h"

CppInterface::CppInterface() {
    m_singleton = CppSingleton::instance();
    connect(m_singleton.get(), &CppSingleton::sharedColorChanged, this, &CppInterface::sharedColorChanged);
}

QColor CppInterface::sharedColor()
{
    return m_singleton.get()->sharedColor();
}

void CppInterface::setSharedColor(QColor color)
{
    m_singleton.get()->setSharedColor(color);
}
