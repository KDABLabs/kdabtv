/* MIT License

Copyright (C) 2025 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include <QRangeModel>
#include <QTableView>

struct Person
{
    QString name;
    int age;
};

template <size_t I, typename T>
    requires((I <= 1) && std::is_same_v<std::remove_cvref_t<T>, Person>)
auto &&get(T &&person)
{
    if constexpr (I == 0)
        return q23::forward_like<T>(person.name);
    else
        return q23::forward_like<T>(person.age);
}

template <>
struct std::tuple_size<Person> : std::integral_constant<size_t, 2>
{
};

template <size_t I>
struct std::tuple_element<I, Person>
{
    using type = q20::remove_cvref_t<decltype(get<I>(std::declval<Person>()))>;
};

void Struct()
{
    QList<Person> people{{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};
    auto model = new QRangeModel(people);
    auto view = new QTableView;
    view->setModel(model);
    view->show();

    Person p1 = {"Diana", 28};
    const Person p2 = {"Diana", 28};
    static_assert(std::is_same<decltype(get<0>(p1)), QString &>());
    static_assert(std::is_same<decltype(get<0>(p2)), const QString &>());
    static_assert(std::is_same<decltype(get<0>(std::move(p1))), QString &&>());
    static_assert(std::is_same<decltype(get<0>(std::move(p2))), const QString &&>());
}
