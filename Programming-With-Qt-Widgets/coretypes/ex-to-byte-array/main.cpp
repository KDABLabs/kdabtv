/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QString>
#include <iostream>

void someApi(const char *charArray)
{
    std::cout << charArray << std::endl;
}

int main()
{
    QString foo("Foo");
    const char *charArray = foo.toLatin1().constData();
    foo = "Bah";
    someApi(charArray);
    return 0;
}
