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
#pragma once

#include <QComboBox>
#include <QObject>
#include <functional>

namespace ComboBoxHelper {

template <typename ValueType>
struct Item
{
    Item(const QString &text, const ValueType &value)
        : text(text)
        , value(value)
    {
    }
    const QString text;
    const ValueType value;
};

template <typename ValueType>
void setup(QComboBox *cb, ValueType defaultValue, const QVector<Item<ValueType>> &list,
           const std::function<void(ValueType)> &function = {})
{
    for (const Item<ValueType> &item : list) {
        cb->addItem(item.text, QVariant::fromValue(item.value));
        if (item.value == defaultValue) {
            cb->setCurrentIndex(cb->count() - 1);
        }
    }
    if (function) {
        QObject::connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged), [function, cb] {
            const ValueType value = cb->currentData().value<ValueType>();
            function(value);
        });
        function(defaultValue);
    }
}

template <typename ValueType, typename Target, typename Function>
void setup(QComboBox *cb, ValueType defaultValue, const QVector<Item<ValueType>> &list,
           Target *target, Function function)
{
    setup(cb, defaultValue, list);
    QObject::connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [function, cb, target] {
                         const ValueType value = cb->currentData().value<ValueType>();
                         std::invoke(function, target, value);
                     });
    std::invoke(function, target, defaultValue);
}

template <typename T>
void setCurrentValue(QComboBox *combo, T value)
{
    int index = combo->findData(QVariant::fromValue(value));
    Q_ASSERT(index != -1);
    combo->setCurrentIndex(index);
}

} // End Namespace
