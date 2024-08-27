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

#include "connection.h"
#include "serverinterface.h"
#include "basejob.h"

#include <QLocalSocket>
#include <QJsonDocument>
#include <QJsonObject>

#include <QTimer>

Connection::Connection(QObject *parent) : QObject(parent)
    , m_socket(new QLocalSocket(this))
{
    connect(m_socket, &QLocalSocket::connected, this, [this]() {
        //qDebug() << "Connected!";
        Q_EMIT connected(true);
    });
    connect(m_socket, &QLocalSocket::disconnected, this, [this]() {
        //qDebug() << "Disconnected!";
        Q_EMIT connected(false);
    });
    connect(m_socket, &QLocalSocket::errorOccurred, this, [this](QLocalSocket::LocalSocketError socketError) {
        //qDebug() << "Error:" << socketError << "retrying in 100ms";
        Q_EMIT connected(false);

        QTimer::singleShot(500, this, [this]() { connectToServer(); });
    });
    connect(m_socket, &QLocalSocket::readyRead, this, &Connection::slotReadyRead);
}

void Connection::connectToServer()
{
    m_socket->connectToServer(ServerInterface::serverName()); // note that this returns immediately
}

void Connection::disconnectFromServer()
{
    m_socket->disconnectFromServer();
}

void Connection::quitServer()
{
    if (m_socket->state() == QLocalSocket::ConnectedState) {
        QJsonObject query;
        query.insert("command", "quit");
        sendCommand(query);
    }
}

void Connection::sendCommand(const QJsonObject &document)
{
    m_socket->write(QJsonDocument(document).toJson(QJsonDocument::Compact) + '\n');
    m_socket->flush();
}

void Connection::addJob(BaseJob *job)
{
    m_jobs.enqueue(job);
    // The socket's buffer can queue up multiple commands,
    // so send it right away, no need to wait until the current job is done
    sendCommand(job->query());
}

void Connection::slotReadyRead()
{
    while (m_socket->canReadLine()) {
        QByteArray line = m_socket->readLine();
        line.chop(1);
        const QJsonDocument doc = QJsonDocument::fromJson(line);
        const QJsonObject response = doc.object();
        // Dispatch to current job
        Q_ASSERT(!m_jobs.isEmpty());
        auto *currentJob = m_jobs.dequeue();
        currentJob->processResponse(response);
        delete currentJob; // job auto-deletes themselves
    }
}
