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
    QStringList generate() { return QStringList{"a", "b", "c"}; }
};
}

void go5()
{
    qDebug() << "===== Step 5 =====";
    Foo foo;
    foo.print();
}
