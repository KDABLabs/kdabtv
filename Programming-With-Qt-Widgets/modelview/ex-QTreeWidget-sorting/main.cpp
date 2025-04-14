/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "qtreewidget.h"
#include <QtWidgets>

class MyItem : public QTreeWidgetItem
{
public:
    explicit MyItem(int id, QTreeWidgetItem *parent)
        : QTreeWidgetItem(parent)
        , m_id(id)
    {
        setText(0, QString("Sub A - %1").arg(m_id));
        setText(1, QString("Sub B - %1").arg(m_id));
        setText(2, QString("Sub C - %1").arg(m_id));
    }

    bool operator<(const QTreeWidgetItem &other) const override
    {
        int column = treeWidget()->sortColumn();
        if (column == 1) {
            return m_id < static_cast<const MyItem &>(other).m_id;
        }
        return QTreeWidgetItem::operator<(other);
    }

private:
    int m_id;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto tree = new QTreeWidget;
    tree->setAttribute(Qt::WA_DeleteOnClose);

    // ============================================
    //             Play with these
    // ============================================
    tree->setSortingEnabled(true);
    // tree->header()->setSortIndicatorShown(false);
    // tree->header()->setSectionsMovable(false);

    tree->header()->resizeSection(0, 200);

    tree->setHeaderLabels({"Column A", "Column B", "Column C"});

    auto top = new QTreeWidgetItem(tree);
    top->setText(0, "Top A");
    top->setText(1, "Top B");
    top->setText(2, "Top C");

    auto top2 = new QTreeWidgetItem;
    top2->setText(0, "Second Top A");
    top2->setText(1, "Second Top B");
    tree->addTopLevelItem(top2);
    top2->setExpanded(true);

    for (int i = 1; i < 25; ++i) {
        new MyItem(i, top2);
    }

    tree->resize(600, 800);
    tree->show();
    return app.exec();
}
