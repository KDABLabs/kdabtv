/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2011-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "barchart.h"

BarChart::BarChart(QWidget *parent)
    : QWidget(parent)
{
}

void BarChart::addBar(const QString &label, int percentage, const QColor &color)
{
    Bar newBar;
    newBar.label = label;
    newBar.value = percentage;
    newBar.color = color;

    m_bars.append(newBar);
    update();
}

void BarChart::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawText( rect(), Qt::AlignCenter, tr("Paint me !") );
}
