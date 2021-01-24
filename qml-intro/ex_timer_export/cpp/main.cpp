/*************************************************************************
 *
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "randomtimer.h"

#include <QGuiApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app( argc, argv );

    qsrand( QDateTime::currentMSecsSinceEpoch() );

    // Expose the RandomTimer class
    qmlRegisterType<RandomTimer>( "CustomComponents", 1, 0, "RandomTimer" );

    QQuickView viewer;
    viewer.setSource( QUrl( "qrc:/main.qml" ) );
    viewer.show();

    return app.exec();
}
