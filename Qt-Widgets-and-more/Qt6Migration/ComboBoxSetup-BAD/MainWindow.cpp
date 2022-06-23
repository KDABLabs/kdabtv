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

#include "MainWindow.h"
#include "ComboBoxHelper.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->badCombo, qOverload<int>(&QComboBox::activated), this, &MainWindow::doBadStuff);

    int setupMethod = 0;
    if (setupMethod == 0)
        ComboBoxHelper::setup<GoodThings>(ui->goodCombo, GoodThings::KDABVideos,
                                          {{"Angels", GoodThings::Angels},
                                           {"Depeche Mode", GoodThings::DepecheMode},
                                           {"KDAB Videos on YouTube", GoodThings::KDABVideos}},
                                          this, &MainWindow::doGoodThings);
    else if (setupMethod == 1)
        ComboBoxHelper::setup<GoodThings>(ui->goodCombo, GoodThings::KDABVideos,
                                          {{"Angels", GoodThings::Angels},
                                           {"Depeche Mode", GoodThings::DepecheMode},
                                           {"KDAB Videos on YouTube", GoodThings::KDABVideos}});
    else
        ComboBoxHelper::setup<GoodThings>(ui->goodCombo, GoodThings::KDABVideos,
                                          {{"Angels", GoodThings::Angels},
                                           {"Depeche Mode", GoodThings::DepecheMode},
                                           {"KDAB Videos on YouTube", GoodThings::KDABVideos}},
                                          [this](GoodThings which) { doGoodThings(which); });
    connect(ui->reset, &QPushButton::clicked, this, &MainWindow::reset);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doBadStuff(int which)
{
    if (which == 0) {
        qDebug() << "I believe wars was selected, lets hope no one added something above it....";
    } else if (ui->badCombo->itemText(which) == "Mispellinks")
        qDebug() << "Oh my the world will implode if anyone ever fixes my spellinks :-)";
    else
        qDebug() << "Whatever..." << which;
}

void MainWindow::doGoodThings(MainWindow::GoodThings which)
{
    switch (which) {
    case GoodThings::Angels:
        qDebug() << "Angels are good assuming they exists.";
        break;
    case GoodThings::DepecheMode:
        qDebug() << "Enjoy the Silence...";
        break;
    case GoodThings::KDABVideos:
        qDebug() << "http://kdab.tv rocks!";
    }
}

void MainWindow::reset()
{
    ComboBoxHelper::setCurrentValue(ui->goodCombo, GoodThings::KDABVideos);
}
