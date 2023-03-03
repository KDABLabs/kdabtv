/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#ifndef PUSHBUTTONSTYLEHELPER_H
#define PUSHBUTTONSTYLEHELPER_H

#include <QSize>

class QPainter;
class QPushButton;
class QStyleOptionButton;
class QWidget;

class PushButtonStyleHelper
{
public:
    void setupPainterForShape(const QStyleOptionButton *option, QPainter *painter, const QWidget *widget);
    void drawButtonShape(const QStyleOptionButton *option, QPainter *painter, const QWidget *widget);
    QSize sizeFromContents(const QStyleOptionButton *option, QSize contentsSize, const QWidget *widget) const;
    void adjustTextPalette(QStyleOptionButton *option) const;
};

#endif // PUSHBUTTONSTYLEHELPER_H
