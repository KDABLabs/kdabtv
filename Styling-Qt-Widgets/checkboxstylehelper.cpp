/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#include "checkboxstylehelper.h"
#include "colorrepository.h"
#include "pushbuttonstylehelper.h"
#include "teststyle.h"

#include <QPainter>
#include <QStyleOption>

void CheckBoxStyleHelper::draw(const TestStyle *style, const QStyleOptionButton *option, QPainter *painter,
                               const QWidget *widget) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    style->pushButtonStyleHelper()->setupPainterForShape(option, painter, widget);
    painter->drawRoundedRect(QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5), 5, 5);
    drawIndicator(option, painter); // with the same pen color
    painter->restore();
}

void CheckBoxStyleHelper::drawIndicator(const QStyleOption *option, QPainter *painter) const
{
    if (option->state & QStyle::State_On) {
        const QRect rect = option->rect;
        const QVector<QPointF> points{QPointF(rect.x() + 4, rect.y() + 9), QPointF(rect.x() + 8, rect.y() + 12),
                                      QPointF(rect.x() + 14, rect.y() + 5)};
        painter->drawPolyline(points);
    }
}

int CheckBoxStyleHelper::indicatorSize() const
{
    return 18;
}
