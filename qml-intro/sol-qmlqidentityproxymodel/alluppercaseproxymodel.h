/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef ALLUPPERCASEPROXYMODEL_H
#define ALLUPPERCASEPROXYMODEL_H

#include <QIdentityProxyModel>

class AllUpperCaseProxyModel : public QIdentityProxyModel
{
    Q_OBJECT

public:
    explicit AllUpperCaseProxyModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // ALLUPPERCASEPROXYMODEL_H
