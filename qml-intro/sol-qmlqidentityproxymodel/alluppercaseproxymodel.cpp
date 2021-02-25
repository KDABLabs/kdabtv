/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "alluppercaseproxymodel.h"

#include "playlistmodel.h"

AllUpperCaseProxyModel::AllUpperCaseProxyModel(QObject *parent)
    : QIdentityProxyModel(parent)
{
}

QVariant AllUpperCaseProxyModel::data(const QModelIndex &index, int role) const
{
    const QVariant value =  QIdentityProxyModel::data(index, role);

    if (role == PlayListModel::TitleRole) {
        const QString title = value.toString();
        return title.toUpper();
    }

    return value;
}
