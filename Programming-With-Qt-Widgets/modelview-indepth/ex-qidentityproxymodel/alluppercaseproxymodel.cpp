/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "alluppercaseproxymodel.h"

#include <QColor>

AllUpperCaseProxyModel::AllUpperCaseProxyModel(QObject *parent)
    : QIdentityProxyModel(parent)
{
}

QVariant AllUpperCaseProxyModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(checkIndex(index, CheckIndexOption::IndexIsValid));

    const QVariant value = QIdentityProxyModel::data(index, role);

    if (role == Qt::DisplayRole) {
        const QString title = value.toString();
        return title.toUpper();
    }

    return value;
}
