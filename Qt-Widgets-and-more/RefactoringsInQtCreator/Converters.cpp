#include "Converters.h"
#include <QDebug>
#include <QPushButton>
#include <QString>
#include <algorithm>

using namespace std;

void Converters::test(int foo, bool bar)
{
    int flag = 256;
    const QString txt = "Game Over";
    const QString øl = "Mere ØL!";

    QStringList l;
    auto it = l.cbegin();

    int also256 = 256 + 256;

    QPushButton *ok = new QPushButton("OK");

    QString *name = new QString("Jesper");
    qDebug() << name->length();

    QList<int> intList{1, 5, 2};
    QStringList result;
    transform(intList.cbegin(), intList.cend(), std::back_inserter(result),
              [](int i) { return QString::number(i); });

    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(go()));
}

void Converters::go() { }

void Converters::complexStuff()
{
    int dummy = 0;
    if (dummy < 10)
        ++dummy;
}
