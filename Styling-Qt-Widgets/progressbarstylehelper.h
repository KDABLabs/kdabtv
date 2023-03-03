/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#ifndef PROGRESSBARSTYLEHELPER_H
#define PROGRESSBARSTYLEHELPER_H

#include <QStyle>
class QStyleOptionProgressBar;
class QPainter;
class QWidget;

class ProgressBarStyleHelper
{
public:
    void drawGroove(const QStyleOptionProgressBar *option, QPainter *painter, const QWidget *widget);
    void drawContents(const QStyleOptionProgressBar *option, QPainter *painter, const QWidget *widget);
    void drawText(const QStyleOptionProgressBar *option, QPainter *painter, const QWidget *widget);
    QRect subElementRect(QStyle::SubElement subElement, const QStyleOptionProgressBar *option, const QWidget *widget);
};

#endif // PROGRESSBARSTYLEHELPER_H
