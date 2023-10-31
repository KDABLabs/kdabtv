/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "myemitter.h"

MyEmitter::MyEmitter(const QString &label, QWidget *parent)
    : QPushButton(label, parent)
{
    connect(this, &QPushButton::clicked, this, &MyEmitter::sendSignal);
}

void MyEmitter::sendSignal()
{
    emit aSignal();
}
