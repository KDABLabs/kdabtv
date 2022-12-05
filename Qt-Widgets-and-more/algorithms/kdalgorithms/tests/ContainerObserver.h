#pragma once
#include <vector>

template <typename T>
struct ContainerObserver : public std::vector<int>
{
    ContainerObserver() { ++copies; }
    static void reset() { copies = 0; }
    static int copies;
};

template <typename T>
int ContainerObserver<T>::copies = 0;
