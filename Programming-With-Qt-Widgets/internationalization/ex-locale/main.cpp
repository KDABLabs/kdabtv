/*************************************************************************
 *
 * Copyright (c) 2024, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QCollator>
#include <QDateTime>
#include <QLocale>

void print(const QString &title, const QLocale &locale)
{
    QStringList letters{"a", "b", "c", "o", "ö", "p", "A", "B", "C", "O", "Ö", "P"};
    QCollator order(locale);
    std::sort(letters.begin(), letters.end(), order);

    qDebug().noquote() << "============================ " << title
                       << " ============================"
                       << "\n"
                       << "Name: " << locale.name() << "\n"
                       << "Territory: " << locale.territory() << "\n"
                       << locale.toString(12345.67) << "\n"
                       << locale.toString(QDateTime::currentDateTime()) << "\n"
                       << locale.toString(QDate::currentDate()) << "\n"
                       << locale.dayName(1, QLocale::ShortFormat) << "\n"
                       << letters;
}

int main()
{
    print("German", QLocale(QLocale::German));
    print("US English", QLocale(QLocale::English, QLocale::UnitedStates));
    print("British", QLocale(QLocale::English, QLocale::UnitedKingdom));
    print("Japanese", QLocale(QLocale::Japanese));
    print("System", QLocale::system());
    print("C", QLocale::c());
}
