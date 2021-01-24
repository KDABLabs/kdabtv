/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "UserList.h"

#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    UserList userList;

    QQuickView view;
    view.rootContext()->setContextProperty("_userList", &userList);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return app.exec();
}
