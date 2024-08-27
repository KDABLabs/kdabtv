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
#include "socketworker.h"
#include <QDebug>
#include <QThread>

Connection::Connection(QObject *parent)
    : QObject(parent)
    , m_worker(new SocketWorker) // no parent!
    , m_thread(new QThread)
{
    // Without the qRegisterMetaType below, we get this runtime warning:
    // WARNING:  QObject::connect: Cannot queue arguments of type 'std::vector<Person>'
    // (Make sure 'std::vector<Person>' is registered using qRegisterMetaType().)
    qRegisterMetaType<std::vector<Person>>();

    connect(m_worker.get(), &SocketWorker::connected, this, &Connection::connected);
    connect(m_worker.get(), &SocketWorker::matchesFetched, this, &Connection::matchesFetched);
    connect(m_worker.get(), &SocketWorker::countryFlagFetched, this, &Connection::countryFlagFetched);

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
    QMetaObject::invokeMethod(m_worker.get(), &SocketWorker::connectToServer);
}

void Connection::disconnectFromServer()
{
    QMetaObject::invokeMethod(m_worker.get(), &SocketWorker::disconnectFromServer);
}

void Connection::quitServer()
{
    QMetaObject::invokeMethod(m_worker.get(), &SocketWorker::quitServer);
}

void Connection::queryPersonMatches(const QString &field, const QString &searchValue)
{
    // Important: copy the arguments into the lambda, it'll crash if you capture by reference
    QMetaObject::invokeMethod(m_worker.get(), [=]() {
        m_worker->queryPersonMatches(field, searchValue);
    });
}
