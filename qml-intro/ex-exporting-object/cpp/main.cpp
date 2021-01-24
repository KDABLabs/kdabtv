/*************************************************************************
 *
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "User.h"
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQuick>
#include <QTimer>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    QQmlContext* context = view.engine()->rootContext();

    User user("Joe", QDate(1971, 07, 11), User::Developer);

    // Update the Role from C++ after 3 seconds.
    QTimer* timer = new QTimer(&app);
    timer->start(3000);
    QObject::connect(timer, &QTimer::timeout, &user, &User::changeRole);

    context->setContextProperty("_userData", &user);

    view.setSource(QUrl("qrc:main.qml"));
    view.show();
    return app.exec();
}
