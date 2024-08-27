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
#include "serverinterface.h" // just serverName() and objectPath()

#include <QDBusServiceWatcher>
#include <QDBusConnection>
#include <QTimer>

Connection::Connection(QObject *parent) : QObject(parent)
     , m_watcher(new QDBusServiceWatcher(ServerInterface::serverName(),
                                         QDBusConnection::sessionBus(),
                                         QDBusServiceWatcher::WatchForOwnerChange,
                                         this))
{
    connect(m_watcher, &QDBusServiceWatcher::serviceOwnerChanged,
            this, &Connection::slotServiceOwnerChanged);

    Person::registerDBusTypes();
}

Connection::~Connection() = default;

void Connection::connectToServer()
{
    m_serverInterface.reset(new com::kdab::PeopleServerAPI(ServerInterface::serverName(),
                                                           ServerInterface::objectPath(),
                                                           QDBusConnection::sessionBus(),
                                                           this));
    if (m_serverInterface->isValid()) {
        Q_EMIT connected(true);
    }
}

void Connection::disconnectFromServer()
{
    m_serverInterface.reset(nullptr);
    Q_EMIT connected(false);
}


void Connection::slotServiceOwnerChanged(const QString &serviceName, const QString &oldOwner, const QString &newOwner)
{
    Q_ASSERT(serviceName == ServerInterface::serverName()); // that's what the watcher is looking for
    if (newOwner.isEmpty()) { // server went away
        disconnectFromServer();
    } else { // server registered (or transfered to a new owner)
        connectToServer();
    }
}

void Connection::quitServer()
{
    if (m_serverInterface) {
        m_serverInterface->quit();
    }
}

void Connection::queryNextCountry()
{
    if (!m_pendingCountryNames.isEmpty()) {
        const QString country = m_pendingCountryNames.takeFirst();
        QDBusPendingReply<QString> reply = m_serverInterface->getFlagName(country);
        auto watcher = new QDBusPendingCallWatcher(reply, this);
        QObject::connect(watcher, &QDBusPendingCallWatcher::finished,
                         this, [=]() {
            const QString flagName = reply.value();
            if (!flagName.isEmpty()) {
                Q_EMIT countryFlagFetched(country, flagName);
            }
            queryNextCountry();
            watcher->deleteLater();
        });
    }
}

void Connection::queryPersonMatches(const QString &field, const QString &searchValue)
{
    QDBusPendingReply<QVector<Person>> reply = m_serverInterface->getMatches(field, searchValue);
    auto watcher = new QDBusPendingCallWatcher(reply, this);
    QObject::connect(watcher, &QDBusPendingCallWatcher::finished,
                     this, [=]() {
        const QVector<Person> matches = reply.value();
        Q_EMIT matchesFetched(matches);

        QStringList countryNames;
        for (const Person &person : matches) {
            if (!countryNames.contains(person.country)) {
                countryNames.append(person.country);
            }
        }

        // Remember what countries we'll need to query flags for, and start with the first one
        m_pendingCountryNames = countryNames;
        queryNextCountry();

        watcher->deleteLater();
    });
}
