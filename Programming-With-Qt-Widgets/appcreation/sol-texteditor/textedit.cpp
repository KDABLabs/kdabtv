/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "textedit.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

TextEdit::TextEdit(QWidget *parent)
    : QTextEdit(parent)
{

}

bool TextEdit::save(const QString &fileName)
{
    QFile f(fileName);
    if ( !f.open(QIODevice::WriteOnly) ) {
        qWarning().nospace() << "Couldn't open file " << fileName << ": " << f.errorString();
        return false;
    }

    QTextStream t(&f);
    t << toPlainText();
    return true;
}

bool TextEdit::load(const QString &fileName)
{
    QFile f(fileName);
    if ( !f.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qWarning().nospace() << "Couldn't open file " << fileName << ": " << f.errorString();
        return false;
    }

    QTextStream stream(&f);
    setPlainText(stream.readAll());
    return true;
}

