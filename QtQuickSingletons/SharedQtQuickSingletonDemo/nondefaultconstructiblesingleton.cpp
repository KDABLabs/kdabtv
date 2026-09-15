#include "nondefaultconstructiblesingleton.h"

NonDefaultConstructibleSingleton::NonDefaultConstructibleSingleton(QObject *parent)
    : QObject(parent)
    , m_sharedColor(u"white"_s)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

NonDefaultConstructibleSingleton *NonDefaultConstructibleSingleton::create(QQmlEngine *qmlEngine, QJSEngine *)
{
    static auto singleton = new NonDefaultConstructibleSingleton();
    Q_ASSERT(qmlEngine->thread() == singleton->thread());

    // There should only be one engine accessing the singleton.
    // However, in this instance sharing accross engines works out because they're all running on the same thread.
    // if (s_engine)
    //     Q_ASSERT(qmlEngine == s_engine);
    // else
    //     s_engine = qmlEngine;

    return singleton;
}

QColor NonDefaultConstructibleSingleton::sharedColor()
{
    return m_sharedColor;
}

void NonDefaultConstructibleSingleton::setSharedColor(QColor color)
{
    m_sharedColor = color;
    emit sharedColorChanged(color);
}
