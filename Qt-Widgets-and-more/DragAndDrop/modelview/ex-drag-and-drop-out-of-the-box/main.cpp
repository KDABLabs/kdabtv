/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

#if 1
    QStringList countries;
    countries << "Denmark"
              << "Norway"
              << "Sweden"
              << "USA"
              << "Poland";
    QStringListModel model(countries);
#else
    QStandardItemModel model(10, 3);
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 3; ++col) {
            model.setData(model.index(row, col), QString("(%1,%2)").arg(row).arg(col));
        }
    }
#endif

    auto top = new QWidget;
    top->setAttribute(Qt::WA_DeleteOnClose);
    auto layout = new QHBoxLayout(top);

    auto add = [&](QAbstractItemView *view) {
        layout->addWidget(view);
        view->setModel(&model);
        view->setDragEnabled(true);
        view->setAcceptDrops(true);
        // view->setDragDropMode(QAbstractItemView::InternalMove);
    };

    add(new QListView);
    add(new QTreeView);

    auto table = new QTableView;
    //    table->setDragEnabled(true);
    add(table);

    top->show();
    return app.exec();
}
