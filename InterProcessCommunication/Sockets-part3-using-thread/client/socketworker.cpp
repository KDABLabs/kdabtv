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
OUT OF OR IN SocketWorker WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "socketworker.h"
#include "person.h"
#include "serverinterface.h"

#include <QLocalSocket>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <QCoreApplication>

#include <QTimer>

SocketWorker::SocketWorker(QObject *parent) : QObject(parent)
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
}

void SocketWorker::connectToServer()
{
    Q_ASSERT(QThread::currentThread() != QCoreApplication::instance()->thread());
    m_socket->connectToServer(ServerInterface::serverName()); // note that this returns immediately
    // we could use m_socket->waitForConnected() if we wanted to follow up with an initial command
}

void SocketWorker::disconnectFromServer()
{
    Q_ASSERT(QThread::currentThread() != QCoreApplication::instance()->thread());
    m_socket->disconnectFromServer();
}

void SocketWorker::quitServer()
{
    Q_ASSERT(QThread::currentThread() != QCoreApplication::instance()->thread());
    if (m_socket->state() == QLocalSocket::ConnectedState) {
        QJsonObject query;
        query.insert("command", "quit");
        sendCommand(query);
    }
}

void SocketWorker::sendCommand(const QJsonObject &document)
{
    m_socket->write(QJsonDocument(document).toJson(QJsonDocument::Compact) + '\n');
    m_socket->flush();
}

bool SocketWorker::waitForReadyRead()
{
    // We should never have data waiting for us already since we didn't go to the event loop
    Q_ASSERT(!m_socket->canReadLine());
    if (!m_socket->waitForReadyRead()) {
        qWarning() << "Socket timeout, disconnecting";
        m_socket->disconnectFromServer();
        return false;
    }
    return true;
}

QJsonDocument SocketWorker::readResponse()
{
    Q_ASSERT(m_socket->canReadLine());
    QByteArray line = m_socket->readLine();
    line.chop(1);
    return QJsonDocument::fromJson(line);
}

void SocketWorker::queryPersonMatches(const QString &field, const QString &searchValue)
{
    Q_ASSERT(QThread::currentThread() != QCoreApplication::instance()->thread());

    // Send getMatches request
    QJsonObject query;
    query.insert("command", "getMatches");
    query.insert("field", field);
    query.insert("searchValue", searchValue);
    sendCommand(query);

    // Wait for response
    if (!waitForReadyRead()) {
        return;
    }

    // Read and process response
    const QJsonDocument doc = readResponse();
    const QJsonObject response = doc.object();
    const QJsonArray array = response.value("matches").toArray();
    const int numMatches = array.size();
    std::vector<Person> matches;
    matches.reserve(numMatches);
    QStringList countryNames;
    for (const QJsonValue &value : array) {
        Person person = Person::fromJsonValue(value.toObject());
        if (!countryNames.contains(person.country)) {
            countryNames.append(person.country);
        }
        matches.push_back(std::move(person));
    }
    Q_EMIT matchesFetched(matches);

    // Fetch flags
    queryFlags(countryNames);
}

void SocketWorker::queryFlags(const QStringList &countryNames)
{
    // Query country flags synchronously
    for (const QString &country : qAsConst(countryNames)) {
        QJsonObject query;
        query.insert("command", "getFlagName");
        query.insert("country", country);
        sendCommand(query);
        if (!waitForReadyRead()) {
            break;
        }
        // Read and process response
        const QJsonDocument doc = readResponse();
        const QJsonObject response = doc.object();
        Q_ASSERT(response.value("command").toString() == u"getFlagName");
        const QString flagName = response.value("flag").toString();
        if (!flagName.isEmpty()) {
            Q_EMIT countryFlagFetched(country, flagName);
        }
    }
}



