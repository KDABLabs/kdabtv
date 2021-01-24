/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDateTime>

//--> slide
int main(int argc, char *argv[])
{
    //--> hide
    QGuiApplication app(argc, argv);
    //<-- hide
    // ...
    QQuickView view;
    QQmlContext* context = view.engine()->rootContext();
    context->setContextProperty("_aString", QString("KDAB"));
    context->setContextProperty("_aSize", QSize(800,600));
    context->setContextProperty("_today", QDateTime::currentDateTime());
    // ...
    //--> hide
    view.setSource(QUrl("qrc:main.qml"));
    view.show();
    return app.exec();
    //<-- hide
}
//<-- slide
