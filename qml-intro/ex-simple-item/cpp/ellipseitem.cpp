/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QPainter>
#include "ellipseitem.h"

//--> slide
EllipseItem::EllipseItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

void EllipseItem::paint(QPainter *painter)
{
//--> hide
    painter->save();

    QPen pen = painter->pen();
    pen.setBrush(m_color);
    pen.setWidth(3);
    painter->setPen(pen);
    const QRectF paintRect = QRectF({}, QSizeF{width(), height()}).adjusted(1, 1, -1, -1);
//<-- hide
    painter->drawEllipse(paintRect);
//--> hide
    painter->restore();
//<-- hide
}
//<-- slide

QColor EllipseItem::color() const
{
    return m_color;
}

void EllipseItem::setColor(const QColor &newColor)
{
    if (m_color != newColor) {
        m_color = newColor;
        update();
        emit colorChanged();
    }
}
