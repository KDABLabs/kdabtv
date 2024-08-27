/* MIT License

Copyright (C) 2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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


#include "connection.h"
#include "personmatchjob.h"

#include <QJsonArray>

QJsonObject PersonMatchJob::query() const
{
    QJsonObject query;
    query.insert("command", "getMatches");
    query.insert("field", m_field);
    query.insert("searchValue", m_searchValue);
    return query;
}

void PersonMatchJob::setField(const QString &field)
{
    m_field = field;
}

void PersonMatchJob::setSearchValue(const QString &searchValue)
{
    m_searchValue = searchValue;
}

void PersonMatchJob::processResponse(const QJsonObject &response)
{
    const QJsonArray array = response.value("matches").toArray();
    const int numMatches = array.size();
    std::vector<Person> matches;
    matches.reserve(numMatches);
    QStringList countryNames;
    for (const QJsonValue &value : array) {
        Person person = Person::fromJsonValue(value.toObject());
        if (!countryNames.contains(person.country)) {
            countryNames.append(person.country);
        }
        matches.push_back(std::move(person));
    }
    Q_EMIT matchesFetched(matches, countryNames);
}
