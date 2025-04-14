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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    struct Player
    {
        QString name;
        QString role;
        QString goals;
    };

    QHash<int, Player> players;
    players[2] = {"Bob", "Defender", "1"};
    players[3] = {"Patrick", "Defender", "0"};
    players[4] = {"Susan", "Midfielder", "3"};
    players[5] = {"Felipe", "Midfielder", "5"};
    players[6] = {"Donna", "Striker", "6"};

    auto tree = new QTreeWidget;

    QStringList headerTexts{"Name", "Role", "Goals"};
    tree->setHeaderLabels(headerTexts);

    auto teamItem = new QTreeWidgetItem(tree);
    teamItem->setText(0, "Qt FC");
    teamItem->setText(2, "19");

    // Creating a child item with a parent item.
    auto player1 = new QTreeWidgetItem(teamItem);
    player1->setText(0, "James");
    player1->setText(1, "Goalkeeper");
    player1->setText(2, "0");
    player1->setIcon(1, QPixmap(":images/1.png"));

    for (int i = 2; i <= 6; ++i) {
        auto player = new QTreeWidgetItem;
        player->setText(0, players[i].name);
        player->setText(1, players[i].role);
        player->setText(2, players[i].goals);
        player->setIcon(1, QPixmap(QString(":images/%1.png").arg(i)));
        teamItem->addChild(player);
    }

    // Adding child items later.
    auto player7 = new QTreeWidgetItem();
    player7->setText(0, "Bernie");
    player7->setText(1, "Striker");
    player7->setText(2, "4");
    player7->setIcon(1, QPixmap(":images/7.png"));
    teamItem->addChild(player7);

    tree->setWindowTitle("Tree Child Items");
    tree->show();
    return app.exec();
}
