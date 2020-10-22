/* MIT License

Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "HeaderSortingAdapter.h"
#include <QApplication>
#include <QHeaderView>
#include <QMenu>
#include <QRandomGenerator>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList columnNames{"Monkeys", "Apples", "Compilers", "Gizzmos", "Bars"};
    constexpr int rowCount = 100;
    constexpr int columnCount = 5;

    QRandomGenerator generator;

    QStandardItemModel model(rowCount, columnCount);
    for (int column = 0; column < columnCount; ++column) {
        model.setHeaderData(column, Qt::Horizontal, columnNames.at(column));
        for (int row = 0; row < rowCount; ++row) {
            model.setData(model.index(row, column), generator.bounded(0, 1000));
            model.setHeaderData(row, Qt::Vertical, QString("row %1").arg(row + 1));
        }
    }

    QSortFilterProxyModel sortProxy;
    sortProxy.setSourceModel(&model);

    QTableView view;
    view.setSortingEnabled(true);
    view.horizontalHeader()->setSectionsMovable(true);
    view.setModel(&sortProxy);

    view.horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(view.horizontalHeader(), &QHeaderView::customContextMenuRequested, [] {
        QMenu menu;
        menu.addAction("Amazing");
        menu.addAction("Cool stuff!");
        menu.exec(QCursor::pos());
    });

    // The magic line
    HeaderSortingAdapter adapter(&view);

    view.resize(600, 400);
    view.show();

    return a.exec();
}
