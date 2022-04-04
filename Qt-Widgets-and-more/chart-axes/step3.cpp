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

#include "shared.h"
#include <memory>

namespace {
class Axis
{
public:
    virtual ~Axis() = default;
    virtual void setup(Diagram *diagram) = 0;
    ChartPosition pos;

protected:
    Axis() = delete;
    Axis(const Axis &) = delete;
    explicit Axis(ChartPosition pos)
        : pos(pos)
    {
    }
};

class NormalAxis : public Axis
{
public:
    explicit NormalAxis(ChartPosition pos)
        : Axis(pos)
    {
    }

    void setup(Diagram *diagram) override { diagram->addNormalAxis(pos); }
};

class CurrencyAxis : public Axis
{
public:
    explicit CurrencyAxis(const QString &symbol, ChartPosition pos)
        : Axis(pos)
        , symbol(symbol)
    {
    }
    void setup(Diagram *diagram) override { diagram->addCurrencyAxis(symbol, pos); }

private:
    QString symbol;
};

void createChart(Diagram *diagram, const std::initializer_list<std::unique_ptr<Axis>> &axes)
{
    for (auto &axis : axes) {
        axis->setup(diagram);
    }
}

}

void go3()
{
    qDebug() << "=========== Step 3 =============";
    Diagram diagram;
    createChart(&diagram,
                {std::make_unique<NormalAxis>(Bottom), std::make_unique<CurrencyAxis>("€", Right),
                 std::make_unique<NormalAxis>(Top)});
}
