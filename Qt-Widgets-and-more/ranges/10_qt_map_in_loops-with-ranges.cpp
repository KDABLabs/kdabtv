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

namespace {
template <typename Container>
class asRange
{
public:
    explicit asRange(Container &container)
        : m_container(container)
    {
    }

    auto begin() const { return m_container.constKeyValueBegin(); }
    auto end() const { return m_container.constKeyValueEnd(); }

private:
    Container &m_container;
};

template <typename Container>
class asMutableRange
{
public:
    explicit asMutableRange(Container &container)
        : m_container(container)
    {
    }

    auto begin() { return m_container.keyValueBegin(); }
    auto end() { return m_container.keyValueEnd(); }

private:
    Container &m_container;
};

} // end namespace

void qt_map_in_loops_with_ranges()
{
    qDebug() << "========== ranges - qt_map_in_loops-with-ranges ==========";
    QMap<int, QString> map{{4, "four"}, {5, "five"}, {6, "six"}};

    for (const auto &[key, value] : asRange(map)) {
        qDebug() << key << value;
    }

    qDebug() << "--------- Lets modify the values ---------";
    for (auto &&[key, value] : asMutableRange(map)) {
        value = "-->" + value + "<--";
    }

    for (const auto &[key, value] : asRange(map)) {
        qDebug() << key << value;
    }

    qDebug() << "--------- Works with hashes too ---------";
    QHash<int, QString> hash{{7, "seven"}, {8, "eight"}, {9, "nine"}};

    for (const auto &[key, value] : asRange(hash)) {
        qDebug() << key << value;
    }
}
