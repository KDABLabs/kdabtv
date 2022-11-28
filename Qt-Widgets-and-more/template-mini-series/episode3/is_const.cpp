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
#include <type_traits>
using namespace std;

namespace {

template <typename T>
struct isConst
{
    static constexpr bool value = false;
};

template <typename T>
struct isConst<const T>
{
    static constexpr bool value = true;
};
} // end namespace

void is_const()
{
    cout << "========== episode3 - is_const ==========\n";
    cout << std::boolalpha;
    cout << "int: " << isConst<int>::value << endl;
    cout << "const int: " << isConst<const int>::value << endl;
    cout << "int const: " << isConst<int const>::value << endl;

    int x;
    cout << "is x const? " << isConst<decltype(x)>::value
         << ", std: " << std::is_const<decltype(x)>::value << endl;

    const int y = 1;
    cout << "is y const? " << isConst<decltype(y)>::value
         << ", std: " << std::is_const<decltype(y)>::value << endl;
}
