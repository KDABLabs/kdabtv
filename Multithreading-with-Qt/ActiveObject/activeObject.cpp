/*****************************************************************************************
 *
 * Copyright (c) 2015, Klaralvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 ******************************************************************************************/

#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <memory>

// This class is a object whose event handling will happen in an internal secondary thread.
// That thread is entirely hidden from the user of the class.
// This pattern is called "active object" (http://www.drdobbs.com/parallel/prefer-using-active-objects-instead-of-n/225700095)
class Worker : public QObject
{
    Q_OBJECT
public:
    // called by main thread
    Worker() {
        // We use a timer as the emitter of a signal; a more realistic use case would be a socket for instance
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &Worker::go);
        m_timer->start(500);

        m_thread = std::make_unique<QThread>(); // Do NOT pass 'this' as parent here. moveToThread moves all children, so this shouldn't be a child!
        m_thread->setObjectName("Secondary Thread");
        moveToThread(m_thread.get());
        m_thread->start();

        qDebug("Construction:");
        qDebug("=============");
        qDebug("Current thread: %s", qPrintable(QThread::currentThread()->objectName()));
        qDebug("Thread for timer: %s", qPrintable(m_timer->thread()->objectName()));
        qDebug("!!! Thread for the object itself: %s\n", qPrintable(thread()->objectName()));

        reconfigure();
    }

    // called by main thread
    ~Worker() override
    {
        QMetaObject::invokeMethod(this, "cleanup");
        m_thread->wait();
    }

    // called by main thread
    void reconfigure()
    {
        QMetaObject::invokeMethod(this, "reconfigure_impl");
    }

signals:
    void quitApp();

private slots:
    // called by secondary thread
    void go() {
        qDebug("In the 'go' slot:");
        qDebug("============");
        qDebug("!!! Current thread: %s\n", qPrintable(QThread::currentThread()->objectName()));

        emit quitApp(); // In this example we don't want to keep running forever
    }

    // called by secondary thread
    void reconfigure_impl()
    {
        qDebug("In reconfigure_impl:");
        qDebug("============");
        qDebug("!!! Current thread: %s\n", qPrintable(QThread::currentThread()->objectName()));
    }
    // called by secondary thread
    void cleanup()
    {
        delete m_timer;
        m_thread->quit();
    }

private:
    QTimer* m_timer;
    std::unique_ptr<QThread> m_thread;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.thread()->setObjectName("Main Thread");
    auto worker = new Worker; // could be on the stack in this simple example, but this is to show a more general use case

    QObject::connect(worker, &Worker::quitApp, &a, [&](){
            qDebug("In the main() lambda:");
            qDebug("============");
            qDebug("!!! Current thread: %s\n", qPrintable(QThread::currentThread()->objectName()));
            delete worker; // or better, use std::unique_ptr::reset()
            a.quit();
    });

    return a.exec();
}

#include "activeObject.moc"
