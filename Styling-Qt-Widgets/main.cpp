/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "colorrepository.h"
#include "maindialog.h"
#include "teststyle.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QFile>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption qss("qss", "Use a Qt stylesheet instead of a widget style");
    parser.addOption(qss);
    QCommandLineOption nostyle("nostyle",
                               "Disable builtin styling; you can still pass --style to select another style like 'windows'");
    parser.addOption(nostyle);
    parser.addHelpOption();
    parser.process(app.arguments());

    const bool useStylesheet = parser.isSet(qss);
    QString styleSheetText;
    if (useStylesheet) {
        QFile styleSheetFile(":/stylesheet/stylesheet.qss");
        if (!styleSheetFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Couldn't find" << styleSheetFile.fileName();
        } else {
            styleSheetText = QString::fromUtf8(styleSheetFile.readAll());
        }
    } else if (!parser.isSet(nostyle)) {
        app.setStyle(new TestStyle);
    }
    app.setPalette(ColorRepository::standardPalette());

    auto dlg = new MainDialog(styleSheetText, parser.isSet(nostyle));
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();

    return app.exec();
}
