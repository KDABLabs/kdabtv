/* MIT License

Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "MoneyEditor.h"
#include "Money.h"
#include <QHBoxLayout>
#include <QTimer>

MoneyEditor::MoneyEditor(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    m_currency = new QComboBox;
    m_currency->addItems({"€", "$"});
    layout->addWidget(m_currency);

    m_amount = new QDoubleSpinBox;
    m_amount->setMaximum(INT_MAX);
    layout->addWidget(m_amount, 1);

    layout->setContentsMargins(0, 0, 0, 0);
    setAutoFillBackground(true);
}

void MoneyEditor::setValue(const Money &money)
{
    // This is indeed very brittle, but after all it is just an example.
    m_currency->setCurrentIndex(money.currency());
    m_amount->setValue(money.amount());
}

Money MoneyEditor::value() const
{
    return Money((Money::Currency)m_currency->currentIndex(), m_amount->value());
}
