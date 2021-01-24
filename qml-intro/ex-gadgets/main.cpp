/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "Database.h"
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <qqml.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    qRegisterMetaType<Person>();

    view.engine()->rootContext()->setContextProperty("_santa", QVariant::fromValue(Person("Santa", 256)));

    Database db;
    view.engine()->rootContext()->setContextProperty("_db", &db);

    view.setSource(QUrl("qrc:main.qml"));
    view.show();
    return app.exec();
}
