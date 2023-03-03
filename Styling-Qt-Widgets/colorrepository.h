/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#ifndef COLORREPOSITORY_H
#define COLORREPOSITORY_H

#include <QColor>
#include <QPalette>

/**
 * Our colors. They are separate from the widget style so that custom widgets can also use them directly.
 */
namespace ColorRepository
{
    QPalette standardPalette();
    void setDarkMode(bool dark);

    QColor windowBackground();
    QColor baseBackground();
    QColor text();

    QColor pressedTextColor();
    QColor hoverTextColor();

    QColor pressedOutlineColor();
    QBrush hoverOutlineBrush(const QRect &rect);
    QColor buttonOutlineColor();

    QColor buttonPressedBackground();
    QColor buttonHoveredBackground();
    QColor buttonBackground();

    QBrush progressBarOutlineBrush(const QRect &rect);
    QBrush progressBarOutlineFadingBrush(const QRect &rect);
    QBrush progressBarContentsBrush(const QRect &rect);
    QColor progressBarTextColor(bool enabled);
}

#endif // COLORREPOSITORY_H
