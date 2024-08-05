/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "Contact.h"
#include <QObject>
#include <QCoreApplication>

class Sender :public QObject
{
    Q_OBJECT

public:
    void send()
    {
        Contact santa( "Santa Claus" );
        emit data( santa );
    }

signals:
    void data(const Contact& );
};


class Receiver :public QObject
{
    Q_OBJECT

public slots:
    void setContact( const Contact& contact )
    {
        qDebug("Got contact: %s", qPrintable(contact.name()));
        QCoreApplication::quit();
    }
};


int main( int argc, char** argv ) {
    QCoreApplication app( argc, argv );

    // First, try commenting this line out
    qRegisterMetaType<Contact>();

    Sender sender;
    Receiver receiver;

    // Next, try these variants
    //QObject::connect( &sender, SIGNAL(data(Contact)), &receiver, SLOT(setContact(Contact)) ); // works
    QObject::connect( &sender, SIGNAL(data(Contact)),
                      &receiver, SLOT(setContact(Contact)),
                      Qt::QueuedConnection ); // fails
    //QObject::connect( &sender, &Sender::data, &receiver, &Receiver::setContact ); // works
    //QObject::connect( &sender, &Sender::data, &receiver, &Receiver::setContact, Qt::QueuedConnection ); // works
    sender.send();

    return app.exec();
}

#include "main.moc"
