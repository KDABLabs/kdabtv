/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QApplication>
#include "widget.h"
#include "eventlogwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto logger = new EventLogWindow();
    logger->setAttribute(Qt::WA_DeleteOnClose);
    logger->resize(640, 240);
    logger->move(40, 0);
    logger->show();

    auto window = new Widget();
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->setLogAll(false); // does not log event(...) calls
    window->resize(240, 320);
    window->move(40, 320);
    window->show();

    QObject::connect(window, &Widget::notifyEvent,
                     logger, &EventLogWindow::logEvent);

    return app.exec();
}
