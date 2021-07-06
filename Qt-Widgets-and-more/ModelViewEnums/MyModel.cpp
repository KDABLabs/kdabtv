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
#include "MyModel.h"
#include "EnumConverters.h"

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_data = {{"Alan Wilder", QDate(1959, 6, 1)},
              {"Andrew Fletcher", QDate(1961, 7, 8)},
              {"David Gahan", QDate(1962, 5, 9)},
              {"Martin Lee Gore", QDate(1961, 7, 23)},
              {"Vince Clarke", QDate(1960, 7, 3)}};
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (enumCast<Column>(section)) {
    case Column::Name:
        return "Name";
    case Column::Age:
        return "Age";
    case Column::COLUMNCOUNT:
        Q_UNREACHABLE();
    }
    Q_UNREACHABLE();
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.count();
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return +Column::COLUMNCOUNT;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const DummyData &row = m_data.at(index.row());
    switch (role) {
    case +Role::Name:
        return row.name;

    case +Role::Birthday:
        return row.birthday;

    case Qt::DisplayRole: {
        switch (enumCast<Column>(index.column())) {
        case Column::Name:
            return row.name;
        case Column::Age: {
            const QDate birthday = row.birthday;
            const QDate today = QDate::currentDate();
            if (QDate(today.year(), birthday.month(), birthday.day()) < birthday)
                return today.year() - birthday.year() - 1;
            else
                return today.year() - birthday.year();
        }

        case Column::COLUMNCOUNT:
            Q_UNREACHABLE();
        }
        Q_UNREACHABLE();
    }
    }
    return {};
}
