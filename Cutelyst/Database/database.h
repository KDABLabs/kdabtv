#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class QJsonArray;
class DatabaseThread;

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

    Q_INVOKABLE void qsqlQuery();
    Q_INVOKABLE void qsqlQueryThread();
    Q_INVOKABLE void asqlQuery();
    Q_INVOKABLE void cancelAsqlQuery();

    Q_INVOKABLE void migrate(int target);
    Q_INVOKABLE void countRows();

Q_SIGNALS:
    void gotResult(const QJsonArray &rows);

private:
    DatabaseThread *m_dbThread;
    QObject *m_queryCanceler = nullptr;
};

#endif // DATABASE_H
