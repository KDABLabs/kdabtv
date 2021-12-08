/* MIT License

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Money.h"
#include <QDebug>
#include <QLoggingCategory>
#include <QString>

Q_LOGGING_CATEGORY(MoneyLog, "QWAM.Money", QtWarningMsg)

Money::Money(Currency currency, double amount)
    : m_valid(true)
    , m_currency(currency)
    , m_amount(amount)
{
    qCDebug(MoneyLog) << "Create Money instance ";
}

Currency Money::currency() const
{
    return m_currency;
}

double Money::amount() const
{
    return m_amount;
}

QString Money::toString() const
{
    if (!m_valid)
        return QString("NOTHING");
    else
        return QString("%1%2").arg(m_currency.toString()).arg(m_amount, 0, 'f', 2);
}

QDebug operator<<(QDebug debug, const Money &money)
{
    QDebugStateSaver dummy(debug);
    debug.noquote() << money.toString();
    return debug;
}
