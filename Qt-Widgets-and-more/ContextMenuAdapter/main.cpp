/* MIT License

Copyright (C) 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "CustomContextMenuAction.h"
#include "QWAMTableView.h"
#include <QApplication>
#include <QDebug>
#include <QStandardItemModel>

using namespace CustomContextMenu;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWAMTableView view;

    QStandardItemModel model(10, 10);
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            model.setItem(row, col, new QStandardItem(QString::number(row * col)));
        }
    }
    view.resize(1100, 400);
    view.setModel(&model);

    // Negate ------------------------
    auto negateFn = [&model](const QModelIndex &index) {
        model.setData(index, -index.data().toInt());
    };

#if VERSION == 1
    auto negateAction = std::make_unique<Action>("Negate", negateFn, onlyOneCellSelected(&view));
    view.addContextMenuAction(std::move(negateAction));
#else
    Action negateAction("Negate", negateFn);
    view.addContextMenuAction(negateAction);
#endif

    // Add Color --------------------------------

    auto addColor = [&](const QString &name, const QColor &color) {
        auto paint = [&](const QModelIndex &) {
            const auto selection = view.selectionModel()->selectedIndexes();
            for (const auto &index : selection)
                model.setData(index, color, Qt::BackgroundRole);
        };

#if VERSION == 1
        view.addContextMenuAction(std::make_unique<Action>("Paint/" + name, paint));
#else
        view.addContextMenuAction(Action("Paint/" + name, paint));
#endif
    };

    addColor("Blue", Qt::blue);
    addColor("Red", Qt::red);
    addColor("Green", Qt::green);

#if VERSION == 1
    view.addContextMenuAction(std::make_unique<Separator>("Paint"));
#else
    view.addContextMenuAction(Separator("Paint"));
#endif

    addColor("Clear", Qt::white);

    view.show();
    app.exec();
}
