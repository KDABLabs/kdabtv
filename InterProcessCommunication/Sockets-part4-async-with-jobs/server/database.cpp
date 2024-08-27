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

#include "database.h"
#include <QJsonObject>
#include <algorithm>

Database::Database()
{
    m_data = {
        Person{ "David", "Faure", "Avignon", "France" },
        Person{ "René", "Faure", "Paris", "France" },
        Person{ "René", "Dupont", "Paris", "France" },
        Person{ "Mike", "Dupont", "Paris", "USA" },
        Person{ "Mike", "Smith", "New York", "USA" },
        Person{ "John", "Smith", "New York", "USA" }
    };
    m_countryFlags = { { "France", "fr.svg" },
                       { "USA", "us.svg" } };
}

std::vector<Person> Database::search(const QString &field, const QString &value) const
{
    std::vector<Person> result;
    result.reserve(m_data.size());

    auto personMatchesFiltering = [&](const Person &person) {
        const QString *variable;
        if (field == u"firstName") {
            variable = &person.firstName;
        } else if (field == u"lastName") {
            variable = &person.lastName;
        } else if (field == u"city") {
            variable = &person.city;
        } else if (field == u"country") {
            variable = &person.country;
        } else {
            return false;
        }
        return variable->contains(value, Qt::CaseInsensitive);
    };

    std::copy_if(m_data.cbegin(), m_data.cend(), std::back_inserter(result), personMatchesFiltering);

    return result;
}

QString Database::countryFlag(const QString &country) const
{
    const auto it = m_countryFlags.find(country);
    return it == m_countryFlags.end() ? QString() : it->second;
}
