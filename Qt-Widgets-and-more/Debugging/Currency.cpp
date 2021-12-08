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

#include "Currency.h"
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(MoneyLog)

Currency::Currency(Currency::Type value)
    : m_value(value)
{
    qCInfo(MoneyLog) << "Creating currency" << value;
}

const Currency::Currencies Currency::currencies()
{
    Currencies result;
    for (int i = 0; i <= Currency::JPY; ++i)
        result.append(static_cast<Currency::Type>(i));
    return result;
}

Currency::Type Currency::type() const
{
    return m_value;
}

QString Currency::toString() const
{
    switch (m_value) {
    case SEK:
        return "kr";
    case EUR:
        return "€";
    case GBP:
        return "£";
    case USD:
        return "$";
    case JPY:
        return "‎¥";
    }
    Q_ASSERT(false);
    return {};
}
