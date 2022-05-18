#include <QDebug>
#include <QStringList>

namespace {
class Foo
{
public:
    explicit Foo(const QStringList &list)
        : m_list(list)
    {
    }
    void print()
    {
        for (const auto &list = generate(); const QString &string : list) {
            qDebug() << string;
        }
    }

private:
    QStringList generate() { return m_list; }
    QStringList m_list;
};

void caller()
{
    QStringList list{"a", "b", "c"};
    Foo foo(list);
    foo.print();
}
}

void go8()
{
    qDebug() << "===== Step 8 =====";
    caller();
}
