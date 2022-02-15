/* MIT License

Copyright (C) 2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include <QApplication>
#include <QDebug>
#include <QHeaderView>
#include <QScrollBar>
#include <QStandardItemModel>
#include <QTableView>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto top = new QWidget;
    QTableView *view = new QTableView;
    QTextEdit *edit = new QTextEdit;
    edit->setText("This edit is just to show the table in a layout");

    auto layout = new QVBoxLayout(top);
    layout->addWidget(view);
    layout->addWidget(edit);
    top->resize(800, 800);

    constexpr int rows = 10;
    constexpr int columns = 5;
    QStandardItemModel model(rows, columns);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            model.setItem(row, col, new QStandardItem(QString("(%1,%2)").arg(row).arg(col)));
        }
    }
    view->setModel(&model);
    auto verticalHeader = view->verticalHeader();
    auto horizontalHeader = view->horizontalHeader();

    if (false) {
        // stretch last column
        horizontalHeader->setStretchLastSection(true);

        // Not sure if this makes sense at all, but at least we got rid of the empty space :-)
        verticalHeader->setStretchLastSection(true);
    }

    if (false) {
        // Stretching other columns that just the last one
        horizontalHeader->setSectionResizeMode(1, QHeaderView::Stretch);
        horizontalHeader->setSectionResizeMode(2, QHeaderView::Stretch);
        horizontalHeader->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    }

    if (false) {
        // compress columns
        horizontalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

    if (true) {
        // compress rows.
        verticalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

    if (false) {
        // Resizing to content initially, but still allowing the columns to be resized later.
        horizontalHeader->setResizeContentsPrecision(-1);
        for (int col = 0; col < columns; ++col)
            view->resizeColumnToContents(col);
        horizontalHeader->setStretchLastSection(true);
    }

    if (true) {
        // Fix the size of the view so it can show without scrollbars
        view->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        view->setSizePolicy({QSizePolicy::Preferred, QSizePolicy::Fixed});

        auto timer = new QTimer;
        timer->setInterval(2000);
        QObject::connect(timer, &QTimer::timeout, [&] {
            model.setRowCount(model.rowCount() + 1);
            model.setItem(model.rowCount() - 1, 0,
                          new QStandardItem(QString("Row %1").arg(model.rowCount())));
        });
        timer->start();
    }

    top->show();
    return a.exec();
}
