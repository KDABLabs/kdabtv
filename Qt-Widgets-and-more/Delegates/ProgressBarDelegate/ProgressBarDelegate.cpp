/* MIT License

Copyright (C) 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "ProgressBarDelegate.h"
#include <QPainter>

void ProgressBarDelegate::paintInternal(QPainter *painter, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    const auto &data = index.data(Qt::DisplayRole);
    if (data.isNull())
        return;

    bool ok;
    const auto value = data.toDouble(&ok);
    if (!ok)
        return;

    const QColor color = [&] {
        if (value < 0.0)
            return Qt::gray;
        else if (value <= 1.0)
            return Qt::green;
        else
            return Qt::red;
    }();

    // Paint the complete cell, so alternate background coloring aren't seen
    painter->fillRect(option.rect, painter->background());

    QRect rect = option.rect.adjusted(2, 2, -2, -2);
    if (value >= 0 && value <= 1.0)
        rect.setWidth(rect.width() * qMin(1.0, value));

    painter->fillRect(rect, color);
    painter->drawText(option.rect, Qt::AlignCenter,
                      value < 0.0 ? "-" : QString("%1 %").arg(value * 100, 0, 'f', 0));
}
