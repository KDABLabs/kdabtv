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

void qt_map_in_loops()
{
    qDebug() << "========== ranges - qt_map_in_loops ==========";
    QMap<int, QString> map{{4, "four"}, {5, "five"}, {6, "six"}};
    for (const auto &value : map) {
        qDebug() << value;
    }

    qDebug() << "--------- Take 2 ---------";
    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        qDebug() << *it << it.key() << it.value();
    }

    qDebug() << "--------- Take 3 ---------";
    for (auto it = map.constKeyValueBegin(); it != map.constKeyValueEnd(); ++it) {
        qDebug() << it->first << it->second;
    }
}
