/*************************************************************************
 *
 * Copyright (c) 2010, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QPushButton button("Hello world");
  button.show();

  return app.exec();
}
