#include <QDebugStateSaver>
#include <QString>
#include <tuple>

namespace {

class Employee
{
public:
    Employee(const QString &name, int age)
        : m_name(name)
        , m_age(age)
    {
    }

    static bool byName(const Employee &lhs, const Employee &rhs)
    {
        return lhs.m_name.localeAwareCompare(rhs.m_name) < 0;
    }

    static bool byAge(const Employee &lhs, const Employee &rhs) { return lhs.m_age < rhs.m_age; }

    static bool byNameAndAge(const Employee &lhs, const Employee &rhs)
    {
        const int cmp = lhs.m_name.localeAwareCompare(rhs.m_name);
        if (cmp != 0)
            return cmp < 0;
        return lhs.m_age < rhs.m_age;
    }

    friend QDebug operator<<(QDebug debug, const Employee &foo)
    {
        QDebugStateSaver dummy(debug);
        debug.noquote().nospace() << foo.m_name << " (" << foo.m_age << " years old)";
        return debug;
    }

private:
    QString m_name;
    int m_age;
};
}

void go9()
{
    QVector<Employee> employees{
        {"Maria", 20},
        {"Martina", 20},
        {"Mário", 30},
        {"Maria", 19},
    };
    qDebug() << "==== Step 9 (sort by name and age) ======";
    std::sort(employees.begin(), employees.end(), &Employee::byNameAndAge);
    for (const auto &employee : employees)
        qDebug() << employee;

    qDebug() << "==== Step 9 (sort by name) ======";
    std::sort(employees.begin(), employees.end(), &Employee::byName);
    for (const auto &employee : employees)
        qDebug() << employee;

    qDebug() << "==== Step 9 (sort by age) ======";
    std::sort(employees.begin(), employees.end(), &Employee::byAge);
    for (const auto &employee : employees)
        qDebug() << employee;
}
