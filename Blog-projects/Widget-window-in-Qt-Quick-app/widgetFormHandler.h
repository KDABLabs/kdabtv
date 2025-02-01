#pragma once

#include <QObject>
#include <QQmlEngine>

class FontControlsWidgetsForm;

class WidgetFormHandler : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString fontFamily READ fontFamily NOTIFY fontFamilyChanged)

public:
    explicit WidgetFormHandler(QObject *parent = nullptr);
    ~WidgetFormHandler();

    const bool isVisible();
    void setVisible(bool);
    QString text() const;
    void setText(const QString&);
    QString fontFamily() const;

signals:
    void visibleChanged();
    void textChanged();
    void fontFamilyChanged();
    void toggleWidgetsWindow();

private:
    std::unique_ptr<FontControlsWidgetsForm> m_window;
};
