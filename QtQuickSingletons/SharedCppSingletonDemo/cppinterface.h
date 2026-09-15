#pragma once

#include <QQuickItem>

#include "cppsingleton.h"

class CppInterface : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QColor sharedColor READ sharedColor WRITE setSharedColor NOTIFY sharedColorChanged FINAL)
public:
    CppInterface();

    QColor sharedColor();
    Q_INVOKABLE void setSharedColor(QColor color);

signals:
    void sharedColorChanged(QColor color);

private:
    std::shared_ptr<CppSingleton> m_singleton;
};
