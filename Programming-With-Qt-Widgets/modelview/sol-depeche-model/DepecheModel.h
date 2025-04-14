#pragma once

#include "Storage.h"
#include <QAbstractTableModel>

class DepecheModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    using QAbstractTableModel::QAbstractTableModel;
    enum class Column {
        Year,
        RecordLabel,
        CD,
        CS,
        LP,
        DCC,
        MD,
        DOWNLOAD,
        UK,
        AUS,
        AUT,
        FRA,
        GER,
        ITA,
        NLD,
        SWE,
        SWI,
        US,
        COLUMNCOUNT
    };

    // QAbstractItemModel interface
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    Storage m_storage;
};
