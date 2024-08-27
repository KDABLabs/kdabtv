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

#include <QLocalSocket>
#include <QJsonArray>
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

void Connection::queryNextCountry()
{
    if (!m_pendingCountryNames.isEmpty()) {
        QJsonObject query;
        query.insert("command", "getFlagName");
        query.insert("country", m_pendingCountryNames.constFirst());
        sendCommand(query);
    }
}

void Connection::queryPersonMatches(const QString &field, const QString &searchValue)
{
    QJsonObject query;
    query.insert("command", "getMatches");
    query.insert("field", field);
    query.insert("searchValue", searchValue);
    sendCommand(query);
}

void Connection::slotReadyRead()
{
    while (m_socket->canReadLine()) {
        QByteArray line = m_socket->readLine();
        line.chop(1);
        const QJsonDocument doc = QJsonDocument::fromJson(line);
        const QJsonObject response = doc.object();
        // Dispatch based on the command this is a response for
        const QString command = response.value("command").toString();
        if (command == u"getMatches") {
            processGetMatchesResponse(response);
        } else if (command == u"getFlagName") {
            processGetFlagNameResponse(response);
        }
    }
}

void Connection::processGetMatchesResponse(const QJsonObject &response)
{
    // Fill table widget based on received matches
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

    // Remember what countries we'll need to query flags for, and start with the first one
    m_pendingCountryNames = countryNames;
    queryNextCountry();
}

void Connection::processGetFlagNameResponse(const QJsonObject &response)
{
    // this could also be repeated as part of the response...
    const QString country = m_pendingCountryNames.takeFirst();

    const QString flagName = response.value("flag").toString();
    if (!flagName.isEmpty()) {
        Q_EMIT countryFlagFetched(country, flagName);
    }

    queryNextCountry();
}



