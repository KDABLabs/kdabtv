/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>

class PlayListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles
    {
        MediaTypeRole = Qt::UserRole,
        TitleRole,
        ProducerRole,
        DurationRole
    };

    explicit PlayListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    struct Entry
    {
        QString mediaType; // 'audio' or 'video'
        QString title;
        QString producer;
        int duration; // in seconds
    };

    QVector<Entry> m_entries;
};

#endif // PLAYLISTMODEL_H
