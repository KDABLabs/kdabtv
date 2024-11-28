#ifndef WIDGETFORMHANDLER_H
#define WIDGETFORMHANDLER_H

#include "fontcontrolswidgetsform.h"

#include <QObject>
#include <QQmlEngine>
#include <QWidget>

class WidgetFormHandler : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString font READ font NOTIFY fontChanged)

public:
    explicit WidgetFormHandler(QObject *parent = nullptr);

    const bool isVisible();
    void setVisible(bool);
    const QString text();
    void setText(const QString&);
    const QString font();

signals:
    void visibleChanged();
    void textChanged();
    void fontChanged();
    void toggleWidgetsWindow();

private:
    FontControlsWidgetsForm *m_window;
};

#endif // WIDGETFORMHANDLER_H
