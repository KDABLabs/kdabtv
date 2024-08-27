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

#include "dbusworker.h"
#include "serverinterface.h" // just serverName() and objectPath()

#include <QDBusServiceWatcher>
#include <QDBusConnection>
#include <QTimer>

DBusWorker::DBusWorker(QObject *parent) : QObject(parent)
     , m_watcher(new QDBusServiceWatcher(ServerInterface::serverName(),
                                         QDBusConnection::sessionBus(),
                                         QDBusServiceWatcher::WatchForOwnerChange,
                                         this))
{
    connect(m_watcher, &QDBusServiceWatcher::serviceOwnerChanged,
            this, &DBusWorker::slotServiceOwnerChanged);

    Person::registerDBusTypes();
}

DBusWorker::~DBusWorker() = default;

void DBusWorker::connectToServer()
{
    Q_ASSERT(QThread::currentThread() != QCoreApplication::instance()->thread());

    m_serverInterface.reset(new com::kdab::PeopleServerAPI(ServerInterface::serverName(),
                                                           ServerInterface::objectPath(),
                                                           QDBusConnection::sessionBus(),
                                                           this));
    if (m_serverInterface->isValid()) {
        Q_EMIT connected(true);
    }
}

void DBusWorker::disconnectFromServer()
{
    m_serverInterface.reset(nullptr);
    Q_EMIT connected(false);
}


void DBusWorker::slotServiceOwnerChanged(const QString &serviceName, const QString &oldOwner, const QString &newOwner)
{
    Q_ASSERT(serviceName == ServerInterface::serverName()); // that's what the watcher is looking for
    if (newOwner.isEmpty()) { // server went away
        disconnectFromServer();
    } else { // server registered (or transfered to a new owner)
        connectToServer();
    }
}

void DBusWorker::quitServer()
{
    if (m_serverInterface) {
        m_serverInterface->quit();
    }
}

void DBusWorker::queryPersonMatches(const QString &field, const QString &searchValue)
{
    Q_ASSERT(QThread::currentThread() != QCoreApplication::instance()->thread());

    QDBusPendingReply<QVector<Person>> reply = m_serverInterface->getMatches(field, searchValue);
    reply.waitForFinished(); // no need for QDBusPendingCallWatcher anymore
    if (reply.isError()) {
        qWarning() << reply.error();
        return;
    }

    const QVector<Person> matches = reply.value();
    Q_EMIT matchesFetched(matches);

    QStringList countryNames;
    for (const Person &person : matches) {
        if (!countryNames.contains(person.country)) {
            countryNames.append(person.country);
        }
    }

    // Fetch flags
    queryFlags(countryNames);
}

void DBusWorker::queryFlags(const QStringList &countryNames)
{
    // Query country flags synchronously
    for (const QString &country : qAsConst(countryNames)) {
        QDBusPendingReply<QString> reply = m_serverInterface->getFlagName(country);
        reply.waitForFinished();
        if (reply.isError()) {
            qWarning() << reply.error();
        } else {
            const QString flagName = reply.value();
            if (!flagName.isEmpty()) {
                Q_EMIT countryFlagFetched(country, flagName);
            }
        }
    }
}
