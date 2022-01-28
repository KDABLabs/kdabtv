#include "shared.h"

int part2()
{
    auto x = [cached = false, value = 0]() mutable {
        if (!cached)
            value = calculate(42);
        cached = true;
        return value;
    };

    auto y = [cached = false, value = 0]() mutable {
        if (!cached)
            value = calculate(10);
        cached = true;
        return value;
    };

    int z = 0;

    if (cond1())
        z = x();
    else
        z = y();

    if (cond2())
        return z + x();
    else
        return z + y();
}
