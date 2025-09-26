/*************************************************************************
 *
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "gizmo.h"
#include <QtWidgets>

Gizmo::Gizmo(const QColor &color1, const QColor &color2, Qt::Orientation orientation,
             QWidget *parent)
    : QFrame(parent)
{
    m_color1 = color1;
    m_color2 = color2;
    m_orientation = orientation;
    setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);
}

void Gizmo::paintEvent(QPaintEvent *)
{
    int width = size().width();
    int height = size().height();
    QRect rect1;
    QRect rect2;

    if (m_orientation == Qt::Vertical) {
        rect1 = QRect(0, 0, width / 2, height);
        rect2 = QRect(width / 2, 0, width / 2, height);
    } else {
        rect1 = QRect(0, 0, width, height / 2);
        rect2 = QRect(0, height / 2, width, height / 2);
    }

    QPainter painter(this);

    painter.setPen(m_color1);
    painter.setBrush(QBrush(m_color1, Qt::SolidPattern));
    painter.drawRect(rect1);

    painter.setPen(m_color2);
    painter.setBrush(QBrush(m_color2, Qt::SolidPattern));
    painter.drawRect(rect2);

    if (hasFocus()) {
        QRect rect(0, 0, width - 1, height - 1);
        painter.setBrush(Qt::NoBrush);
        QPen pen(Qt::white);
        painter.setPen(pen);
        painter.drawRect(rect);

        pen.setColor(Qt::black);
        pen.setStyle(Qt::DotLine);
        painter.setPen(pen);
        painter.drawRect(rect);
    }
}

QSize Gizmo::sizeHint() const
{
    return QSize(100, 100);
}

void Gizmo::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_C && event->modifiers().testFlag(Qt::ControlModifier)) {
        qApp->clipboard()->setMimeData(mimeData());
    }

    else if (event->key() == Qt::Key_V && event->modifiers().testFlag(Qt::ControlModifier)) {
        decodeMimeData(qApp->clipboard()->mimeData());
        update();
    }
}

/** Decide if a drag should be started **/
bool Gizmo::shouldStartDrag(QMouseEvent *event)
{
    return (event->buttons().testFlag(Qt::LeftButton)
            && (m_pressPos - event->pos()).manhattanLength() > QApplication::startDragDistance());
}

QMimeData *Gizmo::mimeData() const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << m_color1 << m_color2 << (int)m_orientation;

    auto mimeData = new QMimeData;
    mimeData->setData("x-gizmo/x-drag", data);

    mimeData->setText(QString("%1,%2,%3")
                          .arg(m_color1.name())
                          .arg(m_color2.name())
                          .arg(m_orientation == Qt::Vertical ? "Vertical" : "Horizontal"));
    return mimeData;
}

bool Gizmo::decodeMimeData(const QMimeData *mimeData)
{
    if (mimeData->hasFormat("x-gizmo/x-drag")) {
        QByteArray data = mimeData->data("x-gizmo/x-drag");
        QDataStream stream(data);
        int tmp;
        stream >> m_color1 >> m_color2 >> tmp;
        m_orientation = static_cast<Qt::Orientation>(tmp);
        return true;
    } else if (mimeData->hasText()) {
        QString txt = mimeData->text();
        QStringList parts = txt.split(",");
        if (parts.size() == 3) {
            m_color1 = QColor(parts[0]);
            m_color2 = QColor(parts[1]);
            m_orientation = (parts[2] == "Vertical") ? Qt::Vertical : Qt::Horizontal;
            return true;
        }
    }
    return false;
}

void Gizmo::mousePressEvent(QMouseEvent *event)
{
    m_pressPos = event->pos();
}

void Gizmo::mouseMoveEvent(QMouseEvent *event)
{
    if (shouldStartDrag(event)) {
        auto drag = new QDrag(this);
        drag->setMimeData(mimeData());
        Qt::DropAction dropAction = drag->exec(Qt::CopyAction);
        Q_UNUSED(dropAction); // Make the compiler shut up.
    }
    QFrame::mouseMoveEvent(event);
}

void Gizmo::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText() || event->mimeData()->hasFormat("x-gizmo/x-drag"))
        event->accept();
}

void Gizmo::dropEvent(QDropEvent *event)
{
    bool success = decodeMimeData(event->mimeData());

    if (success) {
        event->acceptProposedAction();
        update();
    }
}
