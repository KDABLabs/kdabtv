/*************************************************************************
 *
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
//--> slide
#include <QMetaType>

class Contact
{
public:
    void setName( const QString& name );
    QString name() const;

private:
    QString m_name;
};

Q_DECLARE_METATYPE(Contact)
//<-- slide
#endif // CONTACT_H
