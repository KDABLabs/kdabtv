#include "root.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>

#include <apool.h>
#include <aresult.h>

#include <firebaseadmin.h>
#include <firebaseadminmessaging.h>
#include <firebaseadminreply.h>

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
            sendPushNotifications(msg);
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

    auto fbApp = new FirebaseAdmin(this);
    fbApp->setAccountCredentialData(R"V0G0N(
<REPLACE WITH SERVICE ACCOUNT JSON>
)V0G0N");

    fbApp->getAccessToken();
    m_fbAdminMsg = new FirebaseAdminMessaging(fbApp);
    m_fbAdminMsg->setApiKey("<REPLACE WITH SERVER API KEY>");

    return true;
}

void Root::sendPushNotifications(const QString &message)
{
    QStringList users;
    QRegularExpression re("@([a-zA-Z0-9_]{3,})");
    auto globalMatch = re.globalMatch(message);
    while (globalMatch.hasNext()) {
        QRegularExpressionMatch match = globalMatch.next();
        users << match.captured(1);
    }
    users.removeDuplicates();

    for (const auto &user : qAsConst(users)) {
        APool::database().exec(u"SELECT data->>'firebase_token' FROM users WHERE nick=$1",
                               {
                                   user,
                               }, [=] (AResult &result) {
            if (!result.error()) {
                auto firstRow = result.begin();
                if (firstRow != result.end() && !firstRow[0].toString().isEmpty()) {
                    sendPushNotification(firstRow[0].toString(), message);
                }
            } else {
                qWarning() << "Failed to get firebase_token for user" << user << result.errorString();
            }
        }, this);
    }
}

void Root::sendPushNotification(const QString &deviceToken, const QString &message)
{
    FirebaseMessage msg;
    msg.setToken(deviceToken);
    QString title = "ChatApp - New Message";
    msg.setNotification(title, message);
    FirebaseAndroidNotification android;
    android.setTitle(title);
    android.setBody(message);
    msg.setAndroid(android);
    FirebaseAdminReply *reply = m_fbAdminMsg->send(msg);
    connect(reply, &FirebaseAdminReply::finished, this, [=] {
        reply->deleteLater();
        if (reply->error()) {
            qDebug() << "FIREBASE error" << reply->errorCode() << reply->errorMessage();
        } else {
            qDebug() << "FIREBASE success" << reply->messageId();
        }
    });
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
