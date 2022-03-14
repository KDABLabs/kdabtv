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

#include "DepecheModel.h"
#include "EnumConverters.h"
#include <QColor>

static Qt::CheckState boolToState(bool b)
{
    return b ? Qt::Checked : Qt::Unchecked;
};

DepecheModel::DepecheModel(QObject *parent)
    : QAbstractListModel(parent)
{
    using namespace Medium;
    // source: https://en.wikipedia.org/wiki/Depeche_Mode_discography
    m_data = {
        // clang-format off
        {"Speak & Spell",            1981, "Mute",           CD | CS | LP,            10, 28, -1,  -1, 49, 99, -1, 21, -1, 192},
        {"A Broken Frame",           1982, "Mute",           CD | CS | LP,            8,  -1, -1, 194, 56, 88, -1, 22, -1, 177},
        {"Construction Time Again ", 1983, "Mute",           CD | CS | LP,            6,  -1, -1,  -1,  7, -1, 32, 12, 21,  -1},
        {"Some Great Reward",        1984, "Mute",           CD | CS | LP,            5,  -1, 19,  -1,  3, 32, 34,  7,  5,  51},
        {"Black Celebration",        1986, "Mute",           CD | CS | LP,            4,  69, 26,  19,  2, 17, 35,  5,  1,  90},
        {"Music for the Masses",     1987, "Mute",           CD | CS | LP,            10, 60, 16,   7,  2,  7, 52,  4,  4,  35},
        {"Violator",                 1990, "Mute",           CD | CS | LP | DCC | MD, 2,  42,  4,   1,  2,  5, 17,  6,  2,   7},
        {"Songs of Faith and Devotion", 1993, "Mute",        CD | CS | LP | DCC | MD, 1,  14,  1,   1,  1,  1, 18,  2,  1,   1},
        {"Ultra",                    1997, "Mute",           CD | CS | LP | DCC,      1,   7,  5,   2,  1,  2, 17,  1,  4,   5},
        {"Exciter",                  2001, "Mute",           CD | CS | LP,            9,  20,  2,   1,  1,  2, 15,  1,  2,   8},
        {"Playing the Angel",        2005, "Mute,Reprise",   CD | LP | DOWNLOAD,      6,  45,  1,   1,  1,  1, 11,  1,  1,   7},
        {"Sounds of the Universe",   2009, "Mute",           CD | LP | DOWNLOAD,      2,  32,  1,   2,  1,  1,  7,  1,  1,   3},
        {"Delta Machine",            2013, "Mute, Columbia", CD | LP | DOWNLOAD,      2,  16,  1,   2,  1,  1,  3,  1,  1,   6},
        {"Spirit",                   2017, "Mute, Columbia", CD | LP | DOWNLOAD,      5,  14,  1,   1,  1,  1,  4,  3,  1,   5},
        // clang-format on
    };

    m_selected.resize(m_data.count());
}

int DepecheModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.count();
}

QVariant DepecheModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto peekChartPosition = [](int position) {
        return (position == -1) ? QString() : QString::number(position);
    };

    switch (role) {
    case Qt::DisplayRole: {
        const Data &data = m_data.at(index.row());
        switch (enumCast<Column>(index.column())) {
        case Column::Year:
            return data.year;
        case Column::RecordLabel:
            return data.recordLabel;
        case Column::UK:
            return peekChartPosition(data.UK);
        case Column::AUS:
            return peekChartPosition(data.AUS);
        case Column::AUT:
            return peekChartPosition(data.AUT);
        case Column::FRA:
            return peekChartPosition(data.FRA);
        case Column::GER:
            return peekChartPosition(data.GER);
        case Column::ITA:
            return peekChartPosition(data.ITA);
        case Column::NLD:
            return peekChartPosition(data.NLD);
        case Column::SWE:
            return peekChartPosition(data.SWE);
        case Column::SWI:
            return peekChartPosition(data.SWI);
        case Column::US:
            return peekChartPosition(data.US);
        case Column::COLUMNCOUNT:
            Q_UNREACHABLE();
        default:
            return {};
        }
    }
    case Qt::CheckStateRole: {
        const Data &data = m_data.at(index.row());

        switch (enumCast<Column>(index.column())) {
        case Column::CD:
            return boolToState(data.mediums & Medium::CD);
        case Column::CS:
            return boolToState(data.mediums & Medium::CS);
        case Column::LP:
            return boolToState(data.mediums & Medium::LP);
        case Column::DCC:
            return boolToState(data.mediums & Medium::DCC);
        case Column::MD:
            return boolToState(data.mediums & Medium::MD);
        case Column::download:
            return boolToState(data.mediums & Medium::DOWNLOAD);
        default:
            return {};
        }
    }
    case Qt::TextAlignmentRole:
        return (index.column() == +Column::RecordLabel) ? int(Qt::AlignLeft | Qt::AlignVCenter)
                                                        : int(Qt::AlignCenter);
    }

    return {};
}

int DepecheModel::columnCount(const QModelIndex &) const
{
    return +Column::COLUMNCOUNT;
}

QVariant DepecheModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role) {
    case Qt::DisplayRole: {
        if (orientation == Qt::Horizontal) {
            switch (enumCast<Column>(section)) {
            case Column::Year:
                return "Year";
            case Column::RecordLabel:
                return "Record Label";
            case Column::CD:
                return "CD";
            case Column::CS:
                return "CS";
            case Column::LP:
                return "LP";
            case Column::DCC:
                return "DCC";
            case Column::MD:
                return "MD";
            case Column::download:
                return "download";
            case Column::UK:
                return "UK";
            case Column::AUS:
                return "AUS";
            case Column::AUT:
                return "AUT";
            case Column::FRA:
                return "FRA";
            case Column::GER:
                return "GER";
            case Column::ITA:
                return "ITA";
            case Column::NLD:
                return "NLD";
            case Column::SWE:
                return "SWE";
            case Column::SWI:
                return "SWI";
            case Column::US:
                return "US";
            case Column::COLUMNCOUNT:
                Q_UNREACHABLE();
            }
            return {};
        } else {
            return m_data.at(section).album;
        }
    }

    case Qt::CheckStateRole:
        if (orientation == Qt::Horizontal)
            return {};
        return boolToState(m_selected.at(section));

    case Qt::BackgroundRole:
        if (orientation == Qt::Vertical && section >= 5 && section <= 6)
            return QColor(Qt::green);
        return {};
    }

    return {};
}

bool DepecheModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
                                 int role)
{
    if (role != Qt::CheckStateRole || orientation != Qt::Vertical)
        return false;

    m_selected[section] = value.value<Qt::CheckState>() == Qt::Checked;
    emit headerDataChanged(orientation, section, section);
    return true;
}

QStringList DepecheModel::selectedAlbums() const
{
    QStringList result;
    for (int row = 0; row < rowCount(); ++row) {
        if (m_selected.at(row))
            result.append(m_data.at(row).album);
    }
    return result;
}
