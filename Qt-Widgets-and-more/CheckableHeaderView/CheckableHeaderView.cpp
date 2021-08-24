/* MIT License

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "CheckableHeaderView.h"
#include <QMouseEvent>
#include <QPainter>

namespace {
static constexpr int margin = 4;
}

int CheckableHeaderView::checkBoxSize() const
{
    return fontMetrics().height();
}

int CheckableHeaderView::checkBoxAreaWidth() const
{
    return checkBoxSize() + 2 * margin;
}

void CheckableHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    // First paint the background as we later narrow the area the QHeaderView itself paints.
    const QVariant backgroundBrush =
        model()->headerData(logicalIndex, orientation(), Qt::BackgroundRole);

    painter->save();
    QStyleOptionHeader opt;
    initStyleOption(&opt);
    opt.rect = rect;
    if (!backgroundBrush.isNull()) {
        opt.palette.setBrush(QPalette::Button, backgroundBrush.value<QBrush>());
        opt.palette.setBrush(QPalette::Window, backgroundBrush.value<QBrush>());
    }
    style()->drawControl(QStyle::CE_Header, &opt, painter, this);
    painter->restore();

    // paint the section adjusted to the right
    painter->save();
    QHeaderView::paintSection(painter, rect.adjusted(checkBoxAreaWidth(), 0, 0, 0), logicalIndex);
    painter->restore();

    // paint the check box
    QStyleOptionButton option;
    const int size = checkBoxSize();
    option.rect = QRect(rect.left() + margin, rect.top() + (rect.height() - size) / 2, size, size);
    if (model()->headerData(logicalIndex, orientation(), Qt::CheckStateRole) == Qt::Checked)
        option.state = QStyle::State_On | QStyle::State_Enabled;
    else
        option.state = QStyle::State_Off | QStyle::State_Enabled;
    style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
}

QSize CheckableHeaderView::sizeHint() const
{
    return QHeaderView::sizeHint() + QSize(checkBoxAreaWidth(), 0);
}

void CheckableHeaderView::mousePressEvent(QMouseEvent *event)
{
    const int index = logicalIndexAt(event->pos());
    if (index == -1) {
        QHeaderView::mousePressEvent(event);
        return;
    }

    if (event->pos().x() > checkBoxAreaWidth()) {
        QHeaderView::mousePressEvent(event);
        return;
    }

    const Qt::CheckState state =
        model()->headerData(index, orientation(), Qt::CheckStateRole).value<Qt::CheckState>();
    model()->setHeaderData(index, orientation(), state == Qt::Checked ? Qt::Unchecked : Qt::Checked,
                           Qt::CheckStateRole);
}
