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
#include <QApplication>
#include <QStandardItemModel>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStandardItemModel model(5, 3);
    QStringList randomStuff{"Depeche Mode", "The Cure", "Naiive",      "Nitzer Ebb", "Erasure",
                            "Virkelyst",    "16",       "Hjørring",    "Denmark",    "The Earth",
                            "Laura",        "Louise",   "Anne Helene", "Jesper",     "NAN"};

    for (int col = 0; col < 3; ++col) {
        for (int row = 0; row < 5; ++row) {
            QString txt = randomStuff.at((row + col * 5) % randomStuff.length());
            model.setData(model.index(row, col), txt);
        }
    }

    //    model.setHorizontalHeaderLabels(
    //        {"Bands from the 80th I love", "My patch of the universe", "My Family"});

    model.setHeaderData(0, Qt::Horizontal,
                        QStringList{"Bands from the 80th I love", "80th bands", "Bands", "80th"});
    model.setHeaderData(1, Qt::Horizontal,
                        QStringList{"My patch of the universe", "Here I live", "Location"});
    model.setHeaderData(2, Qt::Horizontal, QStringList{"My Family", "Just us", "us", "-"});

    QTableView table;
    new ColumnHeaderLengthAdapter(&table);
    table.setModel(&model);
    table.show();

    return a.exec();
}
