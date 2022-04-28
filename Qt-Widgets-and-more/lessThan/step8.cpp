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

    friend bool operator<(const Employee &lhs, const Employee &rhs)
    {
        return std::tie(lhs.m_name, lhs.m_age) < std::tie(rhs.m_name, rhs.m_age);
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

void go8()
{
    qDebug() << "==== Step 8 ======";
    QVector<Employee> employees{
        {"Maria", 20},
        {"Martina", 20},
        {"Mário", 30},
        {"Maria", 19},
    };
    std::sort(employees.begin(), employees.end());
    for (const auto &employee : employees)
        qDebug() << employee;
}
