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

#pragma once
#include "strong_typedef.hpp"
#include <QDebug>

// Tool to convert a strong_typedef to its underlying value
template <typename Tag, typename ValueType, typename... Properties>
constexpr auto &operator+(const jss::strong_typedef<Tag, ValueType, Properties...> &e) noexcept
{
    return e.underlying_value();
}

namespace jss {
template <typename Tag, typename ValueType, typename... Properties>
constexpr size_t qHash(const jss::strong_typedef<Tag, ValueType, Properties...> &e,
                       uint seed = 0) noexcept(noexcept(qHash(e.underlying_value(), seed)))
{
    return qHash(e.underlying_value(), seed);
}

template <typename Tag, typename ValueType, typename... Properties>
QDebug operator<<(QDebug &dbg, const jss::strong_typedef<Tag, ValueType, Properties...> &e)
{
    return dbg << e.underlying_value();
}
}
