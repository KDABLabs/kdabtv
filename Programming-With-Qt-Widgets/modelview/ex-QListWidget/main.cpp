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

// Simple ListMode without icons
void showListWithoutIcons()
{
    auto w = new QListWidget;
    w->setAttribute(Qt::WA_DeleteOnClose);
    for (int i = 1; i < 10; ++i)
        w->addItem(QString("Item %1").arg(i));

    auto item = new QListWidgetItem("Extra item");
    w->addItem(item);
    w->show();
}

// ListMode with Icons
void showListWithIcons()
{
    auto w = new QListWidget;
    w->setAttribute(Qt::WA_DeleteOnClose);
    for (int i = 1; i < 10; ++i) {
        auto item = new QListWidgetItem(QString("Item %1").arg(i), w);
        item->setIcon(QPixmap(QString(":images/%1.png").arg(i)));
    }
    w->show();
}

// IconMode
void showListInIconMode()
{
    auto w = new QListWidget;
    w->setAttribute(Qt::WA_DeleteOnClose);
    for (int i = 1; i < 10; ++i) {
        auto item = new QListWidgetItem(QString("Item %1").arg(i), w);
        item->setIcon(QPixmap(QString(":images/%1.png").arg(i)));
    }
    w->setViewMode(QListView::IconMode);
    w->setGridSize(QSize(50, 50));
    w->setMovement(QListView::Snap);
    w->show();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    showListWithoutIcons();
    showListWithIcons();
    showListInIconMode();

    return app.exec();
}
