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
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Close Event [*]"));

    QTimer::singleShot(3000, [this] { setWindowModified(true); });

    auto label = new QLabel(tr("Try to close the window."));
    auto layout = new QVBoxLayout;
    layout->addWidget(label, 0, Qt::AlignCenter);
    setLayout(layout);
}

void Widget::closeEvent(QCloseEvent *event)
{
    if (windowShouldClose())
        event->accept();
    else
        event->ignore();
}

bool Widget::windowShouldClose()
{
    if (!isWindowModified())
        return true;

    QMessageBox::StandardButton answer =
        QMessageBox::question(
            this,
            tr("Close Window"),
            tr("Really close the window?"),
            QMessageBox::Yes | QMessageBox::No
        );

    return (answer == QMessageBox::Yes);
}
