#include "Money.h"
#include <QDebug>
#include <QVariant>

void test(const QVariant &x, const QVariant &y)
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    if (x < y)
        qDebug() << x << "<" << y;
    if (x > y)
        qDebug() << x << ">" << y;
    if (x == y)
        qDebug() << x << "==" << y;
#else
    auto result = QVariant::compare(x, y);
    if (result == QPartialOrdering::Unordered) {
        qDebug() << x << "and" << y << "are unordered";
        return;
    }
    if (result < 0)
        qDebug() << x << "<" << y;
    if (result > 0)
        qDebug() << x << ">" << y;
    if (result == 0)
        qDebug() << x << "==" << y;
#endif
}

int main()
{
#if 0
    QMetaType::registerComparators<Money>();
#endif

    QVariant v1(10);
    QVariant v2(20);
    QVariant str("Hello");

    QVariant amount1 = QVariant::fromValue(Money(Money::EUR, 100));
    QVariant amount2 = QVariant::fromValue(Money(Money::EUR, 30));
    QVariant amount3 = QVariant::fromValue(Money(Money::USD, 1000));

    test(v1, v2);
    test(v2, v1);
    test(v1, v1);
    test(v1, str);
    test(str, v1);
    test(amount1, amount2);
    test(amount1, amount3);
}
