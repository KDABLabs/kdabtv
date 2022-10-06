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

#include "MainWindow.h"
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <chrono>
#include <qshortcut.h>

using namespace std::chrono_literals;

MainWindow::MainWindow(QWidget *parent)
    : QLabel(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    // Timer to drive the flip
    m_timer = new QTimer(this);
    m_timer->setInterval(300ms);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::switchImage);

    // Label showing which view is the active one
    m_title = new QLabel(this);
    m_title->setAutoFillBackground(true);
    QPalette pal;
    pal.setBrush(QPalette::Window, Qt::white);
    m_title->setPalette(pal);
    QFont font;
    font.setPixelSize(20);
    m_title->setFont(font);

    // Listen to the clipboard for new images
    connect(qApp->clipboard(), &QClipboard::changed, this, &MainWindow::takeImage);

    // Spacebar will toggle between images
    auto shortcut = new QShortcut(Qt::Key_Space, this);
    QObject::connect(shortcut, &QShortcut::activated, this, [this] {
        stop();
        switchImage();
    });
}

void MainWindow::start()
{
    m_timer->start();
}

void MainWindow::stop()
{
    m_timer->stop();
}

void MainWindow::switchImage()
{
    m_image1Shown = !m_image1Shown;
    setPixmap(m_image1Shown ? m_pix1 : m_pix2);
    m_title->setText(m_image1Shown ? "Baseline" : "Regression");
    m_title->resize(m_title->sizeHint());
}

void MainWindow::takeImage(QClipboard::Mode mode)
{
    // Skip changes to selection
    if (mode != QClipboard::Clipboard)
        return;

    // Spectacle seems to be putting something on the clipboard after a few seconds, which makes
    // this app beleive something has changed.
    auto formats = qApp->clipboard()->mimeData()->formats();

    if (formats.isEmpty() || formats.contains("application/x-kde-onlyReplaceEmpty"))
        return;

    if (m_shootBaseLineNext) {
        stop();
        m_pix1 = qApp->clipboard()->pixmap();
        setPixmap(m_pix1);
    } else {
        m_pix2 = qApp->clipboard()->pixmap();
        start();
    }
    m_shootBaseLineNext = !m_shootBaseLineNext;
}
