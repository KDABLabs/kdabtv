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
QPair<QString, QString> splitPath(const QString &path)
{
    int index1 = path.lastIndexOf(".");
    QString ext = path.mid(index1 + 1);
    int index2 = path.lastIndexOf("/", index1);
    QString base = path.mid(index2 + 1, index1 - index2 - 1);

    return qMakePair(base, ext);
}
} // end namespace

void structured_bindings_qt()
{
    qDebug() << "========== ranges - structured_bindings_qt ==========";
    const auto &[base, ext] = splitPath("/home/me/myfile.mp5");
    qDebug() << base << ext;
}
