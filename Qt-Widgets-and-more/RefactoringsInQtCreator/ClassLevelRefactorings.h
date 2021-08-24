#pragma once

#include <QAbstractItemModel>

using UserID = int;
constexpr UserID NOEMPLOYEE = -1;

class ClassLevelRefactorings : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum class Column { Name, Salary, Role, NUMBEROFCOLUMNS };

protected:
    void reload();

private:
    QString m_department;
    UserID m_manager;
};
