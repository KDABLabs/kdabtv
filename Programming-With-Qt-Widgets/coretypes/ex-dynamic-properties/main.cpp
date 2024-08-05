#include "TeamSelector.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Teams teams = TeamSelector().getTeams();
    for (const auto& team : teams) {
        qDebug("%d %s", team.id, qPrintable(team.name));
    }
    return a.exec();
}
