#include "VariablesAndExpressions.h"

struct Data
{
};

Data *getData()
{
    return nullptr;
}

void VariablesAndExpressions::test()
{
    if (true)
        test2();

    if (Data *data = getData()) {
        // DO something with data
    }

    bool x, y;
    if (!x && !y)
        test2();

    if (x || y)
        test2();

    int a = 10, b = 20;
    if ((a < b) || (a > b))
        test2();
}

void VariablesAndExpressions::test2() { }
