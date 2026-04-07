#include "a.h"

#include <cstdio>

class SomeClass
{
public:
    inline void f() {
        printf("From a.cpp\n");
    }
};

void a()
{
    SomeClass obj;
    obj.f();
}


