/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef MYRECEIVER_H
#define MYRECEIVER_H

#include <QObject>

class MyReceiver : public QObject
{
    Q_OBJECT

public:
    explicit MyReceiver(QObject *parent = nullptr);

public slots:
    void aSlot();
    void anOtherSlot(int, QObject *);
};

#endif // MYRECEIVER_H
