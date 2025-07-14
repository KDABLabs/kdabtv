/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

#include "bargraphdelegate.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QTableView view;

    // create a model with 10 values (0, 10, 20, ... 90) and 3 columns
    QStandardItemModel model;
    for(int i=0; i<100; i += 10) {
        const QString formattedPercentage = QString::number(i) + '%';
        // set the percentage formatted as string as the Qt::DisplayRole;
        // set it as raw number as the Qt::UserRole.
        auto item1 = new QStandardItem(formattedPercentage);
        item1->setData(QVariant(i), Qt::UserRole);

        auto item2 = new QStandardItem(formattedPercentage);
        item2->setData(QVariant(i), Qt::UserRole);

        auto item3 = new QStandardItem(formattedPercentage);
        item3->setData(QVariant(i), Qt::UserRole);

        QList<QStandardItem *> items;
        items << item1 << item2 << item3;
        model.appendRow(items);
    }
    view.setModel(&model);

    BarGraphDelegate delegate;
    view.setItemDelegate(&delegate);

    view.resize(400, 400);
    view.show();
    return app.exec();
}

