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
#include <vector>

namespace {

template <typename Container, typename Variable>
void sort_by_member_variable(Container &container, Variable variable)
{
    std::sort(container.begin(), container.end(),
              [variable](const auto &x, const auto &y) { return x.*variable < y.*variable; });
}

template <typename Container, typename Function>
void sort_by_member_function(Container &container, Function function)
{
    std::sort(container.begin(), container.end(), [function](const auto &x, const auto &y) {
        return (x.*function)() < (y.*function)();
    });
}

} // end namespace

void part2()
{
    std::cout << "\n========== invoke - part2 ==========\n";

    std::vector<Foo> v{{12, 100}, {20, 3}, {30, 30}};

    sort_by_member_variable(v, &Foo::second);
    print("Sort bny member variable", v);

    sort_by_member_function(v, &Foo::fraction);
    print("Sort by member function", v);
}
