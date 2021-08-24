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
#include "CheckableHeaderView.h"
#include "DepecheModel.h"
#include <QApplication>
#include <QDebug>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto top = new QWidget;

    auto table = new QTableView;
    auto model = new DepecheModel(table);
    table->setModel(model);
    auto headerview = new CheckableHeaderView(Qt::Vertical);
    headerview->setSectionsClickable(true);
    headerview->setHighlightSections(true);
    table->setVerticalHeader(headerview);

    auto vLay = new QVBoxLayout(top);
    vLay->addWidget(table);

    auto hLay = new QHBoxLayout;
    vLay->addLayout(hLay);
    hLay->addStretch(1);

    auto button = new QPushButton("Play Songs");
    hLay->addWidget(button);

    QObject::connect(button, &QPushButton::clicked, [model] {
        for (auto &album : model->selectedAlbums()) {
            qDebug().noquote() << "♫♫" << album << "♪♪";
        }
    });

    top->resize(800, 400);
    top->show();
    return a.exec();
}
