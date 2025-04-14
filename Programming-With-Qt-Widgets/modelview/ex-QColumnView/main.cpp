/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    auto view = new QColumnView;
    view->setAttribute(Qt::WA_DeleteOnClose);
    auto model = new QFileSystemModel(view);
    model->setRootPath( QDir::root().path() );
    view->setModel( model );
    view->resize( 800, 600 );
    view->show();

    return app.exec();
}
