#include "database.h"

#include <QThread>

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QJsonArray>
#include <QJsonObject>

#include <QLoggingCategory>

#include <adatabase.h>
#include <aresult.h>
#include <apool.h>
#include <amigrations.h>
#include <apg.h>

class DatabaseThread : public QObject
{
    Q_OBJECT
public:
    DatabaseThread() = default;

Q_SIGNALS:
    void gotResult(const QJsonArray &rows);

public Q_SLOTS:
    void openDatabaseOnThread() {
        auto db =  QSqlDatabase::addDatabase("QPSQL", "threaded");
        db.setDatabaseName("testdb");
        if (!db.open()) { // Blocking Call
            qWarning("Failed to open threaded DB");
        }
    }
    void qsqlQueryThread();
};

Database::Database(QObject *parent) : QObject(parent)
{
    // QtSql
    auto db = QSqlDatabase::addDatabase("QPSQL", "local");
    db.setDatabaseName("testdb");
    if (!db.open()) { // Blocking Call
        qWarning("Failed to open local DB");
    }

    auto thread = new QThread(this);
    m_dbThread = new DatabaseThread;
    m_dbThread->moveToThread(thread);
    connect(thread, &QThread::started, m_dbThread, &DatabaseThread::openDatabaseOnThread);
    connect(m_dbThread, &DatabaseThread::gotResult, this, &Database::gotResult, Qt::QueuedConnection);

    thread->start();

    // ASql
    APool::addDatabase(APg::factory("postgres:///testdb"), "local");
}

void Database::qsqlQuery()
{
    QSqlQuery query(QSqlDatabase::database("local"));
    if (query.exec("SELECT now(), pg_sleep(5)")) {
        QJsonArray rows;
        while (query.next()) {
            QJsonObject obj = {
                {"now", query.value(0).toDateTime().toString()},
            };
            rows << obj;
        }
        Q_EMIT gotResult(rows);
    }
}

void Database::qsqlQueryThread()
{
    QMetaObject::invokeMethod(m_dbThread, "qsqlQueryThread", Qt::QueuedConnection);
}

void DatabaseThread::qsqlQueryThread()
{
    QSqlQuery query(QSqlDatabase::database("threaded"));
    if (query.exec("SELECT now(), pg_sleep(5)")) {
        QJsonArray rows;
        while (query.next()) {
            QJsonObject obj = {
                {"now", query.value(0).toDateTime().toString()},
            };
            rows << obj;
        }
        Q_EMIT gotResult(rows);
    }
}


void Database::asqlQuery()
{
    m_queryCanceler = new QObject;
    APool::database("local").exec(u"SELECT now(), pg_sleep(5)", [=] (AResult &result) {
        Q_EMIT gotResult(result.jsonArray());
    }, m_queryCanceler);
}

void Database::cancelAsqlQuery()
{
    delete m_queryCanceler;
    m_queryCanceler = nullptr;
}

void Database::migrate(int target)
{
    auto mig = new AMigrations(this);
    if (!mig->fromFile(":/database.sql")) {
        qWarning() << "failed to load migrations";
        return;
    }

    mig->load(APool::database("local"), "mig_test");
    connect(mig, &AMigrations::ready, this, [=] (bool error, const QString &errorString) {
        qDebug() << "migration ready" << error << errorString;
        if (!error) {
            mig->migrate(target, [=] (bool error, const QString &errorString) {
                QJsonArray ret = {
                    QJsonObject{
                        {"migration_error", error},
                        {"migration_str", errorString},
                    }
                };
                Q_EMIT gotResult(ret);
            });
        }
    });
}

void Database::countRows()
{
    APool::database("local").exec(u"SELECT count(*) FROM big_table", [=] (AResult &result) {
        QJsonArray ret;
        if (result.error()) {
            ret.append(QJsonObject{
                           {"error", result.errorString()}
                       });
        } else {
            for (const auto &row : result) {
                ret << row[0].toInt();
            }
        }
        Q_EMIT gotResult(ret);
    }, this);
}

#include "database.moc"
