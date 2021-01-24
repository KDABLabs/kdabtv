/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef PERSON_H
#define PERSON_H

#include <QMetaType>
#include <QMetaObject>
#include <QString>

class Person
{
    Q_GADGET

    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(int age MEMBER m_age)

public:
    Person(const QString& name, int age);
    Person();

    Q_INVOKABLE QString toString() const;

    QString name() const;
    int age() const;

    bool operator!=(const Person& other) const;
    bool operator==(const Person& other) const;

private:
    QString m_name;
    int m_age;
};

#endif // PERSON_H
