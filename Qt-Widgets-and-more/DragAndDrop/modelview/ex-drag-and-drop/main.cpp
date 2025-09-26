/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "qboxlayout.h"
#include <QtWidgets>

class MyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MyModel(const QStringList &list, QObject *parent = nullptr)
        : QAbstractListModel(parent)
        , _list(list)
    {
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (parent.isValid())
            return 0;
        return _list.count();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid())
            return QVariant();

        if (index.row() < 0 || index.row() >= _list.size())
            return QVariant();

        if (role == Qt::DisplayRole)
            return _list.at(index.row());
        else
            return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override
    {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            Q_ASSERT(section == 0);
            return QString("Country");
        } else
            return QString("Country %1").arg(section);
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        if (!index.isValid())
            return QAbstractListModel::flags(index) | Qt::ItemIsDropEnabled;

        return QAbstractListModel::flags(index) | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override
    {
        Q_UNUSED(role);

        if (index.isValid()) {
            _list.replace(index.row(), value.toString());
            emit dataChanged(index, index, {Qt::DisplayRole});
            return true;
        }
        return false;
    }

    bool insertRows(int position, int rows, const QModelIndex &parent) override
    {
        beginInsertRows(parent, position, position + rows - 1);

        for (int row = 0; row < rows; ++row) {
            _list.insert(position, "");
        }

        endInsertRows();
        return true;
    }

    bool removeRows(int position, int rows, const QModelIndex &parent) override
    {
        beginRemoveRows(parent, position, position + rows - 1);

        for (int row = 0; row < rows; ++row) {
            _list.removeAt(position);
        }

        endRemoveRows();
        return true;
    }

    QStringList mimeTypes() const override
    {
        return QAbstractListModel::mimeTypes() << "text/plain";
    }

    QMimeData *mimeData(const QModelIndexList &indexes) const override
    {
        QStringList list;
        for (const QModelIndex &index : indexes)
            list << data(index).toString();

        QMimeData *mimeData = QAbstractListModel::mimeData(indexes);
        mimeData->setText(list.join(", "));
        return mimeData;
    }

#if 0 // correct, but unnecessary. Default implementation calls insertRow and setData already.
    virtual bool dropMimeData( const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex & parent )
    {
        if  ( data->hasText() ) {
            if ( parent.isValid() ) {
                // drop on an item
                setData( parent, data->text() );
            } else {
                // drop between items
                if (row == -1) {
                    // drop outside items (append)
                    row = rowCount();
                }
                insertRows( row, 1, QModelIndex() );
                setData( index( row, 0, QModelIndex() ), data->text());
            }
            return true;
        }
        else
            return QAbstractListModel::dropMimeData( data, action, row, column, parent );
    }
#endif

    Qt::DropActions supportedDropActions() const override
    {
        return Qt::CopyAction | Qt::MoveAction;
    }

private:
    QStringList _list;
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QStringList countries;
    countries << "Denmark"
              << "Norway"
              << "Sweden"
              << "USA"
              << "Poland";
    MyModel model(countries);

    auto top = new QWidget;
    top->setAttribute(Qt::WA_DeleteOnClose);
    auto layout = new QHBoxLayout(top);

    auto add = [&](QAbstractItemView *view) {
        layout->addWidget(view);
        view->setModel(&model);
        view->setDragEnabled(true);
        view->setAcceptDrops(true);
    };

    add(new QListView);
    add(new QTreeView);

    auto table = new QTableView;
    // table->setDragEnabled(true);
    add(table);

    top->show();
    return app.exec();
}

#include "main.moc"
