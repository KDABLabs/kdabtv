#include "DepecheModel.h"
#include "EnumConverters.h"
#include "Storage.h"
#include <qnamespace.h>

QVariant DepecheModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Vertical) {
        auto album = m_storage.album(section);
        return album.album;
    } else {
        switch (enum_cast<Column>(section)) {
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
        case Column::DOWNLOAD:
            return "Download";
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
        default:
            return {};
        }
    }
}

int DepecheModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_storage.albumCount();
    return 0;
}

int DepecheModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return +Column::COLUMNCOUNT;

    return 0;
}

QVariant DepecheModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto peekChartPosition = [](int position) {
        return (position == -1) ? QString() : QString::number(position);
    };

    const auto album = m_storage.album(index.row());
    switch (role) {
    case Qt::DisplayRole: {
        switch (enum_cast<Column>(index.column())) {
        case Column::Year:
            return album.year;
        case Column::RecordLabel:
            return album.recordLabel;
        case Column::UK:
            return peekChartPosition(album.UK);
        case Column::AUS:
            return peekChartPosition(album.AUS);
        case Column::AUT:
            return peekChartPosition(album.AUT);
        case Column::FRA:
            return peekChartPosition(album.FRA);
        case Column::GER:
            return peekChartPosition(album.GER);
        case Column::ITA:
            return peekChartPosition(album.ITA);
        case Column::NLD:
            return peekChartPosition(album.NLD);
        case Column::SWE:
            return peekChartPosition(album.SWE);
        case Column::SWI:
            return peekChartPosition(album.SWI);
        case Column::US:
            return peekChartPosition(album.US);
        case Column::COLUMNCOUNT:
            Q_UNREACHABLE();
        default:
            return {};
        }
    case Qt::CheckStateRole: {
        switch (enum_cast<Column>(index.column())) {
        case Column::CD:
            return (album.mediums & Medium::CD) ? Qt::Checked : Qt::Unchecked;
        case Column::CS:
            return (album.mediums & Medium::CS) ? Qt::Checked : Qt::Unchecked;
        case Column::LP:
            return (album.mediums & Medium::LP) ? Qt::Checked : Qt::Unchecked;
        case Column::DCC:
            return (album.mediums & Medium::DCC) ? Qt::Checked : Qt::Unchecked;
        case Column::MD:
            return (album.mediums & Medium::MD) ? Qt::Checked : Qt::Unchecked;
        case Column::DOWNLOAD:
            return (album.mediums & Medium::DOWNLOAD) ? Qt::Checked : Qt::Unchecked;
        default:
            return {};
        }
        return {};
    }
    case Qt::TextAlignmentRole:
        if (index.column() == +Column::RecordLabel)
            return (int)(Qt::AlignLeft | Qt::AlignVCenter);
        else
            return Qt::AlignCenter;
    }
    }
    return {};
}
