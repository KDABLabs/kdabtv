/*************************************************************************
 *
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "User.h"


User::User(const QString name, const QDate& birthDay, Role role)
    : m_name(name), m_birthDay(birthDay), m_role(role)
{
}

QString User::name() const
{
    return m_name;
}

void User::setName(const QString &name)
{
    if ( name == m_name )
        return;
    m_name = name;
    emit nameChanged();
}

int User::age() const
{
    // Yes I know the code is broken if you haven't had the birthday this year yet
    // It's an exercises for the interested student to fix :-)

    // Further, notice we would have to set up a signal to fire when we reaches his birthday.
    return QDate::currentDate().year() - m_birthDay.year();
}

User::Role User::role() const
{
    return m_role;
}

void User::setRole(User::Role role)
{
    if ( role == m_role )
        return;

    m_role = role;
    emit roleChanged();
}

bool User::loggedIn() const
{
    return m_loggedIn;
}

void User::setLoggedIn(bool loggedIn)
{
    if (loggedIn == m_loggedIn)
        return;

    m_loggedIn = loggedIn;
    emit loginChanged(loggedIn);
}

void User::changeRole()
{
    setRole(m_role == User::Developer ? User::ProjectManager : User::Developer);
}
