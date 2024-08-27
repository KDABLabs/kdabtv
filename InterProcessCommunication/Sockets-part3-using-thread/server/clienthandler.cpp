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

#include "clienthandler.h"
#include "database.h"

#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLocalSocket>

ClientHandler::ClientHandler(QLocalSocket *socket, Database &database, QObject *parent)
    : QObject(parent)
    , m_clientSocket(socket)
    , m_database(database)
{
    // Delete the socket when deleting the handler
    m_clientSocket->setParent(this);
    connect(m_clientSocket, &QLocalSocket::readyRead, this, &ClientHandler::slotReadyRead);
    connect(m_clientSocket, &QLocalSocket::disconnected, this, &QObject::deleteLater);
}

void ClientHandler::writeResponse(const QJsonObject &response)
{
    const QByteArray bytes = QJsonDocument(response).toJson(QJsonDocument::Compact);
    qDebug().noquote() << bytes;
    m_clientSocket->write(bytes + '\n');
}

void ClientHandler::slotReadyRead()
{
    while (m_clientSocket->canReadLine()) {
        QByteArray line = m_clientSocket->readLine();
        line.chop(1);
        qDebug().noquote() << line;
        const QJsonDocument doc = QJsonDocument::fromJson(line);
        const QJsonObject topObject = doc.object();
        const QString command = topObject.value("command").toString();
        if (command == u"quit") {
            QCoreApplication::instance()->quit();
            return;
        }
        QJsonObject response;
        response.insert("command", command); // remind the client what they asked for...
        if (command == u"getMatches") {
            const QString searchValue = topObject.value("searchValue").toString();
            const QString field = topObject.value("field").toString();
            const std::vector<Person> results = m_database.search(field, searchValue);
            QJsonArray array;
            std::transform(results.cbegin(), results.cend(), std::back_inserter(array), std::mem_fn(&Person::toJsonValue));
            response.insert("matches", array);
            writeResponse(response);
        } else if (command == u"getFlagName") {
            const QString country = topObject.value("country").toString();
            const QString flagName = m_database.countryFlag(country);
            response.insert("flag", flagName);
            writeResponse(response);
        }
    }
}
