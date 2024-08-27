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
#include "dbusworker.h"
#include <QDebug>
#include <QThread>

Connection::Connection(QObject *parent)
    : QObject(parent)
    , m_worker(new DBusWorker) // no parent!
    , m_thread(new QThread)
{
    connect(m_worker.get(), &DBusWorker::connected, this, &Connection::connected);
    connect(m_worker.get(), &DBusWorker::matchesFetched, this, &Connection::matchesFetched);
    connect(m_worker.get(), &DBusWorker::countryFlagFetched, this, &Connection::countryFlagFetched);

    m_worker->moveToThread(m_thread.get());
    m_thread->start();
}

Connection::~Connection()
{
    m_thread->quit();
    m_thread->wait();
}

void Connection::connectToServer()
{
    QMetaObject::invokeMethod(m_worker.get(), &DBusWorker::connectToServer);
}

void Connection::disconnectFromServer()
{
    QMetaObject::invokeMethod(m_worker.get(), &DBusWorker::disconnectFromServer);
}

void Connection::quitServer()
{
    QMetaObject::invokeMethod(m_worker.get(), &DBusWorker::quitServer);
}

void Connection::queryPersonMatches(const QString &field, const QString &searchValue)
{
    // Important: copy the arguments into the lambda, it'll crash if you capture by reference
    QMetaObject::invokeMethod(m_worker.get(), [=]() {
        m_worker->queryPersonMatches(field, searchValue);
    });
}
