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
#include "EnumHelper.h"
#include <QDebug>

class Example : public QObject
{
    Q_OBJECT
public:
    enum class ExampleEnum { Foo, Bar, Baz };
    Q_ENUM(ExampleEnum);
};

// I'm just making this inline to avoid putting it in a .cpp file of its own
// In production I would of course not do that.
inline void newWay()
{
    qDebug().noquote() << "----- New way -------";

    qDebug() << EnumHelper::toString(Example::ExampleEnum::Bar);
    auto myEnum = EnumHelper::fromString<Example::ExampleEnum>("Foo");
    qDebug() << EnumHelper::toString(myEnum);

    auto invalidEnum = EnumHelper::fromString<Example::ExampleEnum>("Badam");
    qDebug() << EnumHelper::toString(invalidEnum);
}
