#include "../EnumHelper.h"
#include "../NewWay.h"
#include <QTest>

class BasicsTest : public QObject
{
    Q_OBJECT

private slots:
    void fromString();
    void toString();
    void failToConvert();

    void allEnums();
    void allEnums_data();
};

void BasicsTest::fromString()
{
    QCOMPARE(EnumHelper::fromString<Example::ExampleEnum>("Foo"), Example::ExampleEnum::Foo);
}

void BasicsTest::toString()
{
    QCOMPARE(EnumHelper::toString(Example::ExampleEnum::Foo), "Foo");
}

void BasicsTest::failToConvert()
{
    QTest::ignoreMessage(QtWarningMsg, R"(Failed to convert enum "Fooooo")");
    QCOMPARE(EnumHelper::fromString<Example::ExampleEnum>("Fooooo"), Example::ExampleEnum());
}

void BasicsTest::allEnums()
{
    QFETCH(Example::ExampleEnum, enumValue);
    QFETCH(QString, expected);

    QCOMPARE(EnumHelper::toString(enumValue), expected);
}

void BasicsTest::allEnums_data()
{
    QTest::addColumn<Example::ExampleEnum>("enumValue");
    QTest::addColumn<QString>("expected");

    QTest::newRow("foo") << Example::ExampleEnum::Foo << "Foo";
    QTest::newRow("bar") << Example::ExampleEnum::Bar << "Bar";
    QTest::newRow("baz") << Example::ExampleEnum::Baz << "Baz";
}

QTEST_MAIN(BasicsTest)

#include "tst_basics.moc"
