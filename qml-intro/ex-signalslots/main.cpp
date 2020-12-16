/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>
#include "myemitter.h"
#include "myreceiver.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyEmitter *emitter = new MyEmitter("Hello World");
    emitter->setAttribute(Qt::WA_DeleteOnClose);
    MyReceiver *receiver = new MyReceiver(&app);

    // Using old-style connect here to demonstrate the
    // interals of SIGNAL and SLOT
    QObject::connect(emitter, SIGNAL(aSignal()), receiver, SLOT(aSlot()));

    emitter->show();

    return app.exec();
}
