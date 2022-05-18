#include <QDebug>
#include <QStringList>

namespace {
class Foo
{
public:
    void print()
    {
        const auto &constRefList = m_list;
        for (const QString &string : constRefList) {
            qDebug() << string;
        }
    }

private:
    QStringList m_list{"a", "b", "c"};
};
}

void go2()
{
    qDebug() << "===== Step 2 =====";
    Foo foo;
    foo.print();
}
