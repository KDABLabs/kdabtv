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

#include <type_traits>

// Tool to convert class enum value to underlying type for easier use
template <typename E>
constexpr typename std::underlying_type<E>::type operator+(E e)
{
    return static_cast<typename std::underlying_type<E>::type>(e);
}

namespace {
template <typename T, typename = void>
constexpr bool HasColumnCount = false;
template <typename T>
constexpr bool HasColumnCount<T, std::void_t<decltype(T::COLUMNCOUNT)>> = true;

template <typename T, typename = void>
constexpr bool HasRowCount = false;
template <typename T>
constexpr bool HasRowCount<T, std::void_t<decltype(T::ROWCOUNT)>> = true;
}

template <typename TYPE>
TYPE enumCast(int value)
{
    if constexpr (HasColumnCount<TYPE>)
        Q_ASSERT(value >= 0 && value < +TYPE::COLUMNCOUNT);
    else if constexpr (HasRowCount<TYPE>)
        Q_ASSERT(value >= 0 && value < +TYPE::ROWCOUNT);
    else
        Q_ASSERT(value >= 0 && value < +TYPE::MAXCOUNT);
    return static_cast<TYPE>(value);
}
