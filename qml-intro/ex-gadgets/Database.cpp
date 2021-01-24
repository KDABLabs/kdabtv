/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "Database.h"

Database::Database(QObject* parent) : QObject(parent)
{
    addPerson(Person("Fake Santa", 65));
}

Person Database::lookup(const QString& name) const
{
    return m_persons.value(name, Person("Unknown", -1));
}

Person Database::makePerson(const QString& name, int age)
{
    return Person(name, age);
}

void Database::addPerson(const Person& person)
{
    m_persons.insert(person.name(), person);
}
