#ifndef ROOT_H
#define ROOT_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class FirebaseAdminMessaging;
class Root : public Controller
{
    Q_OBJECT
    C_NAMESPACE("")
public:
    explicit Root(QObject *parent = nullptr);
    ~Root();

    C_ATTR(users, :Local :AutoArgs :ActionClass(REST))
    void users(Context *c) {};

    C_ATTR(users_POST, :Private)
    void users_POST(Context *c);

    C_ATTR(users_PUT, :Private)
    void users_PUT(Context *c);

    C_ATTR(messages, :Local :AutoArgs :ActionClass(REST))
    void messages(Context *c) {};

    C_ATTR(messages_POST, :Private)
    void messages_POST(Context *c);


    C_ATTR(websocket, :Path('ws') :AutoArgs)
    void websocket(Context *c, const QString &id);

    QHash<int, Context *> m_wsClients;

    bool postFork(Application *app) override;

    void sendPushNotifications(const QString &message);
    void sendPushNotification(const QString &deviceToken, const QString &message);


    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c);

    C_ATTR(defaultPage, :Path)
    void defaultPage(Context *c);

private:
    C_ATTR(End, :ActionClass("RenderView"))
    void End(Context *c) { Q_UNUSED(c); }

    FirebaseAdminMessaging *m_fbAdminMsg;
};

#endif //ROOT_H

