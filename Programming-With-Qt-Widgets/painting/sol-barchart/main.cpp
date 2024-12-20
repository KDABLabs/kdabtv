/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2011-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>
#include "barchart.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  auto chart = new BarChart();
  chart->setAttribute(Qt::WA_DeleteOnClose);
  chart->addBar("Germany", 80, Qt::green);
  chart->addBar("France",51, Qt::blue);
  chart->addBar("USA", 35, Qt::red);
  chart->addBar("Sweden", 25, Qt::yellow);

  chart->show();
  chart->resize( 500, 300 );

  return app.exec();
}
