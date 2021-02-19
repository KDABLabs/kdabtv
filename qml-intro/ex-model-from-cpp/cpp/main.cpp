/*************************************************************************
 *
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QGuiApplication>
#include <QQuickView>
#include <QStringListModel>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "mymodel.h"
int main( int argc, char** argv ) {
    QGuiApplication app( argc, argv );

    MyModel model;

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    QQmlContext *context = view.engine()->rootContext();
    context->setContextProperty("_myModel", &model);

    view.setSource(QUrl("qrc:main.qml"));
    view.show();

    return app.exec();
}
