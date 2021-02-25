/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "playlistmodel.h"

PlayListModel::PlayListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_entries = {
       Entry { "audio", "Enjoy The Silence", "Depeche Mode", 276 },
       Entry { "audio", "Farewell", "Apocalyptica", 337 },
       Entry { "video", "The Matrix", "The Wachowskis", 8160 },
       Entry { "video", "Big Buck Bunny", "Sacha Goedegebure", 600 }
    };
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
        case TitleRole:
            return entry.title;
        case ProducerRole:
            return entry.producer;
        case MediaTypeRole:
            return entry.mediaType;
        case DurationRole:
            return entry.duration;
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> PlayListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names.insert(MediaTypeRole, "mediaType");
    names.insert(TitleRole, "title");
    names.insert(ProducerRole, "producer");
    names.insert(DurationRole, "duration");
    return names;
}

