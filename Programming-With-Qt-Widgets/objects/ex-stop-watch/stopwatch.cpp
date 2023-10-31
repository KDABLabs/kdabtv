/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "stopwatch.h"

#include <QDebug>
#include <QTimer>

#include <chrono>

using namespace std::chrono_literals;

StopWatch::StopWatch(QObject *parent)
    : QObject(parent)
{
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StopWatch::addOneSecond);

    timer->start(1s);
}

void StopWatch::addOneSecond()
{
    m_secs += 1;

    const QString str = QString::asprintf("%d:%02d", m_secs / 60, m_secs % 60);

    qDebug() << str;
}
