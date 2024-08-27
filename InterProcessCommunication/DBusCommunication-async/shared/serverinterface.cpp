#include "serverinterface.h"

const char *ServerInterface::serverName()
{
    return "com.kdab.PeopleServer";
}

const char *ServerInterface::objectPath()
{
    return "/PeopleServer";
}
