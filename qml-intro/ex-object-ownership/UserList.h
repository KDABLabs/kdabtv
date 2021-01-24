/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef USERLIST_H
#define USERLIST_H

#include <QObject>
#include <QVector>

class User;

class UserList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int count READ count CONSTANT)

public:
    explicit UserList(QObject *parent = nullptr);
    ~UserList();

    int count() const;

    Q_INVOKABLE QObject* userAt(int index) const;

private:
    QVector<User*> m_users;
};

#endif
