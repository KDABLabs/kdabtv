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

#include "widget.h"
#include "ui_widget.h"

#include "../server/serverinterface.h" // this will become a shared library in part 2

#include <QDebug>
#include <QProcess>
#include <QTimer>

#include <QLocalSocket>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_socket(new QLocalSocket(this))

{
    ui->setupUi(this);

    // Run server
    if (true) {
        // For ease of development: let's start the server ourselves
        // In production, you probably have both things running independently
        m_process = new QProcess(this);
        connect(m_process, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
            qWarning() << "Error:" << error;
        });

        m_process->setProcessChannelMode(QProcess::ForwardedChannels);

        const QString binDir = QApplication::applicationDirPath();
#ifdef Q_OS_WIN
        m_process->start(binDir + "/PeopleServer.exe", QStringList());
#else
        m_process->start(binDir + "/PeopleServer", QStringList());
#endif
        const bool ok = m_process->waitForStarted(); // so we can connect to it
        if (ok) {
            qDebug() << "PeopleServer started";
        } // otherwise errorOccured() is emitted
    }

    // Prepare GUI
    connect(ui->runButton, &QPushButton::clicked, this, &Widget::runQuery);
    ui->runButton->setEnabled(false); // we're not connected yet

    // Prepare socket
    connect(m_socket, &QLocalSocket::connected, this, [this]() {
        //qDebug() << "Connected!";
        ui->runButton->setEnabled(true); // ready!
    });
    connect(m_socket, &QLocalSocket::disconnected, this, [this]() {
        //qDebug() << "Disconnected!";
        ui->runButton->setEnabled(false);
    });
    connect(m_socket, &QLocalSocket::errorOccurred, this, [this](QLocalSocket::LocalSocketError socketError) {
        //qDebug() << "Error:" << socketError << "retrying in 100ms";
        ui->runButton->setEnabled(false);
        QTimer::singleShot(500, this, [this]() { connectToServer(); });
    });

    // Go!
    connectToServer();
}

Widget::~Widget()
{
    if (m_socket->state() == QLocalSocket::ConnectedState) {
        if (m_process && m_process->state() == QProcess::Running) {
            m_socket->write("QUIT\n");
            m_socket->flush();
            m_process->waitForFinished();
        }
        m_socket->disconnectFromServer();
    }
    delete ui;
}


void Widget::connectToServer()
{
    m_socket->connectToServer(s_serverName); // note that this returns immediately
}

void Widget::runQuery()
{
    m_socket->write("HELLO\n");
    m_socket->flush();
}
