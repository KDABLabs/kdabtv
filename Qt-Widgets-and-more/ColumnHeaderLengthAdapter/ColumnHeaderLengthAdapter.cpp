/* MIT License

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "ColumnHeaderLengthAdapter.h"
#include <QHeaderView>
#include <QTableView>
#include <QTreeView>

ColumnHeaderLengthAdapter::ColumnHeaderLengthAdapter(QTableView *view)
    : QAbstractTableModel(view)
{
    m_headerView = view->horizontalHeader();
    QMetaObject::invokeMethod(this, &ColumnHeaderLengthAdapter::initialize, Qt::QueuedConnection);
}

ColumnHeaderLengthAdapter::ColumnHeaderLengthAdapter(QTreeView *view)
    : QAbstractTableModel(view)
{
    m_headerView = view->header();
    QMetaObject::invokeMethod(this, &ColumnHeaderLengthAdapter::initialize, Qt::QueuedConnection);
}

int ColumnHeaderLengthAdapter::rowCount(const QModelIndex & /*parent*/) const
{
    return 0;
}

int ColumnHeaderLengthAdapter::columnCount(const QModelIndex &parent) const
{
    Q_ASSERT(!parent.isValid());
    Q_UNUSED(parent);
    if (!m_sourceModel)
        return 0;
    else
        return m_sourceModel->columnCount();
}

QVariant ColumnHeaderLengthAdapter::data(const QModelIndex & /*index*/, int /*role*/) const
{
    return {};
}

QVariant ColumnHeaderLengthAdapter::headerData(int section, Qt::Orientation orientation,
                                               int role) const
{
    if (!m_sourceModel)
        return {};

    const QStringList list =
        m_sourceModel->headerData(section, orientation, Qt::DisplayRole).toStringList();

    if (role == Qt::DisplayRole) {
        const auto font =
            m_sourceModel->headerData(section, orientation, Qt::FontRole).value<QFont>();
        for (const auto &headerText : list) {
            const int width = QFontMetrics(font).boundingRect(headerText).width();
            if (width < m_headerView->sectionSize(section) - 10)
                return headerText;
        }

        if (!list.empty())
            return list.last();

    } else if (role == Qt::ToolTipRole) {
        QString fullText;
        if (!list.isEmpty())
            fullText = list.first();

        const QString modelToolTip =
            m_sourceModel->headerData(section, orientation, Qt::ToolTipRole).toString();
        if (headerData(section, orientation, Qt::DisplayRole).toString() != fullText
            || !modelToolTip.isEmpty()) {
            QString toolTip;
            if (!fullText.isEmpty())
                toolTip = QString("<b>%1</b>").arg(fullText);
            if (!modelToolTip.isEmpty())
                toolTip += QString("<br/>%1").arg(modelToolTip);
            return toolTip;
        }
    }

    return m_sourceModel->headerData(section, orientation, role);
}

QString ColumnHeaderLengthAdapter::headerDataToString(const QVariant &variant)
{
    if (!variant.isValid())
        return {};

    if (variant.canConvert<QString>())
        return variant.toString();
    else if (variant.canConvert<QStringList>()) {
        const QStringList list = variant.toStringList();
        if (!list.isEmpty())
            return list.first();
    }
    return {};
}

// This method needs to be invoked asynchronously as the model might not be set at the time the
// constructor is called.
void ColumnHeaderLengthAdapter::initialize()
{
    m_sourceModel = m_headerView->model();
    if (!m_sourceModel) {
        auto view = qobject_cast<QAbstractItemView *>(m_headerView->parentWidget());
        if (view) {
            m_sourceModel = view->model();
        }
    }

    // Maybe there simply is no model connected - not likely, but that is the case in designer.
    if (!m_sourceModel)
        return;

    beginResetModel();
    m_headerView->setModel(this);
    endResetModel();
    connect(m_sourceModel, &QAbstractItemModel::modelAboutToBeReset, this,
            &ColumnHeaderLengthAdapter::beginResetModel);
    connect(m_sourceModel, &QAbstractItemModel::modelReset, this,
            &ColumnHeaderLengthAdapter::endResetModel);

    connect(m_sourceModel, &QAbstractItemModel::columnsAboutToBeInserted, this,
            &ColumnHeaderLengthAdapter::beginResetModel);
    connect(m_sourceModel, &QAbstractItemModel::columnsInserted, this,
            &ColumnHeaderLengthAdapter::endResetModel);

    connect(m_sourceModel, &QAbstractItemModel::columnsAboutToBeMoved, this,
            &ColumnHeaderLengthAdapter::beginResetModel);
    connect(m_sourceModel, &QAbstractItemModel::columnsMoved, this,
            &ColumnHeaderLengthAdapter::endResetModel);

    connect(m_sourceModel, &QAbstractItemModel::columnsAboutToBeRemoved, this,
            &ColumnHeaderLengthAdapter::beginResetModel);
    connect(m_sourceModel, &QAbstractItemModel::columnsRemoved, this,
            &ColumnHeaderLengthAdapter::endResetModel);
}
