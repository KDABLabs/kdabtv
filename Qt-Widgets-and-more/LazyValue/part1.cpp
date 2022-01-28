#include "shared.h"

int part1()
{
    int x = calculate(42);
    int y = calculate(10);

    int z = 0;

    if (cond1())
        z = x;
    else
        z = y;

    if (cond2())
        return z + x;
    else
        return z + y;
}
