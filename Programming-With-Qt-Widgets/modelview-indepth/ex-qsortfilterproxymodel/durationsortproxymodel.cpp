/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "durationsortproxymodel.h"

#include "playlistmodel.h"

DurationSortProxyModel::DurationSortProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    sort(0);
}

bool DurationSortProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    const int leftData = sourceLeft.data(PlayListModel::DurationRole).toInt();
    const int rightData = sourceRight.data(PlayListModel::DurationRole).toInt();

    return leftData < rightData;
}
