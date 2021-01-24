/*************************************************************************
 *
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDate>

//--> slide
class User : public QObject
{
    Q_OBJECT
    //--> hide
    Q_PROPERTY( QString name READ name WRITE setName NOTIFY nameChanged )

    // We don't want to be able to change the age from QML, hence the read only age
    // Further, notice that age is not an instance variable.
    Q_PROPERTY( int age READ age NOTIFY ageChanged )

    Q_PROPERTY( Role role READ role NOTIFY roleChanged )
    Q_PROPERTY( bool loggedIn READ loggedIn WRITE setLoggedIn NOTIFY loginChanged )
    //<-- hide

public:
    enum Role { Developer = 0, Tester = 1, ProjectManager = 2 };
    Q_ENUM( Role )
    //--> hide

    explicit User(const QString name = QString(), const QDate& birthday = QDate(), Role role = Developer);

    QString name() const;
    void setName(const QString& name );

    int age() const;

    Role role() const;
    void setRole(Role);

    bool loggedIn() const;
    void setLoggedIn(bool loggedIn);

public slots:
    void changeRole();

signals:
    void nameChanged();
    void ageChanged();
    void roleChanged();
    void loginChanged(bool loggedIn);

private:
    QString m_name;
    QDate m_birthDay;
    Role m_role;
    bool m_loggedIn = false;
    //<-- hide
};
//<-- slide

#endif // USER_H
