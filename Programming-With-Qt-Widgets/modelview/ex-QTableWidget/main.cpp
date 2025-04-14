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

void fill(QTableWidget *table, int rows, int columns)
{
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            QString text = QString::number((row + 1) * (column + 1));
            auto item = new QTableWidgetItem(text);
            table->setItem(row, column, item);
        }
    }
}

void showTimesTable()
{
    auto table = new QTableWidget(10, 10);
    table->setAttribute(Qt::WA_DeleteOnClose);
    fill(table, 10, 10);

    QTimer::singleShot(5000, [table] {
        table->setRowCount(20);
        table->setColumnCount(5);
        fill(table, 20, 5);
    });

    table->resize(1000, 500);
    table->show();
}

void setItemsInTable()
{
    auto table = new QTableWidget(3, 3);
    table->setAttribute(Qt::WA_DeleteOnClose);

    auto item1 = new QTableWidgetItem("X");
    auto item2 = new QTableWidgetItem("O");
    auto item3 = new QTableWidgetItem("X");
    table->setItem(1, 1, item1);
    table->setItem(1, 2, item2);
    table->setItem(2, 0, item3);

    QFont font;
    font.setPointSize(24);
    table->setFont(font);

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            auto item = table->item(row, column);
            if (item)
                item->setTextAlignment(Qt::AlignCenter);
        }
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();

    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
    table->show();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    showTimesTable();
    setItemsInTable();

    return app.exec();
}
