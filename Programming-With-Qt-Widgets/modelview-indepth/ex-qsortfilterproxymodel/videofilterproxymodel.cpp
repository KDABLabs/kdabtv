/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "videofilterproxymodel.h"

#include "playlistmodel.h"

VideoFilterProxyModel::VideoFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool VideoFilterProxyModel::videoFilterEnabled() const
{
    return m_videoFilterEnabled;
}

void VideoFilterProxyModel::setVideoFilterEnabled(bool enabled)
{
    if (m_videoFilterEnabled == enabled)
        return;

    m_videoFilterEnabled = enabled;
    emit videoFilterEnabledChanged();

    invalidateFilter();
}

bool VideoFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!m_videoFilterEnabled)
        return true;

    const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    const QString mediaType = index.data(PlayListModel::MediaTypeRole).toString();

    return (mediaType == "video");
}
