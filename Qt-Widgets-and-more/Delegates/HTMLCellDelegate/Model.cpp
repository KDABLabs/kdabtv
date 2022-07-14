/* MIT License

Copyright (C) 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "Model.h"
#include <QFont>

int Model::rowCount(const QModelIndex & /*parent*/) const
{
    return 4;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        switch (index.row()) {
        case 0:
            return "<html><body><b>Hello</b> <i>world</i></body></html>";
        case 1:
            return "<font color=\"red\">RED and <b>BOLD</b></font>";
        case 2:
            return "<p>Paragraph 1</p><p>Paragraph 2</p>";
        case 3:
            return "<style>"
                   "  th, td { padding: 10px; }"
                   "</style>"
                   "<table border=1>"
                   "<tr><th>Country</th><th>Population</th></tr>"
                   "<tr><td>The world</td><td>7,942 Millions</td></tr>"
                   "<tr><td>Denmark</td><td>6 Millions</td></tr></table>";
        }
        break;
    case Qt::FontRole: {
        QFont font;
        font.setPointSize(font.pointSize() * (1 + index.row() / 2.0));
        return font;
    } break;
    }
    return {};
}
