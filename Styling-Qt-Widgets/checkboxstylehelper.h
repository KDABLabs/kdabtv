/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#ifndef CHECKBOXSTYLEHELPER_H
#define CHECKBOXSTYLEHELPER_H

class TestStyle;
class QPainter;
class QStyleOptionButton;
class QStyleOption;
class QWidget;

class CheckBoxStyleHelper
{
public:
    void draw(const TestStyle *style, const QStyleOptionButton *option, QPainter *painter, const QWidget *widget) const;
    void drawIndicator(const QStyleOption *option, QPainter *painter) const;
    int indicatorSize() const;

};

#endif // CHECKBOXSTYLEHELPER_H
