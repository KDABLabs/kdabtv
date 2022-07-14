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

#include "DataAndPercentageDelegate.h"
#include "EnumConverters.h"
#include <QPainter>

DataAndPercentageDelegate::DataAndPercentageDelegate(QAbstractItemModel *model)
    : QWAMDelegate(model)
{
    auto clearWidth = [this] { m_widths.clear(); };
    // clang-format off
    connect(model, &QAbstractItemModel::modelReset,      this, clearWidth);
    connect(model, &QAbstractItemModel::rowsInserted,    this, clearWidth);
    connect(model, &QAbstractItemModel::rowsRemoved,     this, clearWidth);
    connect(model, &QAbstractItemModel::rowsMoved,       this, clearWidth);
    connect(model, &QAbstractItemModel::columnsInserted, this, clearWidth);
    connect(model, &QAbstractItemModel::columnsRemoved,  this, clearWidth);
    connect(model, &QAbstractItemModel::columnsMoved,    this, clearWidth);
    connect(model, &QAbstractItemModel::layoutChanged,   this, clearWidth);
    // clang-format on
}

namespace {
const int MARGIN = 5;
const int PADDING = 3;
}

void DataAndPercentageDelegate::paintInternal(QPainter *painter, const QStyleOptionViewItem &option,
                                              const QModelIndex &index) const
{
    painter->save();
    painter->setClipRect(option.rect);

    if (m_widths.isEmpty())
        recalculateCellWidth(index.model(), option.fontMetrics);

    QRect rect = option.rect;

    // Paint the value
    const QString value = index.data(+Model::Role::Value).toString();
    rect.adjust(MARGIN, 0, 0, 0);
    rect.setWidth(m_widths[index.column()][Model::Role::Value]);
    painter->drawText(rect, Qt::AlignVCenter | Qt::AlignHCenter, value);

    // Paint the arrow
    rect.setX(rect.right() + PADDING);
    const auto pixmap = index.data(+Model::Role::Arrow).value<QPixmap>();
    painter->drawPixmap(rect.x(), rect.y() + (rect.height() - pixmap.height()) / 2, pixmap);

    // Paint the delta
    rect.setX(rect.x() + pixmap.width() + PADDING);
    rect.setWidth(m_widths[index.column()][Model::Role::Delta]);

    painter->drawText(rect, Qt::AlignVCenter | Qt::AlignRight,
                      index.data(+Model::Role::Delta).toString());

    painter->restore();
}

void DataAndPercentageDelegate::recalculateCellWidth(const QAbstractItemModel *model,
                                                     const QFontMetrics &metrics) const
{
    m_widths.clear();

    for (int column = 0; column < model->columnCount(); ++column) {
        for (auto role : {Model::Role::Value, Model::Role::Delta}) {
            int width = 0;
            for (int row = 0; row < model->rowCount(); ++row) {
                width = qMax(
                    width,
                    metrics.boundingRect(model->data(model->index(row, column), +role).toString())
                        .width());
            }
            m_widths[column][role] = width;
        }
    }
}

QSize DataAndPercentageDelegate::sizeHint(const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{
    if (m_widths.isEmpty()) {
        QStyleOptionViewItem opt = setOptions(index, option);
        recalculateCellWidth(index.model(), opt.fontMetrics);
    }

    const auto cell = m_widths.value(index.column());
    const int width = cell[Model::Role::Value] + cell[Model::Role::Delta]
        + 12 /*image width*/ + 2 * PADDING + 2 * MARGIN;

    return QSize(width, QWAMDelegate::sizeHint(option, index).height());
}

size_t qHash(const Model::Role &role)
{
    return +role;
}
