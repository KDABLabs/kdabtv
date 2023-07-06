/* MIT License

Copyright (C) 2023 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "Foo.h"
#include <functional>
#include <iostream>

namespace {

} // end namespace

void part4()
{
    std::cout << "\n========== invoke - part4 ==========\n";

    Foo f{42, 2};

    int Foo::*variable = &Foo::first;
    int (Foo::*function)() const = &Foo::go;

    std::cout << f.first << "," << f.go() << std::endl;
    std::cout << f.*variable << "," << (f.*function)() << std::endl;

    Foo *g = &f;
    std::cout << g->*variable << "," << (g->*function)() << std::endl;

    std::cout << std::invoke(variable, f) << "," << std::invoke(function, f) << std::endl
              << std::invoke(variable, g) << "," << std::invoke(function, g) << std::endl;
}
