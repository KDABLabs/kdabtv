/* MIT License

Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#pragma once

#define CHECK_rowCount(index) Q_ASSERT(checkIndex(index))

#define CHECK_columnCount(index) Q_ASSERT(checkIndex(index))

#define CHECK_data(index)                                                                          \
    if (qobject_cast<const QAbstractTableModel *>(this)                                            \
        || qobject_cast<const QAbstractListModel *>(this))                                         \
        Q_ASSERT(checkIndex(index,                                                                 \
                            QAbstractItemModel::CheckIndexOption::IndexIsValid                     \
                                | QAbstractItemModel::CheckIndexOption::ParentIsInvalid));         \
    else                                                                                           \
        Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid))

#define CHECK_setData(index) CHECK_data(index)

#define CHECK_headerData(section, orientation)                                                     \
    Q_ASSERT(section >= 0);                                                                        \
    if (orientation == Qt::Horizontal)                                                             \
        Q_ASSERT(section < columnCount({}));                                                       \
    else                                                                                           \
        Q_ASSERT(section < rowCount({}));

#define CHECK_setHeaderData(section, orientation) CHECK_headerData(section, orientation)

#define CHECK_flags(index) Q_ASSERT(checkIndex(index))

// If you get an assert for row or column being zero and rowCount() and columnCount() is zero too,
// then there is a chance that it is a subclass of QAbstractProxyModel::headerData making this out
// of bound call. The cure is to implement headerData in the subclass of QAbstractProxyModel, and
// while doing so /not/ use mapToSource for finding the row or column in the source model.
#define CHECK_index(row, column, parent)                                                           \
    Q_ASSERT(row >= 0);                                                                            \
    Q_ASSERT(column >= 0);                                                                         \
    Q_ASSERT(row < rowCount(parent));                                                              \
    Q_ASSERT(column < columnCount(parent));                                                        \
    Q_ASSERT(checkIndex(parent));

#define CHECK_parent(parent)                                                                       \
    Q_ASSERT(checkIndex(parent, QAbstractItemModel::CheckIndexOption::DoNotUseParent));

#define CHECK_insertRows(row, count, parent)                                                       \
    Q_ASSERT(checkIndex(parent));                                                                  \
    Q_ASSERT(row >= 0);                                                                            \
    Q_ASSERT(row <= rowCount(parent));                                                             \
    Q_ASSERT(count > 0)

// Technically it might be OK to call removeRows with count == 0, so you might
// consider taking that out and making it a check in your code instead.
#define CHECK_removeRows(row, count, parent)                                                       \
    Q_ASSERT(checkIndex(parent));                                                                  \
    Q_ASSERT(row >= 0);                                                                            \
    Q_ASSERT(count > 0);                                                                           \
    Q_ASSERT(row <= rowCount(parent) - count)

#define CHECK_insertColumns(column, count, parent)                                                 \
    Q_ASSERT(checkIndex(parent));                                                                  \
    Q_ASSERT(column >= 0);                                                                         \
    Q_ASSERT(column <= columnCount(parent));                                                       \
    Q_ASSERT(count > 0)

// Same as removeRows above.
#define CHECK_removeColumns(column, count, parent)                                                 \
    Q_ASSERT(checkIndex(parent));                                                                  \
    Q_ASSERT(column >= 0);                                                                         \
    Q_ASSERT(count > 0);                                                                           \
    Q_ASSERT(column <= columnCount(parent) - count)
