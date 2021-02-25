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

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    PlayListModel model;
    AllUpperCaseProxyModel proxyModel;

    proxyModel.setSourceModel(&model);

    QQuickView view;
    view.rootContext()->setContextProperty("_cppModel", &model);
    view.rootContext()->setContextProperty("_cppProxyModel", &proxyModel);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
