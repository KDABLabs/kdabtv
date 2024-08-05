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

void parse(const QString &str) {
    static QRegularExpression rx(R"(^(\d?\d)/(\d?\d)/((\d\d)?\d\d)$)");
    auto match = rx.match(str);
    if (match.hasMatch()) {
        qDebug().noquote() << "Input: " << str.rightJustified(10)
                           << "day:" << match.captured(1).rightJustified(2)
                           << "month:" << match.captured(2).rightJustified(2)
                           << "year:" << match.captured(3).rightJustified(4);
        qDebug() << match.capturedTexts() << "\n";
    } else {
        qWarning().noquote().nospace() << "String \"" << str << "\" didn't match";
    }
}

int main() {
    parse("11/07/1971");
    parse("11/7/1971");
    parse("1/7/1971");
    parse("11/7/71");
    parse("11/07/71");
    parse("1971-07-11");

    return 0;
}
