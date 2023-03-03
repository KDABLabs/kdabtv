/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#include "progressbarstylehelper.h"
#include "colorrepository.h"

#include <QDebug>
#include <QPainter>
#include <QStyleOptionProgressBar>

void ProgressBarStyleHelper::drawGroove(const QStyleOptionProgressBar *option, QPainter *painter, const QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(ColorRepository::buttonOutlineColor());
    painter->setBrush(ColorRepository::baseBackground());
    const qreal radius = option->rect.height() / 2;
    painter->drawRoundedRect(QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);
}

void ProgressBarStyleHelper::drawContents(const QStyleOptionProgressBar *option, QPainter *painter, const QWidget *widget)
{
    Q_UNUSED(widget);
    const auto value = option->progress - option->minimum;
    const auto range = option->maximum - option->minimum;
    if (value > 0) {
        painter->save();
        const QRect usableRect = option->rect.adjusted(3, 3, -3, -3);
        QRect progressRect = usableRect;
        progressRect.setWidth(double(value) / double(range) * usableRect.width());

        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(QPen(ColorRepository::progressBarOutlineBrush(option->rect), 1));
        painter->setBrush(ColorRepository::progressBarContentsBrush(option->rect));
        const qreal radius = option->rect.height() / 2 - 2.5;
        painter->drawRoundedRect(QRectF(progressRect).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);

        // Additional trick: the groove itself gets a gradient until the current X value
        QRect repaintedGrooveRect = option->rect;
        repaintedGrooveRect.setWidth(double(value) / double(range) * repaintedGrooveRect.width());
        painter->setClipRect(repaintedGrooveRect);
        painter->setPen(QPen(ColorRepository::progressBarOutlineFadingBrush(option->rect), 1));
        painter->setBrush(Qt::NoBrush);
        painter->setOpacity(0.43);
        painter->drawRoundedRect(QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);

        painter->restore();
    }
}

void ProgressBarStyleHelper::drawText(const QStyleOptionProgressBar *option, QPainter *painter, const QWidget *widget)
{
    Q_UNUSED(widget)
    const QPen oldPen = painter->pen();
    painter->setPen(ColorRepository::progressBarTextColor(option->state & QStyle::State_Enabled));
    painter->drawText(option->rect, Qt::AlignRight | Qt::AlignVCenter | Qt::TextSingleLine, option->text);
    painter->setPen(oldPen);
}

QRect ProgressBarStyleHelper::subElementRect(QStyle::SubElement subElement, const QStyleOptionProgressBar *option,
                                             const QWidget *widget)
{
    Q_UNUSED(widget)
    if (subElement == QStyle::SE_ProgressBarLabel)
        return option->rect.adjusted(0, 0, -6, 0); // right-align before the round rect
    // The area for both groove and content is the whole rect. The drawing will take care of actual contents rect.
    return option->rect;
}
