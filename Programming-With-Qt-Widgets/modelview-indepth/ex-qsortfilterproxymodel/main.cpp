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
#include "videofilterproxymodel.h"

#include <QApplication>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PlayListModel model;
    DurationSortProxyModel sortProxyModel;
    VideoFilterProxyModel filterProxyModel;

    filterProxyModel.setSourceModel(&model);
    sortProxyModel.setSourceModel(&filterProxyModel);

    QWidget widget;
    auto layout = new QHBoxLayout(&widget);

    auto leftView = new QListView;
    leftView->setModel(&model);

    auto rightView = new QListView;
    rightView->setModel(&sortProxyModel);

    auto checkbox = new QCheckBox;
    checkbox->setText("Enable Video Filter");
    checkbox->setChecked(true);

    layout->addWidget(leftView);
    layout->addWidget(rightView);
    layout->addWidget(checkbox);

    QObject::connect(checkbox, &QCheckBox::toggled,
                     &filterProxyModel, &VideoFilterProxyModel::setVideoFilterEnabled);

    QObject::connect(rightView, &QListView::clicked, [] (const QModelIndex& index) {
        qDebug("Playing %s with %s",
               qPrintable(index.data(PlayListModel::TitleRole).toString()),
               qPrintable(index.data(PlayListModel::ProducerRole).toString()));
    });
    widget.show();

    return app.exec();
}
