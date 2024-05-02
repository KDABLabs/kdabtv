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
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QResizeEvent>
#include <QThread>
#include <QWidget>

namespace {
class Widget : public QWidget
{
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        static int i = 0;
        qDebug() << "mousePressEvent" << event->pos() << ++i;
        m_path.moveTo(event->pos());
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        static int counter = 0;
        qDebug() << "mouseMoveEvent" << event->pos() << ++counter;
        QThread::msleep(100);
        m_path.lineTo(event->pos());
        update();
    }

    QSize sizeHint() const override { return QSize(500, 500); }

    void paintEvent(QPaintEvent * /*event*/) override
    {
        QPainter painter(this);
        painter.setPen(QPen(Qt::black, 4));
        painter.drawPath(m_path);
    }

    void moveEvent(QMoveEvent *event) override
    {
        static int i = 0;
        qDebug() << "moveEvent" << event->pos() << ++i;
        QThread::msleep(500);
        update();
    }

    void resizeEvent(QResizeEvent *event) override
    {
        static int i = 0;
        qDebug() << "resizeEvent" << event->size() << ++i;
        QThread::msleep(500);
        update();
    }

private:
    QPainterPath m_path;
};
} // end namespace

void part2()
{
    auto top = new Widget;
    top->show();
}
