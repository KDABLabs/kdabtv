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

#include "strong_typedef.hpp"
#include <QDebug>
#include <QHash>
#include <QString>

namespace {
using City = jss::strong_typedef<struct CityTag, QString>;
using Country = jss::strong_typedef<struct CountryTag, QString,
                                    jss::strong_typedef_properties::equality_comparable>;

void printCity(const Country &country, const City &city)
{
    qDebug() << "Step 3, Country =" << country.underlying_value()
             << ",City =" << city.underlying_value();
}

}

namespace jss {
size_t qHash(const Country &country, uint seed = 0)
{
    return qHash(country.underlying_value(), seed);
}
}

void go3()
{
    Country country{"Brazil"};
    City city{"Brasília"};

    QHash<Country, City> capitals;
    capitals[country] = city;
    printCity(country, capitals.value(country));
}
