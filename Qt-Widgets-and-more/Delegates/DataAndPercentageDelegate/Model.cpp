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
#include "../Money.h"
#include "EnumConverters.h"
#include "PercentageValue.h"
#include <QDebug>
#include <QPixmap>

int Model::rowCount(const QModelIndex & /*parent*/) const
{
    return 3;
}
int Model::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

namespace {
// THIS IS JUST STUB DATA
struct Data
{
    Money amount;
    bool direction;
    PercentageValue delta;
};

namespace {
    enum direction { up, down };
}

static Data s_data[6]{
    {100'000_EUR, down, PercentageValue(0.17)}, {120'000_EUR, up, PercentageValue(0.10)},
    {60'000_EUR, up, PercentageValue(0.20)},    {50'000_EUR, up, PercentageValue(2.00)},
    {40'000_EUR, down, PercentageValue(0.42)},  {70'000_EUR, up, PercentageValue(0.10)},
};
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    static const QPixmap upImage("://green_arrow_up.png");
    static const QPixmap downImage("://red_arrow_down.png");
    Data &data = s_data[index.row() * 2 + index.column()];
    switch (role) {
    case +Role::Value:
        return QVariant::fromValue(data.amount);
    case +Role::Arrow:
        return data.direction == up ? upImage : downImage;

    case +Role::Delta:
        return QVariant::fromValue(data.delta);
    }
    return {};
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Vertical)
        return QStringList{"Income", "Cost", "Total"}.at(section);

    else
        return QStringList{"Forecast", "2021"}.at(section);
}
