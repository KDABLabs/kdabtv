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
#include <string>
using namespace std;

namespace {

template <typename T, typename S>
class Foo
{
public:
    Foo(T, S) { cout << "most generic version\n"; }
};

template <typename T>
class Foo<T, int>
{
public:
    Foo(T, int) { cout << "partial specialization on int\n"; }
};

template <typename T>
class Foo<string, T>
{
public:
    Foo(const string &, T) { cout << "partial specialization on string\n"; }
};

template <>
class Foo<int, int>
{
public:
    Foo(int, int) { cout << "full specialization on int,int\n"; }
};

} // end namespace

void multiple_arguments()
{
    cout << "========== episode2 - multipleArguments ==========\n";
    Foo<char, string> f1('a', string("def"));
    Foo<char, int> f2('a', 42);
    Foo<string, string> f3(string("abc"), string("def"));
    Foo<int, int> f4(42, 0);

    cout << "----- now with deduction of types -----\n";
    Foo f5('a', string("def"));
    Foo f6('a', 42);
    Foo f7(string("abc"), string("def"));
    Foo f8(42, 0);
}
