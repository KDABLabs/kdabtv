/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#include "colorrepository.h"

#include <QApplication>
#include <QBrush>
#include <QToolTip>

// To avoid requiring C++17
template <class T>
constexpr const T &clamp(const T &v, const T &lo, const T &hi)
{
    return v < lo ? lo : hi < v ? hi : v;
}

static bool s_darkMode = true;

QPalette ColorRepository::standardPalette()
{
    QPalette pal;
    // TODO brush with noise.png
    pal.setColor(QPalette::Window, windowBackground());
    pal.setColor(QPalette::Base, baseBackground());
    pal.setColor(QPalette::WindowText, text());
    pal.setColor(QPalette::Text, text());

    // Text color on buttons
    pal.setColor(QPalette::ButtonText, text());

    // pal.setColor(QPalette::ToolTipBase, baseBackground());
    pal.setColor(QPalette::ToolTipText, text());

    QToolTip::setPalette(pal);

    return pal;
}

void ColorRepository::setDarkMode(bool dark)
{
    s_darkMode = dark;
    qApp->setPalette(standardPalette());
}

QColor ColorRepository::windowBackground()
{
    return s_darkMode ? QColor(0x18, 0x21, 0x29) // dark blue
                      : QColor(0xef, 0xf0, 0xf1);
}

QColor ColorRepository::baseBackground()
{
    return s_darkMode ? QColor(0x0f, 0x0f, 0x0f) // almost black
                      : QColor(0xfb, 0xfb, 0xfb); // almost white
}

QColor ColorRepository::text()
{
    return s_darkMode ? QColor(0xa5, 0xa5, 0xa5) : QColor(0x25, 0x25, 0x25);
}

QColor ColorRepository::pressedTextColor()
{
    return QColor(0x65, 0x65, 0x65); // medium gray
}

QColor ColorRepository::hoverTextColor()
{
    return QColor(0xdd, 0xdd, 0xdd); // light gray
}

QColor ColorRepository::pressedOutlineColor()
{
    return QColor(0x32, 0x2d, 0x35);
}

QColor ColorRepository::buttonOutlineColor()
{
    return s_darkMode ? QColor(0x59, 0x51, 0x5f) : QColor(0x9f, 0x95, 0xa3);
}

QBrush ColorRepository::hoverOutlineBrush(const QRect &rect)
{
    // Instructions from the designer:
    // "Draw line passing by center of rectangle (+4% to the right)
    // and that is perpendicular to the topleft-bottomright diagonal.
    // This line intersects the top and bottom in two points, which are the gradient stops"

    const qreal w = rect.width();
    const qreal h = rect.height();
    const qreal xmid = w * 0.54;
    const qreal xoffset = (h * h) / (2 * w); // Proportionality: xoffset / (h/2) = h / w
    const qreal x0 = xmid - xoffset;
    const qreal x1 = xmid + xoffset;

    QLinearGradient gradient(x0, h, x1, 0);
    gradient.setColorAt(0.0, QColor(0x53, 0x94, 0x9f));
    gradient.setColorAt(1.0, QColor(0x75, 0x55, 0x79));
    return QBrush(gradient);
}

QColor ColorRepository::buttonPressedBackground()
{
    return s_darkMode ? QColor(0x17, 0x17, 0x17) : QColor(0xf8, 0xf7, 0xf8);
}

QColor ColorRepository::buttonHoveredBackground()
{
    QColor color = buttonPressedBackground();
    color.setAlphaF(0.2);
    return color;
}

QColor ColorRepository::buttonBackground()
{
    return s_darkMode ? QColor(0x21, 0x1f, 0x22, 0xa7) : QColor(0xf5, 0xf4, 0xf5) /* TODO with opacity = ? */;
}

QBrush ColorRepository::progressBarOutlineBrush(const QRect &rect)
{
    QLinearGradient gradient(0, rect.height(), rect.width(), 0);
    gradient.setColorAt(0.0, QColor(0x11, 0xc2, 0xe1));
    gradient.setColorAt(1.0, QColor(0x89, 0x3a, 0x94));
    return QBrush(gradient);
}

QBrush ColorRepository::progressBarOutlineFadingBrush(const QRect &rect)
{
    QLinearGradient gradient(0, rect.height(), rect.width(), 0);
    gradient.setColorAt(0.0, QColor(0x11, 0xc2, 0xe1));
    gradient.setColorAt(1.0, QColor(0x89, 0x3a, 0x94));
    return QBrush(gradient);
}

QBrush ColorRepository::progressBarContentsBrush(const QRect &rect)
{
    // same as outline brush but with 37% opacity
    QLinearGradient gradient(0, rect.height(), rect.width(), 0);
    gradient.setColorAt(0.0, QColor(0x11, 0xc2, 0xe1, 0x60));
    gradient.setColorAt(1.0, QColor(0x89, 0x3a, 0x94, 0x60));
    return QBrush(gradient);
}

QColor ColorRepository::progressBarTextColor(bool enabled)
{
    QColor textColor = text();
    if (!enabled)
        textColor.setAlphaF(textColor.alphaF() / 2.0);
    return textColor;
}
