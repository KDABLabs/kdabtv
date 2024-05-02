/* MIT License

Copyright (C) 2023 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QRandomGenerator>
#include <QThread>
#include <QVBoxLayout>

namespace {
class Widget : public QWidget
{
protected:
    void paintEvent(QPaintEvent *event)
    {
        static int counter = 0;
        qDebug() << "Repainting!" << ++counter;
        QPainter painter(this);

        QColor color(QRandomGenerator::global()->bounded(255),
                     QRandomGenerator::global()->bounded(255),
                     QRandomGenerator::global()->bounded(255));
        painter.fillRect(event->rect(), color);
        //        QThread::msleep(100);
    }
    QSize sizeHint() const override { return QSize(500, 500); }
};
} // end namespace

void part1()
{
    auto top = new QWidget;
    auto layout = new QVBoxLayout(top);

    auto foo = new Widget;
    layout->addWidget(foo);

    auto button = new QPushButton("update");
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [foo] {
        for (int i = 0; i < 3; ++i)
            foo->update();
    });

    button = new QPushButton("repaint");
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [foo] {
        for (int i = 0; i < 10; ++i)
            foo->repaint();
    });

    top->show();
}
