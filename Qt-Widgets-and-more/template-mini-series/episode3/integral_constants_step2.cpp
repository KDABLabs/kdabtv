/* MIT License

Copyright (C) 2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include <iostream>
using namespace std;

namespace {
template <typename T, T v>
struct integralConstant
{
    static constexpr T value = v;
};

// std::bool_constant was introduced in C++17
template <bool v>
using boolConstant = integralConstant<bool, v>;

using falseType = boolConstant<false>;
using trueType = boolConstant<true>;

template <typename T>
struct isConst : falseType
{
};

template <typename T>
struct isConst<const T> : trueType
{
};

// Requires C++17
template <typename T>
inline constexpr bool isConst_v = isConst<T>::value;

} // end namespace

void integral_constants_step2()
{
    cout << "========== episode3 - integral_constants - step 2 ==========\n";
    cout << std::boolalpha;
    cout << "int: " << isConst_v<int> << ", std: " << std::is_const_v<int> << endl;
    cout << "const int: " << isConst_v<const int> << ", std: "
         << std::is_const_v<const int> << endl;
}
