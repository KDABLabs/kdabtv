#include "widgetFormHandler.h"
#include "fontcontrolswidgetsform.h"

WidgetFormHandler::WidgetFormHandler(QObject *parent)
    : QObject(parent)
    , m_window(std::make_unique<FontControlsWidgetsForm>())
{
    m_window->setVisible(false);
    connect(m_window.get(), &FontControlsWidgetsForm::buttonClicked, this, &WidgetFormHandler::toggleWidgetsWindow);
    connect(m_window.get(), &FontControlsWidgetsForm::textChanged, this, &WidgetFormHandler::textChanged);
    connect(m_window.get(), &FontControlsWidgetsForm::fontFamilyChanged, this, &WidgetFormHandler::fontFamilyChanged);
}

WidgetFormHandler::~WidgetFormHandler() = default;

const bool WidgetFormHandler::isVisible()
{
    return m_window->isVisible();
}

void WidgetFormHandler::setVisible(bool visible)
{
    m_window->setVisible(visible);
    emit visibleChanged();
}

QString WidgetFormHandler::text() const
{
    return m_window->text();
}

void WidgetFormHandler::setText(const QString& text)
{
    m_window->setText(text);
    emit textChanged();
}

QString WidgetFormHandler::fontFamily() const
{
    return m_window->fontFamily();
}
