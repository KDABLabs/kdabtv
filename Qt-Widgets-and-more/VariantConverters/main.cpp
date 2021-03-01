#include <QApplication>
#include <QColor>
#include <QDebug>

#define QVARIANTMACRO()                                                                            \
    inline operator QVariant() const { return QVariant::fromValue(*this); }

class Foo
{
public:
    Foo(int x = 0)
        : x(x)
    {
    }
    QVARIANTMACRO();

private:
    int x;
};

class Bar
{
public:
    Bar(const QString &s = "")
        : s(s)
    {
    }
    QVARIANTMACRO();

private:
    QString s;
};

QVariant data()
{
    return Foo();
}

int main()
{
    Foo f(1);
    Bar b("Hi");

    QVariant fv = f;
    QVariant bv = b;
#if 0 // I'd like this repos to be in a compilable state
    if (f == b)
        qDebug("Fortunately this doesn't compile");
    if (f < b)
        qDebug("Fortunately this doesn't compile");
#endif

    if (f == bv)
        qDebug("Ooops, I didn't mean to compare == with variants, this makes no sense.");
    if (fv < bv)
        qDebug("Ooops, I didn't mean to compare < with variants, this makes no sense.");

    // Careful when you want to return an empty variant from your data
    QVariant v1 = (false ? QVariant::fromValue(QColor(Qt::red)) : QVariant());
    Q_ASSERT(v1.isNull());

    // This is the right way to return a null variant
    QVariant v2 = (false ? QColor(Qt::red) : QVariant());
    Q_ASSERT(v2.isNull());

    // This, however, is the tempting way, but it returns a valid variant with a null color in it.
    QVariant v3 = (false ? QColor(Qt::red) : QColor());
    Q_ASSERT(!v3.isNull());
    Q_ASSERT(!v3.value<QColor>().isValid());

    // If you want to return a variant from a lambda, remember to specify the return type.
    auto fun = [](bool b) -> QVariant {
        if (b)
            return QColor("blue");
        else
            return "Yo";
    };

    qDebug() << fun(true);
}

Q_DECLARE_METATYPE(Foo)
Q_DECLARE_METATYPE(Bar)
