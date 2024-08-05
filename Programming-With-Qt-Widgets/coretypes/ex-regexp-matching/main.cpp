/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

int main() {
    // Matches DD/MM/YYYY format with optional leading zero for day and month
    static QRegularExpression rx("^\\d?\\d/\\d?\\d/(\\d\\d)?\\d\\d$");

    qDebug() << rx.match("11/07/1971").hasMatch();
    qDebug() << rx.match("11/7/1971").hasMatch();
    qDebug() << rx.match("1/7/1971").hasMatch();
    qDebug() << rx.match("11/7/71").hasMatch();
    qDebug() << rx.match("11/07/71").hasMatch();
    qDebug() << rx.match("1971-07-11").hasMatch();

    QString str("11/07/1971");
    qDebug() << str.contains(rx);
    return 0;
}
