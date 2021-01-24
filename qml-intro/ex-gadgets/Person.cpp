/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "Person.h"


Person::Person(const QString& name, int age)
    : m_name(name), m_age(age)
{
}

Person::Person()
{
}

QString Person::toString() const
{
    return QString("Person(%1, %2)").arg(m_name).arg(m_age);
}

QString Person::name() const
{
    return m_name;
}

int Person::age() const
{
    return m_age;
}

bool Person::operator!=(const Person& other) const
{
    return !(*this == other);
}

bool Person::operator==(const Person& other) const
{
    return ((m_name == other.m_name && m_age == other.m_age));
}
