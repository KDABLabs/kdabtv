#include "copy_observer.h"

int CopyObserver::copies = 0;
int CopyObserver::moves = 0;

CopyObserver::CopyObserver(int value)
    : value(value)
{
}

CopyObserver::CopyObserver(const CopyObserver &other)
{
    value = other.value;
    ++copies;
}

CopyObserver::CopyObserver(CopyObserver &&other) noexcept
{
    value = other.value;
    ++moves;
}

CopyObserver &CopyObserver::operator=(const CopyObserver &other)
{
    value = other.value;
    ++copies;
    return *this;
}

bool operator<(const CopyObserver &x, const CopyObserver &y)
{
    return x.value < y.value;
}

void CopyObserver::reset()
{
    copies = 0;
    moves = 0;
}

CopyObserver &CopyObserver::operator=(CopyObserver &&other) noexcept
{
    value = other.value;
    ++moves;
    return *this;
}

bool operator==(const CopyObserver &x, const CopyObserver &y)
{
    return x.value == y.value;
}
