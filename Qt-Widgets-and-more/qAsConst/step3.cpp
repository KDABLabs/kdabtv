#include <QDebug>
#include <QStringList>

namespace {
class Foo
{
public:
    void print() const
    {
        for (const QString &string : m_list) {
            qDebug() << string;
        }
    }

private:
    QStringList m_list{"a", "b", "c"};
};
}

void go3()
{
    qDebug() << "===== Step 3 =====";
    Foo foo;
    foo.print();
}
