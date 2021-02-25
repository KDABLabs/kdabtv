/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef DURATIONSORTPROXYMODEL_H
#define DURATIONSORTPROXYMODEL_H

#include <QSortFilterProxyModel>

class DurationSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit DurationSortProxyModel(QObject *parent = nullptr);

protected:
    bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const override;
};

#endif // DURATIONSORTPROXYMODEL_H
