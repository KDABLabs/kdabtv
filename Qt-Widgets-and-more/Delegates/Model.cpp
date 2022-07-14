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

#include "Model.h"
#include "../Money.h"
#include <QColor>
#include <QFont>

// YES I KNOW. It is missing a lot of the checks it ought to have....

int Model::rowCount(const QModelIndex & /*parent*/) const
{
    return 10;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return QVariant::fromValue(
            Money(Money::EUR, 100 * index.row() * (index.row() % 3 == 0 ? -1 : 1)));

    if (role == Qt::BackgroundRole)
        return (index.row() == 0) ? QVariant(QColor(Qt::red)) : QVariant();

    if (role == Qt::ForegroundRole)
        return (index.row() % 3) == 0 ? QVariant(QColor(Qt::red).lighter()) : QVariant();

    if (role == Qt::TextAlignmentRole)
        return (index.row() > 4) ? QVariant(Qt::AlignCenter) : QVariant();

    if (role == Qt::FontRole) {
        if (index.row() > 6) {
            QFont font;
            font.setPointSize(font.pointSize() * 2);
            return font;
        }
    }

    return {};
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    if (index.row() < 3)
        return QAbstractListModel::flags(index) & ~Qt::ItemIsEnabled;

    if (index.row() < 5)
        return QAbstractListModel::flags(index) | Qt::ItemIsEditable;

    return QAbstractListModel::flags(index);
}
