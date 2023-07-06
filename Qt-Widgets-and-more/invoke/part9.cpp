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
#include <algorithm>
#include <iostream>
#include <vector>

namespace {
template <typename Function, typename Object, typename... Args>
auto invoke(Function f, const Object &o, Args... args)
{
    if constexpr (!std::is_member_pointer_v<Function>) {
        return f(o, args...);
    } else {
        if constexpr (std::is_member_function_pointer_v<Function>) {
            if constexpr (std::is_pointer_v<Object>)
                return (o->*f)(args...);
            else
                return (o.*f)(args...);
        } else {
            static_assert(sizeof...(args) == 0, "invoke: no args allowed for data member");
            if constexpr (std::is_pointer_v<Object>)
                return o->*f;
            else
                return o.*f;
        }
    }
}
} // end namespace

void part9()
{
    std::cout << "========== invoke - part9 ==========\n";
    Foo foo{1, 2};
    //    ::invoke(&Foo::first, Foo{1, 2}, 3);
    //    ::invoke(&Foo::go, foo, 3);
    std::cout << "Variable arguments invoke: " << ::invoke(&Foo::go2, foo, 3) << std::endl;
}
