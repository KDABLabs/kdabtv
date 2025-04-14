#include "TreeModel.h"
#include "TreeNode.h"
#include <QDebug>

TreeModel::TreeModel(TreeNode *root, QObject *parent)
    : QAbstractItemModel(parent)
    , m_root(root)
{
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return m_root->data(section);
    }
    return {};
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    TreeNode *parentNode = treeNodeFromIndex(parent);
    TreeNode *ptr = parentNode->child(row);
    return createIndex(row, column, ptr);
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return {};

    TreeNode *myNode = treeNodeFromIndex(index);
    TreeNode *parentNode = myNode->parentNode();
    if (parentNode == m_root)
        return {};

    int row = parentNode->row();
    return createIndex(row, 0, parentNode);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeNode *data = treeNodeFromIndex(parent);
    return data->childCount();
}

int TreeModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    TreeNode *node = treeNodeFromIndex(index);
    return node->data(index.column());
}
TreeNode *TreeModel::treeNodeFromIndex(const QModelIndex &index) const
{
    if (!index.isValid())
        return m_root;
    else
        return static_cast<TreeNode *>(index.internalPointer());
}
