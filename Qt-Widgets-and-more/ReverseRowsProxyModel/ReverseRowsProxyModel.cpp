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

#include "ReverseRowsProxyModel.h"
#include "CheckIndex.h"

static constexpr int VERSION = 3;

QModelIndex ReverseRowsProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    CHECK_index(row, column, parent);
    if (parent.isValid())
        return {};

    return createIndex(row, column);
}

QModelIndex ReverseRowsProxyModel::parent(const QModelIndex &child) const
{
    CHECK_parent(child);
    return {};
}

int ReverseRowsProxyModel::rowCount(const QModelIndex &parent) const
{
    CHECK_rowCount(parent);
    if (!sourceModel() || parent.isValid())
        return 0;
    return sourceModel()->rowCount();
}

int ReverseRowsProxyModel::columnCount(const QModelIndex &parent) const
{
    CHECK_columnCount(parent);
    if (!sourceModel() || parent.isValid())
        return 0;
    return sourceModel()->columnCount();
}

QModelIndex ReverseRowsProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if (!proxyIndex.isValid())
        return {};
    return sourceModel()->index(mapRow(proxyIndex.row()), proxyIndex.column());
}

QModelIndex ReverseRowsProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if (!sourceIndex.isValid())
        return {};
    return index(mapRow(sourceIndex.row()), sourceIndex.column());
}

QVariant ReverseRowsProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
        return sourceModel()->headerData(section, Qt::Horizontal, role);
    else
        return sourceModel()->headerData(mapRow(section), Qt::Vertical, role);
}
/*
    index in source model  0  1  2  3  4  5  6  7  8
    mapped index in proxy  8  7  6  5  4  3  2  1  0
*/
int ReverseRowsProxyModel::mapRow(int row) const
{
    return (rowCount() - 1) - row;
}

void ReverseRowsProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    if (VERSION > 1) {
        if (auto *model = this->sourceModel()) {
            disconnect(model, nullptr, this, nullptr);
        }

        connect(sourceModel, &QAbstractItemModel::dataChanged, this,
                [this](const QModelIndex &topLeft, const QModelIndex &bottomRight,
                       const QVector<int> &roles) {
                    // Assuming 9 rows, a dataChange(2,30) -> (4,40) should result in
                    // dataChange ((9-1)-4, 30) -> ((9-1)-2, 40)

                    auto mappedTopLeft = mapFromSource(topLeft);
                    auto mappedBottomRight = mapFromSource(bottomRight);

                    auto newTopLeft = index(mappedBottomRight.row(), mappedTopLeft.column());
                    auto newBottomRight = index(mappedTopLeft.row(), mappedBottomRight.column());
                    emit dataChanged(newTopLeft, newBottomRight, roles);
                });

        /*
           When the source model emits the rowsAboutToBeInserted signal, the proxy model also needs
           to emit that signal. The values 'first' and 'last' points before the row. So if we have 8
           rows (as in the test cases) then there are 9 legal values 0 means insert before row 0 1
           means insert before row 1 9 means insert before row 9, which doesn't exist -- it means
           append at the end
        */
        connect(sourceModel, &QAbstractItemModel::rowsAboutToBeInserted, this,
                [this](const QModelIndex & /*parent*/, int first, int last) {
                    auto start = rowCount() - first;
                    auto end = start + last - first;
                    beginInsertRows({}, start, end);
                });

        connect(sourceModel, &QAbstractItemModel::rowsInserted, this, [this] { endInsertRows(); });

        connect(sourceModel, &QAbstractItemModel::rowsAboutToBeRemoved, this,
                [this](const QModelIndex & /*parent*/, int first, int last) {
                    beginRemoveRows({}, mapRow(last), mapRow(first));
                });

        connect(sourceModel, &QAbstractItemModel::rowsRemoved, this, [this] { endRemoveRows(); });

        connect(sourceModel, &QAbstractItemModel::columnsAboutToBeInserted, this,
                [this](const QModelIndex & /*parent*/, int first, int last) {
                    beginInsertColumns({}, first, last);
                });

        connect(sourceModel, &QAbstractItemModel::columnsInserted, this,
                [this] { endInsertColumns(); });

        connect(sourceModel, &QAbstractItemModel::columnsAboutToBeRemoved, this,
                [this](const QModelIndex & /*parent*/, int first, int last) {
                    beginRemoveColumns({}, first, last);
                });

        connect(sourceModel, &QAbstractItemModel::columnsRemoved, this,
                [this] { endRemoveColumns(); });

        connect(sourceModel, &QAbstractItemModel::rowsAboutToBeMoved, this,
                [this](const QModelIndex & /*sourceParent*/, int sourceStart, int sourceEnd,
                       const QModelIndex & /*destinationParent*/, int destinationRow) {
                    beginMoveRows({}, mapRow(sourceEnd), mapRow(sourceStart), {},
                                  mapRow(destinationRow));
                });

        connect(sourceModel, &QAbstractItemModel::rowsMoved, this, [this] { endMoveRows(); });

        connect(sourceModel, &QAbstractItemModel::columnsAboutToBeMoved, this,
                [this](const QModelIndex & /*sourceParent*/, int sourceStart, int sourceEnd,
                       const QModelIndex & /*destinationParent*/, int destinationColumn) {
                    beginMoveColumns({}, sourceStart, sourceEnd, {}, destinationColumn);
                });

        connect(sourceModel, &QAbstractItemModel::columnsMoved, this, [this] { endMoveColumns(); });

        connect(sourceModel, &QAbstractItemModel::headerDataChanged, this,
                [this](Qt::Orientation orientation, int first, int last) {
                    if (orientation == Qt::Horizontal)
                        emit headerDataChanged(orientation, first, last);
                    else
                        emit headerDataChanged(orientation, mapRow(last), mapRow(first));
                });

        connect(sourceModel, &QAbstractItemModel::modelAboutToBeReset, this,
                [this] { beginResetModel(); });

        connect(sourceModel, &QAbstractItemModel::modelReset, this, [this] { endResetModel(); });

        if (VERSION < 3) {
            connect(sourceModel, &QAbstractItemModel::layoutAboutToBeChanged, this,
                    [this] { beginResetModel(); });
            connect(sourceModel, &QAbstractItemModel::layoutChanged, this,
                    [this] { endResetModel(); });
        } else {
            connect(sourceModel, &QAbstractItemModel::layoutAboutToBeChanged, this,
                    [this](const QList<QPersistentModelIndex> & /*parents*/,
                           QAbstractItemModel::LayoutChangeHint hint) {
                        emit layoutAboutToBeChanged({}, hint);

                        m_ownPersistentIndexesForLayoutChange = persistentIndexList();
                        m_sourcePersistentIndexesForLayoutChange.reserve(
                            m_ownPersistentIndexesForLayoutChange.size());

                        std::transform(m_ownPersistentIndexesForLayoutChange.cbegin(),
                                       m_ownPersistentIndexesForLayoutChange.cend(),
                                       std::back_inserter(m_sourcePersistentIndexesForLayoutChange),
                                       [this](const QModelIndex &proxyIndex) {
                                           return QPersistentModelIndex(mapToSource(proxyIndex));
                                       });
                    });

            connect(sourceModel, &QAbstractItemModel::layoutChanged, this,
                    [this](const QList<QPersistentModelIndex> & /*parents*/,
                           QAbstractItemModel::LayoutChangeHint hint) {
                        // For each saved index in this model, figure out where the corresponding
                        // source index has moved to; use that to change our persistent model
                        // indexes.
                        QModelIndexList newOwnPersistentIndexes;
                        newOwnPersistentIndexes.reserve(
                            m_ownPersistentIndexesForLayoutChange.size());

                        std::transform(m_sourcePersistentIndexesForLayoutChange.cbegin(),
                                       m_sourcePersistentIndexesForLayoutChange.cend(),
                                       std::back_inserter(newOwnPersistentIndexes),
                                       [this](const QPersistentModelIndex &sourceIndex) {
                                           return mapFromSource(sourceIndex);
                                       });

                        changePersistentIndexList(m_ownPersistentIndexesForLayoutChange,
                                                  newOwnPersistentIndexes);

                        emit layoutChanged({}, hint);
                        m_ownPersistentIndexesForLayoutChange.clear();
                        m_sourcePersistentIndexesForLayoutChange.clear();
                    });
        }
    }
    beginResetModel();
    QAbstractProxyModel::setSourceModel(sourceModel);
    endResetModel();
}
