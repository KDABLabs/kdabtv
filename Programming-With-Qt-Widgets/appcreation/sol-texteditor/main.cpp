/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "editor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app( argc, argv );
    Editor editor;
    editor.show();
    return app.exec();
}
