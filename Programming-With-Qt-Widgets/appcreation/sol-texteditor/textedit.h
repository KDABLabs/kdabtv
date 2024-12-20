/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class TextEdit : public QTextEdit
{
public:
    explicit TextEdit(QWidget *parent = nullptr);

    bool save(const QString &fileName);
    bool load(const QString &fileName);
};

#endif // TEXTEDIT_H
