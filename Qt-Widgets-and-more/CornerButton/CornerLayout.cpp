#include "CornerLayout.h"
#include <QEvent>
#include <QLayout>
#include <QWidget>

CornerLayout::CornerLayout(QWidget *parent)
    : QObject(parent)
    , m_parentWidget(parent)
{
    parent->installEventFilter(this);
}

void CornerLayout::addWidget(QWidget *widget, Qt::Corner corner, const QPoint &offset)
{
    widget->setParent(m_parentWidget);
    m_layout.append({corner, widget, offset});
}

bool CornerLayout::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Resize)
        placeWidgets();

    return QObject::eventFilter(watched, event);
}

void CornerLayout::placeWidgets()
{
    QMargins margins;
    if (m_parentWidget->layout())
        margins = m_parentWidget->layout()->contentsMargins();

    for (const auto &item : m_layout) {
        const int horizontalOffset = [&] {
            if (item.corner == Qt::TopLeftCorner || item.corner == Qt::BottomLeftCorner)
                return margins.left() + item.offset.x();
            return margins.right() + item.offset.x();
        }();

        const int verticalOffset = [&] {
            if (item.corner == Qt::TopLeftCorner || item.corner == Qt::TopRightCorner)
                return margins.top() + item.offset.y();
            return margins.bottom() + item.offset.y();
        }();

        const int x = [&] {
            if (item.corner == Qt::TopLeftCorner || item.corner == Qt::BottomLeftCorner)
                return horizontalOffset;
            return m_parentWidget->width() - (item.widget->width() + horizontalOffset);
        }();

        const int y = [&] {
            if (item.corner == Qt::TopLeftCorner || item.corner == Qt::TopRightCorner)
                return verticalOffset;
            return m_parentWidget->height() - (item.widget->height() + verticalOffset);
        }();

        item.widget->move(x, y);
    }
}

#include "moc_CornerLayout.cpp"
