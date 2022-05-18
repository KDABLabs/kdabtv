#include <QDebug>
#include <QStringList>

namespace {
class Foo
{
public:
    void print()
    {
        for (const QString &string : m_list) {
            qDebug() << string;
        }
    }

private:
    QStringList m_list{"a", "b", "c"};
};
}

void go1()
{
    qDebug() << "===== Step 1 =====";
    Foo foo;
    foo.print();
}
