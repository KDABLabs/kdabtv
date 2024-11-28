#include "widgetFormHandler.h"

WidgetFormHandler::WidgetFormHandler(QObject *parent)
    : QObject{parent}
{
    m_window = new FontControlsWidgetsForm();
    m_window->setVisible(false);

    QObject::connect(m_window, &FontControlsWidgetsForm::pushButton_clicked, this, &WidgetFormHandler::toggleWidgetsWindow);
    QObject::connect(m_window, &FontControlsWidgetsForm::textChanged, this, &WidgetFormHandler::textChanged);
    QObject::connect(m_window, &FontControlsWidgetsForm::fontChanged, this, &WidgetFormHandler::fontChanged);
}

const bool WidgetFormHandler::isVisible()
{
    return m_window->isVisible();
}

void WidgetFormHandler::setVisible(bool visible)
{
    m_window->setVisible(visible);
    emit visibleChanged();
}

const QString WidgetFormHandler::text()
{
    return m_window->text();
}

void WidgetFormHandler::setText(const QString& text)
{
    m_window->setText(text);
    emit textChanged();
}

const QString WidgetFormHandler::font()
{
    return m_window->font();
}
