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

#include "MyModel.h"

MyModel::MyModel(QObject *parent)
    : QAbstractListModel(parent)
{
    // Just some random test data
    m_data = {{Money::EUR, 100}, {Money::USD, 200}, {Money::EUR, 9.99}};
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.count();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const Money &money = m_data.at(index.row());
    if (role == Qt::DisplayRole)
        return QVariant::fromValue(money);
    // Alternatively I could have returned a string in Display Role, and the Money instance in
    // EditRole.
    return {};
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int /*role*/)
{
    // I really ought to test the parameters, just imagine a bogus proxy model in the middle...
    // That is for another episode though.
    m_data[index.row()] = value.value<Money>();
    // Let the world (other views, etc.) know that the data changed
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    // I ought to handle !index.isValid(), but again just a demo.
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}
