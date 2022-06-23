#include <QCoreApplication>
#include <QDebug>
#include <QLocale>
#include <QVariant>

int main()
{
    qDebug() << QVariant(200'000.0).toString();
    qDebug() << QString::number(200'000.0, 'g', QLocale::FloatingPointShortest);
}
