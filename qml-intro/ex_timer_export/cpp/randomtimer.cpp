/*************************************************************************
 *
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "randomtimer.h"

#include <QDebug>
#include <QTimer>

RandomTimer::RandomTimer( QObject* parent )
    : QObject( parent ),
      m_timer( new QTimer( this ) )
{
    connect( m_timer, &QTimer::timeout, this, &RandomTimer::timeout );
}

void RandomTimer::setInterval( int msec )
{
    if ( m_timer->interval() == msec )
        return;
    m_timer->setInterval( msec );
    emit intervalChanged();
}

int RandomTimer::interval() const
{
    return m_timer->interval();
}

bool RandomTimer::isActive() const
{
    return m_timer->isActive();
}

int RandomTimer::randomInterval( int min, int max ) const
{
    int range = max - min;
    int msec = min + qrand() % range;
    qDebug() << "Random interval =" << msec << "msecs";
    return msec;
}

void RandomTimer::start()
{
    if ( m_timer->isActive() )
        return;
    m_timer->start();
    emit activeChanged();
}

void RandomTimer::stop()
{
    if ( !m_timer->isActive() )
        return;
    m_timer->stop();
    emit activeChanged();
}
