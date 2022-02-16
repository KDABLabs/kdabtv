#include "root.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>

#include <apool.h>
#include <aresult.h>

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent)
{
}

Root::~Root()
{
}

void Root::users_POST(Context *c)
{
    const QJsonObject data = c->request()->bodyJsonObject();
    ASync a(c);
    APool::database().exec(u"INSERT INTO users (nick, data) VALUES ($1, $2) RETURNING id",
                           {
                               data[u"nick"],
                               data,
                           }, [a, c] (AResult &result) {
        auto firstRow = result.begin();
        if (!result.error() && firstRow != result.end()) {
            // RETURN the new user ID
            c->res()->setJsonObjectBody({
                                            {"id", firstRow[0].toInt()},
                                        });
        } else {
            qWarning() << "Failed to create user" << result.errorString();
            c->res()->setStatus(Response::InternalServerError);
            c->res()->setJsonObjectBody({
                                            {"error_msg", "failed to create user"},
                                        });
        }
    }, c);
}

void Root::users_PUT(Context *c)
{
    const QJsonObject data = c->request()->bodyJsonObject();
    ASync a(c);
    APool::database().exec(u"UPDATE users SET nick=$1, data=$2 WHERE id=$3",
                           {
                               data[u"nick"],
                               data,
                               data[u"user_id"],
                           }, [a, c, data] (AResult &result) {
        if (!result.error() && result.numRowsAffected()) {
            c->res()->setJsonObjectBody({
                                            {"id", data[u"user_id"]},
                                        });
        } else {
            qWarning() << "Failed to create user" << result.errorString();
            c->res()->setStatus(Response::InternalServerError);
            c->res()->setJsonObjectBody({
                                            {"error_msg", "failed to create user"},
                                        });
        }
    }, c);
}

void Root::messages_POST(Context *c)
{
    const QJsonObject data = c->request()->bodyJsonObject();
    const QString msg = data[u"msg"].toString();
    ASync a(c);
    APool::database().exec(u"INSERT INTO messages (user_id, msg) VALUES ($1, $2) RETURNING id",
                           {
                               data[u"user_id"],
                               msg,
                           }, [a, c, this, msg] (AResult &result) {
        auto firstRow = result.begin();
        if (!result.error() && firstRow != result.end()) {
            // RETURN the new message ID
            c->res()->setJsonObjectBody({
                                            {"id", firstRow[0].toInt()},
                                        });
        } else {
            qWarning() << "Failed to create message" << result.errorString();
            c->res()->setStatus(Response::InternalServerError);
            c->res()->setJsonObjectBody({
                                            {"error_msg", "failed to create message"},
                                        });
        }
    }, c);
}

void Root::websocket(Context *c, const QString &user_id)
{
    if (!c->response()->webSocketHandshake()) {
        c->response()->webSocketClose(Response::CloseCodeNormal, "internal-server-error");
        return;
    }

    if (m_wsClients.contains(user_id.toInt())) {
        c->response()->webSocketClose(Response::CloseCodeNormal, "already-logged-in");
        return;
    }
    m_wsClients.insert(user_id.toInt(), c);

    connect(c, &Context::destroyed, this, [=] {
        m_wsClients.remove(user_id.toInt());
    });

    APool::database().exec(uR"V0G0N(
SELECT m.id, m.created_at, u.nick, m.msg
FROM messages m
INNER JOIN users u ON m.user_id=u.id
ORDER BY 2 DESC
)V0G0N",
                  [c] (AResult &result) {
        if (result.error()) {
            c->response()->webSocketClose(Response::CloseCodeNormal, "error-getting-msgs");
        } else {
            c->response()->webSocketTextMessage(QJsonDocument(result.jsonArray()).toJson());
        }
    }, c);
}

bool Root::postFork(Application *app)
{
    auto db = APool::database();
    auto subscribe = [=] () mutable {
        db.subscribeToNotification("new_message", [=] (const ADatabaseNotification &notification) {
            for (const auto &ws : qAsConst(m_wsClients)) {
                ws->response()->webSocketTextMessage(notification.payload.toString());
            }
        }, this);
    };

    db.onStateChanged([=] (ADatabase::State state, const QString &msg) mutable {
        if (state == ADatabase::State::Disconnected) {
            qCritical() << "DB connection closed, disconnecting clients";
            for (const auto &ws : qAsConst(m_wsClients)) {
                ws->response()->webSocketClose(Response::CloseCodeNormal, "db-disconnected");
            }
        } else if (state == ADatabase::State::Connected) {
            subscribe();
        }
    });

    return true;
}

void Root::index(Context *c)
{
    c->response()->body() = "Welcome to Cutelyst!";
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}
