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

#include "strongTypedefSupport.h"
#include <QBuffer>
#include <QDataStream>
#include <QDebug>

namespace qt_strong_typedef_properties {
struct streamable
{
    template <typename Derived, typename ValueType>
    struct mixin
    {
        friend QDataStream &operator<<(QDataStream &stream, const Derived &self)
        {
            stream << self.underlying_value();
            return stream;
        }

        friend QDataStream &operator>>(QDataStream &stream, Derived &self)
        {
            stream >> self.underlying_value();
            return stream;
        }
    };
};
}

namespace {
using Country =
    jss::strong_typedef<struct CountryTag, QString, jss::strong_typedef_properties::comparable,
                        qt_strong_typedef_properties::streamable>;
}

void go5()
{
    Country country{"Republic of Yara"};
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out << country;

    QDataStream in(buffer.buffer());
    in >> country;

    qDebug() << "Step 5: " << country;
}
