/* MIT License

Copyright (C) 2025 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include <QAbstractTableModel>
#include <QHeaderView>
#include <QTableView>

namespace {
struct Person
{
    QString name;
    int age;
};
using People = QList<Person>;

class TableModel : public QAbstractTableModel
{
public:
    TableModel(const People &people, QObject *parent = nullptr);
    enum class Column { Name, Age, COLOUMNCOUNT };

    int columnCount(const QModelIndex &parent = {}) const override;
    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

private:
    People m_people;
};

TableModel::TableModel(const People &people, QObject *parent)
    : QAbstractTableModel(parent)
    , m_people(people)
{
}

int TableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return static_cast<int>(Column::COLOUMNCOUNT);
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_people.count();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical || role != Qt::DisplayRole || section < 0
        || section >= columnCount())
        return {};
    switch (static_cast<Column>(section)) {
    case Column::Name:
        return "Name";
    case Column::Age:
        return "Age";
    default:
        Q_UNREACHABLE();
    }
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_people.count())
        return {};

    switch (role) {
    case Qt::DisplayRole: {
        const Person &person = m_people.at(index.row());
        switch (static_cast<Column>(index.column())) {
        case Column::Name:
            return person.name;
        case Column::Age:
            return person.age;
        default:
            return QVariant{};
        }
    }
    }
    return {};
}

} // namespace

void normalTableModel()
{
    People people{{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};
    auto model = new TableModel(people);
    auto view = new QTableView;
    view->setModel(model);
    view->verticalHeader()->hide();
    view->show();
}
