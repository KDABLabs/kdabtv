/*************************************************************************
 *
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef SIMPLEWINDOW_H
#define SIMPLEWINDOW_H

#include <QWidget>

class SimpleWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SimpleWindow(QWidget *parent = nullptr);

};

#endif // SIMPLEWINDOW_H
