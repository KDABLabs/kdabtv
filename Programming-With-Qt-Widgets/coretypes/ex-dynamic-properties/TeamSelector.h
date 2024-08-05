#pragma once

#include <QDialog>
#include "Team.h"
class TeamSelector : public QDialog
{
    Q_OBJECT
public:
    Teams getTeams();
};

