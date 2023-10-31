/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <QPushButton>

class MyEmitter : public QPushButton
{
    Q_OBJECT

public:
    explicit MyEmitter(const QString &label, QWidget *parent = nullptr);

signals:
    void aSignal();
    void anOtherSignal(int, QWidget *);

private:
    void sendSignal();
};

#endif // MYSIGNAL_H
