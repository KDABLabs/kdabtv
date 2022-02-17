#ifndef KDCHATAPPBACK_H
#define KDCHATAPPBACK_H

#include <Cutelyst/Application>

using namespace Cutelyst;

class KDChatAppBack : public Application
{
    Q_OBJECT
    CUTELYST_APPLICATION(IID "KDChatAppBack")
public:
    Q_INVOKABLE explicit KDChatAppBack(QObject *parent = nullptr);
    ~KDChatAppBack();

    bool init() final;

    bool postFork() final;
};

#endif //KDCHATAPPBACK_H

