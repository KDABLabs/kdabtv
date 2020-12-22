/*************************************************************************
 *
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

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
    qDebug() << "QVariant::type() == QVariant::UserType:" << (variant.type() == QVariant::UserType);
    qDebug() << "QVariant::userType():" << variant.userType();
    qDebug() << "qMetaTypeId<Contact>():" << qMetaTypeId<Contact>();

    return 0;
}
