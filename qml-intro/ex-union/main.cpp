/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <cstdio>

union Data
{
    int i;
    double d;
    char* name;
};

int main( int /*argc*/, char** /*argv*/)
{
    Data d;
    d.i = 10;
    printf("%d\n", d.i );
    printf("%g\n", d.d );

    d.d = 10;
    printf("%d\n", d.i );
    printf("%g\n", d.d );
}
