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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto tree = new QTreeWidget;
    tree->setAttribute(Qt::WA_DeleteOnClose);
    tree->setSortingEnabled(true);

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

    for (int i = 1; i < 10; ++i) {
        auto sub = new QTreeWidgetItem(top2);
        sub->setText(0, QString("Sub A - %1").arg(i));
        sub->setText(1, QString("Sub B - %1").arg(i));
        sub->setText(2, QString("Sub C - %1").arg(i));
        sub->setIcon(1, QPixmap(QString(":images/%1.png").arg(i)));
    }

    tree->setSelectionMode(QAbstractItemView::MultiSelection);
    tree->setSelectionBehavior(QAbstractItemView::SelectItems);

    QObject::connect(tree, &QTreeWidget::itemSelectionChanged, [tree] {
        qDebug().nospace().noquote() << "Selected:";
        for (auto item : tree->selectedItems()) {
            qDebug().nospace().noquote() << "  " << item->text(0);
        }
    });

    QObject::connect(tree, &QTreeWidget::currentItemChanged,
                     [](QTreeWidgetItem *current, QTreeWidgetItem *previous) {
                         qDebug().nospace().noquote()
                             << "Current: +++" << (current ? current->text(0) : "NONE");
                         qDebug().nospace().noquote()
                             << "         ---" << (previous ? previous->text(0) : "NONE");
                     });

    QObject::connect(tree->selectionModel(), &QItemSelectionModel::selectionChanged,
                     [](const QItemSelection &selected, const QItemSelection &deselected) {
                         qDebug().nospace().noquote() << "Selection Model:";
                         for (auto index : selected.indexes()) {
                             qDebug().nospace().noquote() << "  +" << index.data().toString();
                         }
                         for (auto index : deselected.indexes()) {
                             qDebug().nospace().noquote() << "  -" << index.data().toString();
                         }
                     });

    tree->resize(600, 800);
    tree->show();
    return app.exec();
}
