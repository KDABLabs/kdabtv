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
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <chrono>

using namespace std::chrono_literals;

namespace {
class Test
{
public:
    Test()
    {
        auto timer = new QTimer;
        timer->setInterval(300ms);
        //        timer->setTimerType(Qt::PreciseTimer);
        QObject::connect(timer, &QTimer::timeout, [this, timer] {
            qDebug() << QTime::currentTime().toString("mm:ss zzz");
            if (m_countCount++ == 20)
                timer->stop();
        });
        timer->start();

        timer = new QTimer;
        timer->setInterval(2s);
        QObject::connect(timer, &QTimer::timeout, [this, timer] {
            qDebug("Good Night");
            qApp->thread()->sleep(1);
            qDebug("Good Morning");
            ++m_countSleep;
            if (m_countSleep == 5)
                timer->stop();
        });
        timer->start();
    }

private:
    int m_countCount = 0;
    int m_countSleep = 0;
};
} // end namespace

void part2()
{
    qDebug() << "========== timers - part2 ==========";
    new Test();
}
