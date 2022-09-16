/* MIT License

Copyright (C) 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "Model.h"
#include <QDebug>

int Model::rowCount(const QModelIndex & /*parent*/) const
{
    return 1;
}

int Model::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            return m_company1;
        case 1:
            return m_company2;
        case 2:
            return QVariant::fromValue(m_company3);
        }
    }
    return {};
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    qDebug() << "Setting Data" << value;
    switch (index.column()) {
    case 0:
        m_company1 = value.toString();
        break;
    case 1:
        m_company2 = value.toString();
        break;
    case 2:
        m_company3 = value.value<Company>();
    }
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return {};
    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
