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

// clang-format off
namespace {
template <typename Function, typename Object>
auto invoke_helper(Function f, const Object &o,
                   std::true_type /* is_member_function_pointer<Function> */,
                   std::false_type /* is_pointer<Object> */,
                   std::true_type /* is_member_pointer<Function> */)
{
    return (o.*f)();
}

template <typename Function, typename Object>
auto invoke_helper(Function f, const Object &o,
                   std::false_type /* is_member_function_pointer<Function> */,
                   std::false_type /* is_pointer<Object> */,
                   std::true_type /* is_member_pointer<Function> */)
{
    return o.*f;
}

template <typename Function, typename Object>
auto invoke_helper(Function f, const Object &o,
                   std::true_type /* is_member_function_pointer<Function> */,
                   std::true_type /* is_pointer<Object> */,
                   std::true_type /* is_member_pointer<Function> */)
{
    return (o->*f)();
}

template <typename Function, typename Object>
auto invoke_helper(Function f, const Object &o,
                   std::false_type /* is_member_function_pointer<Function> */,
                   std::true_type /* is_pointer<Object> */,
                   std::true_type /* is_member_pointer<Function> */)
{
    return o->*f;
}

template <typename Function, typename Object, typename DontCare1, typename DontCare2>
auto invoke_helper(Function f, const Object &o,
                   DontCare1 /* is_member_function_pointer<Function> */,
                   DontCare2 /* is_pointer<Object> */,
                   std::false_type /* is_member_pointer<Function> */)
{
    return f(o);
}

template <typename Function, typename Object>
auto invoke(Function f, const Object &o)
{
    return invoke_helper(f, o,
                         std::is_member_function_pointer<Function>{},
                         std::is_pointer<Object>{},
                         std::is_member_pointer<Function>{});
}

template <typename Container, typename Member>
void sort_by(Container &container, Member member)
{
    std::sort(container.begin(), container.end(), [member](const auto &x, const auto &y) {
        return ::invoke(member, x) < ::invoke(member, y);
    });
}
int standalone(const Foo &foo) {
    return foo.first * foo.second;
}

} // end namespace
// clang-format on

void part7()
{
    std::cout << "\n========== invoke - part7 ==========\n";
    std::vector<Foo> v{{12, 100}, {20, 3}, {30, 30}};
    std::vector<Foo *> ptrList{new Foo{12, 100}, new Foo{20, 3}, new Foo{30, 30}};

    sort_by(v, &Foo::second);
    print("sort by member variable (instance)", v);

    sort_by(v, &Foo::fraction);
    print("sort by member function (instance)", v);

    sort_by(ptrList, &Foo::second);
    print("sort by member variable (pointer)", ptrList);

    sort_by(ptrList, &Foo::fraction);
    print("sort by member function (pointer)", ptrList);

    auto myLambda = [](const auto &item) { return item.first * item.second; };
    sort_by(v, myLambda);
    print("sort by lambda (instance)", v);

    auto myLambdaPtr = [](const auto *item) { return item->first * item->second; };
    sort_by(ptrList, myLambdaPtr);
    print("sort by lambda (pointer)", ptrList);

    sort_by(v, standalone);
    print("sort by a standalone function", v);
}
