#pragma once

#include <QObject>
#include <QQmlEngine>

class FontsBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit FontsBackend(QObject *parent = nullptr);

    Q_INVOKABLE static QStringList fontFamilyList();
};
