/* MIT License

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#pragma once
#include <QDebug>

enum ChartPosition { Left, Right, Top, Bottom };
static QString posToString(ChartPosition pos)
{
    switch (pos) {
    case Left:
        return "Left";
    case Right:
        return "Right";
    case Top:
        return "Top";
    case Bottom:
        return "Bottom";
    }
    Q_UNREACHABLE();
}

class Diagram
{
public:
    void addNormalAxis(ChartPosition pos)
    {
        qDebug().noquote() << "Adding normal axis at" << posToString(pos);
    }
    void addCurrencyAxis(const QString &symbol, ChartPosition pos)
    {
        qDebug().noquote() << "Adding currency axis with symbol" << symbol << "at"
                           << posToString(pos);
    }
};
