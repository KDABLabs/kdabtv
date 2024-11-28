#ifndef FONTSBACKEND_H
#define FONTSBACKEND_H

#include <QObject>
#include <QQmlEngine>

class FontsBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
private:

public:
    explicit FontsBackend(QObject *parent = nullptr);

    Q_INVOKABLE static const QStringList fontList();

signals:
};

#endif // FONTSBACKEND_H
