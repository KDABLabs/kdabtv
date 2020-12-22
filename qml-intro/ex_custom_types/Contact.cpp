/*************************************************************************
 *
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "Contact.h"

void Contact::setName(const QString &name)
{
    if ( m_name != name )
        m_name = name;
}

QString Contact::name() const
{
    return m_name;
}
