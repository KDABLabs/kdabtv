/* MIT License

Copyright (C) 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "PercentageValue.h"
#include <cmath>

static auto dummy = QMetaType::registerConverter(&PercentageValue::toString);

PercentageValue::PercentageValue(double value, int printDigits)
    : m_value(value)
    , m_printDigits(printDigits)
{
}

double PercentageValue::value() const
{
    return m_value;
}

int PercentageValue::digits() const
{
    return m_printDigits;
}

QString PercentageValue::toString() const
{
    if (std::isinf(m_value) || std::isnan(m_value))
        return "-";
    else
        return QString("%L1 %").arg(100 * m_value, 0, 'f', m_printDigits);
}

bool operator<(const PercentageValue &x, const PercentageValue &y)
{
    return std::tie(x.m_value, x.m_printDigits) < std::tie(y.m_value, y.m_printDigits);
}

bool operator<=(const PercentageValue &x, const PercentageValue &y)
{
    return x < y || x == y;
}

bool operator!=(const PercentageValue &x, const PercentageValue &y)
{
    return !(x == y);
}

bool operator==(const PercentageValue &x, const PercentageValue &y)
{
    return x.m_printDigits == y.m_printDigits && x.m_value == y.m_value;
}

bool PercentageValue::isInf() const
{
    return std::isinf(m_value);
}
