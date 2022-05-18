#include <QDebug>
#include <QStringList>

namespace {
class Foo
{
public:
    void print()
    {
        for (const QString &string : generate()) {
            qDebug() << string;
        }
    }

private:
    const QStringList generate() { return QStringList{"a", "b", "c"}; }
};
}

void go7()
{
    qDebug() << "===== Step 7 =====";
    Foo foo;
    foo.print();
}
