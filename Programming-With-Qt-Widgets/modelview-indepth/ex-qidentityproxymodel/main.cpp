/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "alluppercaseproxymodel.h"
#include "playlistmodel.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PlayListModel model;
    AllUpperCaseProxyModel proxyModel;

    proxyModel.setSourceModel(&model);

    QWidget widget;
    auto layout = new QHBoxLayout(&widget);

    auto leftView = new QListView;
    leftView->setModel(&model);

    auto rightView = new QListView;
    rightView->setModel(&proxyModel);

    layout->addWidget(leftView);
    layout->addWidget(rightView);

    widget.show();

    return app.exec();
}
