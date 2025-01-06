/*************************************************************************
 *
 * Copyright (c) 2024, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTranslator translator;
    bool ok = translator.load(QLocale(), "plural_handling", "_", ":/i18n/");
    if (!ok)
        qDebug("Failed to open translation file.");
    app.installTranslator(&translator);

    QString big = QCoreApplication::translate("main", "big");
    QString red = QCoreApplication::translate("main", "red");

    qDebug() << QCoreApplication::translate("main", "Press the %1 %2 button").arg(big, red);
    for (int i = 0; i < 3; ++i)
        qDebug() << QCoreApplication::translate("main", "Loaded %n files(s)", nullptr, i);
}
