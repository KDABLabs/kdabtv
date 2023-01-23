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

#include <QDebug>

class MyStruct
{
public:
    MyStruct(QString base, QString ext)
        : m_base(std::move(base))
        , m_ext(std::move(ext))
    {
    }
    QString base() const { return m_base; }
    QString ext() const { return m_base; }
    int length() const { return m_base.length() + m_ext.length() + 1; }

private:
    QString m_base;
    QString m_ext;
};

namespace {
MyStruct splitPath(const QString &path)
{
    int index1 = path.lastIndexOf(".");
    const QString ext = path.mid(index1 + 1);
    int index2 = path.lastIndexOf("/", index1);
    const QString base = path.mid(index2 + 1, index1 - index2 - 1);

    return {base, ext};
}

} // end namespace

template <>
struct std::tuple_size<MyStruct>
{
    static constexpr int value = 3;
};

template <>
struct std::tuple_element<2, MyStruct>
{
    using type = int;
};

template <std::size_t index>
struct std::tuple_element<index, MyStruct>
{
    using type = QString;
};

template <std::size_t>
auto get(const MyStruct &);

template <std::size_t index>
auto get(const MyStruct &s)
{
    if constexpr (index == 0)
        return s.base();
    else if constexpr (index == 1)
        return s.ext();
    else
        return s.length();
}

void structured_bindings_my_class()
{
    qDebug() << "========== ranges - structured_bindings_my_class ==========";
    const auto &[base, ext, length] = splitPath("/home/me/myfile.mp5");
    qDebug() << base << ext << length;
}
