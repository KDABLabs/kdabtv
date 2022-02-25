#include "../EnumHelper.h"
#include "../Gadgets.h"
#include <QTest>

class GadgetsTest : public QObject
{
    Q_OBJECT

private slots:
    void gadget1();
};

void GadgetsTest::gadget1()
{
    QCOMPARE(EnumHelper::fromString<MyGadget::MyEnum>("Foo"), MyGadget::Foo);
}

QTEST_APPLESS_MAIN(GadgetsTest)

#include "tst_gadgets.moc"
