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

#pragma once

#include <QObject>
#include <vector>
class Person;

class QLocalSocket;

class SocketWorker : public QObject
{
    Q_OBJECT
public:
    explicit SocketWorker(QObject *parent = nullptr);

    void connectToServer();
    void disconnectFromServer();
    void quitServer();
    void queryPersonMatches(const QString &field, const QString &searchValue);

signals:
    void connected(bool);
    void matchesFetched(const std::vector<Person> &matches);
    void countryFlagFetched(const QString &country, const QString &flagName);

private:
    bool waitForReadyRead();
    QJsonDocument readResponse();
    void sendCommand(const QJsonObject &document);
    void queryFlags(const QStringList &countryNames);

    QLocalSocket *m_socket = nullptr;
};
