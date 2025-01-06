/*************************************************************************
 *
 * Copyright (c) 2024, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "Editor.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    bool ok = translator.load(QLocale(), "editor", "_", ":/i18n/");
    if (!ok)
        qDebug("Failed to open translation file.");
    app.installTranslator(&translator);

    QTranslator qtTranslator;
    ok = qtTranslator.load(QLocale(), "qt", "_", ":/translations");
    if (!ok)
        qDebug("Failed to open Qt's translation file.");
    app.installTranslator(&qtTranslator);

    Editor editor;
    editor.show();
    return QCoreApplication::exec();
}
