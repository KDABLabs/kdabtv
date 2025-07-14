/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "playlistmodel.h"

#include <QColor>

PlayListModel::PlayListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_entries << Entry({ "audio", "Enjoy The Silence", "Depeche Mode", 276 });
    m_entries << Entry({ "audio", "Farewell", "Apocalyptica", 337 });
    m_entries << Entry({ "video", "The Matrix", "The Wachowskis", 8160 });
    m_entries << Entry({ "video", "Big Buck Bunny", "Sacha Goedegebure", 600 });
}

int PlayListModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_entries.count();
}

QVariant PlayListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_entries.count())
        return QVariant();

    const Entry &entry = m_entries[index.row()];

    switch (role) {
        case Qt::DisplayRole:
            return entry.title;
        case Qt::DecorationRole:
            return QColor(entry.mediaType == "audio" ? Qt::green : Qt::blue);
        case Qt::ToolTipRole:
            return entry.producer;
        case DurationRole:
            return entry.duration;
        case MediaTypeRole:
            return entry.mediaType;
        case ProducerRole:
            return entry.producer;
        case TitleRole:
            return entry.title;
        default:
            return QVariant();
    }
}
