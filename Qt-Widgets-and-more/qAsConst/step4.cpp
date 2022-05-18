#include <QDebug>
#include <QStringList>

namespace {
class Foo
{
public:
    void print()
    {
        for (const QString &string : qAsConst(m_list)) {
            qDebug() << string;
        }
    }

private:
    QStringList m_list{"a", "b", "c"};
};
}

void go4()
{
    qDebug() << "===== Step 4 =====";
    Foo foo;
    foo.print();
}
