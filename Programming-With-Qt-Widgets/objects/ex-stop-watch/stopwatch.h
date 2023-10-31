/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>

class StopWatch : public QObject
{
    Q_OBJECT

public:
    explicit StopWatch(QObject *parent = nullptr);

private slots:
    void addOneSecond();

private:
    int m_secs = 0;
};

#endif
