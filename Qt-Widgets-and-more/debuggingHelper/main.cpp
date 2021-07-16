#include "Money.h"
#include <QtWidgets>
#include <variant>

// == = Part 1 == =
struct Foo
{
    int i = 10;
    int j = 20;
};

struct Bar
{
    QString str = "Hi";
};

void part1()
{
    Foo foo;
    QSize size(100, 200);
    qDebug("Break point point");
}

// == = Part 2 == =
namespace MyNameSpace {
struct Foo
{
    int i = 10;
    QStringList list = {"Qt", "Widgets", "and", "More"};
};
}

void part2()
{
    MyNameSpace::Foo nsfoo;
    qDebug("Break point point");
}

// == = Part 3/4 == =
void part34()
{
    Money m(Money::EUR, 100);
    Money m1();
    qDebug("Break point point");
}

// == = Part 5 == =
using FooOrBar = std::variant<Foo, Bar>;

QString fooOrBarToString(const FooOrBar &value)
{
    if (std::holds_alternative<Foo>(value)) {
        auto foo = std::get<Foo>(value);
        return QString("Foo(%1,%2)").arg(foo.i).arg(foo.j);
    } else {
        auto bar = std::get<Bar>(value);
        return QString("Bar(%1)").arg(bar.str);
    }
}

void part5()
{
    FooOrBar foo = Foo();
    FooOrBar bar = Bar();
    qDebug("Break point point");
}

//== = Part 6 == =
using UserID = int;
using UserIDList = QList<UserID>;

class EmployeeDatabase
{
public:
    static EmployeeDatabase &instance()
    {
        static EmployeeDatabase db;
        return db;
    }
    QString lookup(UserID id)
    {
        if (id == 1)
            return "David Gahan";
        if (id == 2)
            return "Martin Gore";
        if (id == 3)
            return "Andrew Fletcher";
        return "Rick Astley";
    }

private:
    EmployeeDatabase() = default;
};

void part6()
{
    UserID a{1};
    qDebug() << EmployeeDatabase::instance().lookup(a);
    UserIDList list{1, 2};
    qDebug("Break point point");
}

int main()
{
    part1();
    part2();
    part34();
    part5();
    part6();
}
