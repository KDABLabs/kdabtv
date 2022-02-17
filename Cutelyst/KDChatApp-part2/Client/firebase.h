#ifndef FIREBASE_H
#define FIREBASE_H

#include <QObject>

class Firebase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString token MEMBER _token NOTIFY tokenChanged)
public:
    explicit Firebase(QObject *parent = nullptr);

    void tokenReceived(const QByteArray &token);
    void messageReceived(const QMap<QString, QString> &data);

Q_SIGNALS:
    void tokenChanged();

private:
    QString _token;
};

#endif // FIREBASE_H
