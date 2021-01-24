/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "UserList.h"

#include "User.h"

#include <QQmlEngine>

UserList::UserList(QObject *parent)
    : QObject(parent)
{
    // create QObjects without parent

    m_users << new User("Jane");
    m_users << new User("John");
    m_users << new User("Joe");
    m_users << new User("Jules");
}

UserList::~UserList()
{
    qDeleteAll(m_users);
}

int UserList::count() const
{
    return m_users.count();
}

QObject* UserList::userAt(int index) const
{
    if (index < 0 || index >= m_users.count())
        return nullptr;

    // Uncomment line below to fix the crash
    //QQmlEngine::setObjectOwnership(m_users[index], QQmlEngine::CppOwnership);

    return m_users[index];
}
