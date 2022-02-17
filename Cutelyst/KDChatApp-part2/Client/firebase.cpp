#include "firebase.h"

#include <QLoggingCategory>

#include "firebase-qt/src/firebaseqtapp.h"
#include "firebase-qt/src/firebaseqtmessaging.h"

Firebase::Firebase(QObject *parent) : QObject(parent)
{
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    auto firebase = new FirebaseQtApp(this);

    auto messaging = new FirebaseQtMessaging(firebase);
    connect(messaging, &FirebaseQtMessaging::tokenReceived, this, &Firebase::tokenReceived, Qt::QueuedConnection);
    connect(messaging, &FirebaseQtMessaging::messageReceived, this, &Firebase::messageReceived, Qt::QueuedConnection);

    firebase->initialize();
#endif
}

void Firebase::tokenReceived(const QByteArray &token)
{
    qDebug() << "Got Firebase Messaging token" << token;
    _token = QString::fromLatin1(token);
    Q_EMIT tokenChanged();
}

void Firebase::messageReceived(const QMap<QString, QString> &data)
{
    qDebug() << "Got a Push Notification when the app is running" << data;
}
