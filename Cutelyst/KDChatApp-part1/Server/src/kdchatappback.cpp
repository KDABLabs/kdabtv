#include "kdchatappback.h"

#include "root.h"

#include <apool.h>
#include <apg.h>

using namespace Cutelyst;

KDChatAppBack::KDChatAppBack(QObject *parent) : Application(parent)
{
}

KDChatAppBack::~KDChatAppBack()
{
}

bool KDChatAppBack::init()
{
    new Root(this);

    return true;
}

bool KDChatAppBack::postFork()
{
    APool::create(APg::factory("postgres:///chat"));
    return true;
}
