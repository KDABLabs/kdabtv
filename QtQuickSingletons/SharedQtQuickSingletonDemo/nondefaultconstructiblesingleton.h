#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QColor>

using namespace Qt::StringLiterals;

class NonDefaultConstructibleSingleton : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(MyNonDefaultConstructibleSingleton)

    Q_PROPERTY(QColor sharedColor READ sharedColor WRITE setSharedColor NOTIFY sharedColorChanged FINAL)
private:
    NonDefaultConstructibleSingleton(QObject *parent = nullptr);

public:
    static NonDefaultConstructibleSingleton *create(QQmlEngine *qmlEngine, QJSEngine *);

    QColor sharedColor();
    Q_INVOKABLE void setSharedColor(QColor color);

signals:
    void sharedColorChanged(QColor color);

private:
    inline static QJSEngine *s_engine = nullptr;

private:
    QColor m_sharedColor;
};
