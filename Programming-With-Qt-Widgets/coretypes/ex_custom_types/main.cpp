/*****************************************************************************************
 *
 * Copyright (c) 2012, Klaralvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 ******************************************************************************************/

#include <QApplication>
#include "Contact.h"
#include <QVariant>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Contact contact;
    contact.setName("Peter");

    const QVariant variant = QVariant::fromValue(contact);

    const Contact cotherContact = variant.value<Contact>();
    qDebug() << cotherContact.name();
    qDebug() << variant.typeName();
    qDebug() << "QVariant::typeId() :" << variant.typeId();
    qDebug() << "QVariant::userType():" << variant.userType();
    qDebug() << "qMetaTypeId<Contact>():" << qMetaTypeId<Contact>();

    return 0;
}
