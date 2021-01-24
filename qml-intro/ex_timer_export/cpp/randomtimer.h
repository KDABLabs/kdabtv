/*************************************************************************
 *
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef RANDOMTIMER_H
#define RANDOMTIMER_H

#include <QObject>

#include <QtQuick>

class QTimer;

class RandomTimer : public QObject
{
    Q_OBJECT
    Q_PROPERTY( int interval READ interval WRITE setInterval NOTIFY intervalChanged )
    Q_PROPERTY( bool active READ isActive NOTIFY activeChanged )

public:
    explicit RandomTimer( QObject* parent = nullptr );

    void setInterval( int msec );
    int interval() const;

    bool isActive() const;

    Q_INVOKABLE int randomInterval( int min, int max ) const;

public slots:
    void start();
    void stop();

signals:
    void timeout();

    void intervalChanged();
    void activeChanged();

private:
    QTimer* m_timer;
};

#endif // RANDOMTIMER_H
