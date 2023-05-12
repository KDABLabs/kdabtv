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

#include <QApplication>
#include <QColor>
#include <QDebug>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <chrono>

using namespace std::chrono_literals;

namespace {
class BrokenClock : public QLabel
{
    Q_OBJECT
public:
    BrokenClock()
    {
        QFont font;
        font.setPointSize(100);
        setFont(font);
        connect(&m_timer, &QTimer::timeout, this, &BrokenClock::updateTime);
        updateTime();
        m_timer.setTimerType(Qt::PreciseTimer);
        m_timer.start();
    }

private:
    void updateTime()
    {
        qDebug() << QTime::currentTime().toString("HH:mm:ss zzz");
        QString text = QTime::currentTime().toString("HH:mm:ss");
        setText(text);
        QPalette pal;
        pal.setColor(QPalette::WindowText, (++m_color % 2) ? QColor(Qt::blue) : QColor(Qt::red));
        setPalette(pal);
        m_timer.setInterval(1000 - QTime::currentTime().msec());
    }

    QTimer m_timer;
    int m_color = 0;
};

} // end namespace

void part1()
{
    qDebug() << "========== timers - part1 ==========";
    auto clock = new BrokenClock;
    clock->show();
}

#include "part1.moc"
