/*************************************************************************
 *
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>
#include "gizmo.h"

int main( int argc, char ** argv ) {
    QApplication a( argc, argv );

    auto gizmo1 = new Gizmo( Qt::blue, Qt::green, Qt::Horizontal );
    auto gizmo2 = new Gizmo( Qt::yellow, Qt::black, Qt::Vertical );
    auto gizmo3 = new Gizmo( Qt::white, Qt::green, Qt::Horizontal );

    auto top = new QWidget;
    top->setAttribute(Qt::WA_DeleteOnClose);
    auto layout = new QVBoxLayout( top );
    layout->addWidget( gizmo1 );
    layout->addWidget( gizmo2 );
    layout->addWidget( gizmo3 );

    top->show();
    return a.exec();
}
