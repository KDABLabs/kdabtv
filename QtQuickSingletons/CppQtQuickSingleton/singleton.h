#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QColor>

class AppSingleton : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    // QML_NAMED_ELEMENT(MySingleton)
    QML_SINGLETON

    Q_PROPERTY(bool ready READ ready WRITE setReady NOTIFY readyChanged FINAL)
    Q_PROPERTY(int margin READ margin FINAL)
    Q_PROPERTY(QString logo READ logo FINAL)
    Q_PROPERTY(QColor boundProperty READ boundProperty WRITE setBoundProperty NOTIFY boundPropertyChanged FINAL)
public:
    explicit AppSingleton(QObject *parent = nullptr);

    bool ready() const;
    void setReady(bool newReady);

    QColor boundProperty() const;
    void setBoundProperty(const QColor &newBoundProperty);

    int margin() const;
    void setMargin(int newMargin);

    QString logo() const;
    void setLogo(const QString &newLogo);

signals:
    void readyChanged();
    void boundPropertyChanged();
    void marginChanged();
    void logoChanged();

private:
    bool m_ready;
    QColor m_boundProperty;
    const QString m_logo;
};
