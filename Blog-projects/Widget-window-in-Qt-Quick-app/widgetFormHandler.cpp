#include "widgetFormHandler.h"

WidgetFormHandler::WidgetFormHandler(QObject *parent)
    : QObject{parent}
{
    m_window = new FontControlsWidgetsForm();
    m_window->setVisible(false);

    QObject::connect(m_window, &FontControlsWidgetsForm::on_pushButton_clicked, this, &WidgetFormHandler::toggleWidgetsWindow);
    QObject::connect(m_window, &FontControlsWidgetsForm::textChanged, this, &WidgetFormHandler::textChanged);
    QObject::connect(m_window, &FontControlsWidgetsForm::fontChanged, this, &WidgetFormHandler::fontChanged);
}

bool WidgetFormHandler::isVisible()
{
    return m_window->isVisible();
}

void WidgetFormHandler::setVisible(bool visible)
{
    if (visible)
        m_window->show();
    else
        m_window->hide();
    emit visibleChanged();
}

QString WidgetFormHandler::getText()
{
    return m_window->getText();
}

void WidgetFormHandler::setText(const QString& text)
{
    m_window->setText(text);
    emit textChanged();
}

QString WidgetFormHandler::getFont()
{
    return m_window->getFont();
}
