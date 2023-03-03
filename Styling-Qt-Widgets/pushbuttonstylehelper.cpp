/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#include "pushbuttonstylehelper.h"

#include "colorrepository.h"

#include <QPainter>
#include <QStyleOptionButton>

static const int s_radius = 6;

void PushButtonStyleHelper::setupPainterForShape(const QStyleOptionButton *option, QPainter *painter, const QWidget *widget)
{
    Q_UNUSED(widget)
    if (!(option->state & QStyle::State_Enabled)) {
        painter->setPen(ColorRepository::buttonOutlineColor());
        painter->setBrush(ColorRepository::buttonBackground());
        painter->setOpacity(0.5);
    } else if (option->state & QStyle::State_Sunken) {
        painter->setPen(ColorRepository::pressedOutlineColor());
        painter->setBrush(ColorRepository::buttonPressedBackground());
    } else if ((option->state & QStyle::State_MouseOver) || (option->state & QStyle::State_HasFocus)) {
        // TODO animation on hover (not on focus)
        painter->setPen(QPen(ColorRepository::hoverOutlineBrush(option->rect), 1));
        painter->setBrush(ColorRepository::buttonHoveredBackground());
    } else {
        painter->setPen(ColorRepository::buttonOutlineColor());
        painter->setBrush(ColorRepository::buttonBackground());
    }
}

void PushButtonStyleHelper::drawButtonShape(const QStyleOptionButton *option, QPainter *painter, const QWidget *widget)
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    setupPainterForShape(option, painter, widget);
    painter->drawRoundedRect(QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5), s_radius, s_radius);
    painter->restore();
}

QSize PushButtonStyleHelper::sizeFromContents(const QStyleOptionButton *option, QSize contentsSize, const QWidget *widget) const
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    const int margin = 6; // usually this comes from PM_ButtonMargin
    const int frameWidth = 2; // due to pen width 1 in drawButtonBevel, on each side
    return QSize(qMax(60, contentsSize.width() + margin + frameWidth), contentsSize.height() + margin + frameWidth);
}

void PushButtonStyleHelper::adjustTextPalette(QStyleOptionButton *option) const
{
    QColor textColor;
    if (!(option->state & QStyle::State_Enabled)) {
        textColor = option->palette.color(QPalette::ButtonText);
        textColor.setAlphaF(0.5);
    } else if (option->state & QStyle::State_Sunken) {
        textColor = ColorRepository::pressedTextColor();
    } else if (option->state & QStyle::State_MouseOver) {
        textColor = ColorRepository::hoverTextColor();
    } else {
        textColor = option->palette.color(QPalette::ButtonText);
    }
    option->palette.setColor(QPalette::ButtonText, textColor);
}
