#pragma once
#include <QDebug>
namespace {
int calculate(int i)
{
    qDebug() << "OK calculating...." << i;
    return i;
}

bool cond1()
{
    return true;
}
bool cond2()
{
    return true;
}
}
