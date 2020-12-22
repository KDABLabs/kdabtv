/*************************************************************************
 *
 * Copyright (c) 2017-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "window.h"

#include <QDebug>
#include <QGuiApplication>

static void printWindowPosition(const QPoint &point)
{
    qDebug() << "new window position is" << point;
}

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    Window window;
    window.show();

    QObject::connect(&window, &Window::positionChanged, printWindowPosition);

    return app.exec();
}
