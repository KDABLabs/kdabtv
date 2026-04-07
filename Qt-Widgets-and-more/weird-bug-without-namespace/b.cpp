#include "b.h"

#include <cstdio>

class SomeClass
{
public:
    void f() {
        printf("From b.cpp\n");
    }
};

void b()
{
    SomeClass obj;
    obj.f();
}


