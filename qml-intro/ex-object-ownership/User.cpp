/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "User.h"

User::User(const QString &name)
    : m_name(name)
{
}

User::~User()
{
    qDebug("User %s destroyed", qPrintable(m_name));
}
