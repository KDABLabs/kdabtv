/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "durationsortproxymodel.h"
#include "playlistmodel.h"
#include "videofilterproxymodel.h"

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    PlayListModel model;

    VideoFilterProxyModel filterProxyModel;
    filterProxyModel.setSourceModel(&model);

    DurationSortProxyModel sortProxyModel;
    sortProxyModel.setSourceModel(&filterProxyModel);

    QQuickView view;
    view.rootContext()->setContextProperty("_cppModel", &model);
    view.rootContext()->setContextProperty("_cppFilterProxyModel", &filterProxyModel);
    view.rootContext()->setContextProperty("_cppSortProxyModel", &sortProxyModel);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
