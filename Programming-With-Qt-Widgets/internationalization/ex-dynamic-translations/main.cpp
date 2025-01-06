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
namespace {
QTranslator translator;
QTranslator qtTranslator;
} // namespace

void setLanguage(const QString &locale)
{
    bool ok = translator.load("editor_" + locale, ":/i18n/");
    if (!ok)
        qDebug("Failed to open translation file.");

    ok = qtTranslator.load("qt_" + locale, ":/translations");
    if (!ok)
        qDebug("Failed to open Qt's translation file.");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setLanguage("en");
    QApplication::installTranslator(&translator);
    QApplication::installTranslator(&qtTranslator);

    Editor editor;
    editor.show();
    QObject::connect(&editor, &Editor::languageChangeRequested, setLanguage);

    return QCoreApplication::exec();
}
