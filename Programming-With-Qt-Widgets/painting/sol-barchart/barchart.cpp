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
#include "qfontmetrics.h"
#include "qnamespace.h"

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
namespace {
int MARGIN = 10;
int CHARTWIDTH;
int BARHEIGHT;
} // namespace

void BarChart::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.translate(MARGIN, MARGIN);
    CHARTWIDTH = width() - 2 * MARGIN;

    QFontMetrics metrics = p.fontMetrics();
    int textHeight = metrics.height();
    BARHEIGHT = textHeight + MARGIN; // half a margin on each side

    { // Paint header
        QRect rect(0, 0, CHARTWIDTH, textHeight);
        p.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, "0 %");
        p.drawText(rect, Qt::AlignRight | Qt::AlignVCenter, "100 %");

        p.drawLine(rect.bottomLeft(), rect.bottomRight());
        int chartBottom = height() - 2 * MARGIN;
        p.setPen(QPen(Qt::DotLine));
        p.drawLine(rect.bottomLeft(), QPoint(0, chartBottom));
        p.drawLine(rect.bottomRight(), QPoint(rect.right(), chartBottom));

        int x = (rect.right() - rect.left()) / 2;
        p.drawLine(QPoint(x, rect.bottom()), QPoint(x, chartBottom));

        p.translate(0, rect.bottom());
    }

    for (Bar &bar : m_bars) {
        p.translate(0, MARGIN);
        QRect rect(0, 0, bar.value / 100.0 * CHARTWIDTH, BARHEIGHT);
        p.setBrush(bar.isSelected ? Qt::gray : bar.color);
        p.setPen(QPen(Qt::SolidLine));
        p.drawRect(rect);
        p.drawText(rect, Qt::AlignCenter, bar.label);

        bar.paintedRect = p.transform().mapRect(rect);

        p.translate(rect.bottomLeft());
    }
}

void BarChart::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    for (Bar &bar : m_bars) {
        bar.isSelected = bar.paintedRect.contains(point);
    }
    update();
}
