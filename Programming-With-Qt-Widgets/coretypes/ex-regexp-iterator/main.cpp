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
    static QRegularExpression rx(
        R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)");
    QString subject("me-in@space.com, Jesper.Pedersen@kdab.com, @here");
    QRegularExpressionMatchIterator i = rx.globalMatch(subject);

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        qDebug() << match.captured();
    }

    return 0;
}
