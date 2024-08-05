#pragma once

#include <QString>
#include <QList>
#include <QMetaType>

struct Team {
    int id;
    QString name;
};

using Teams = QList<Team>;

// Only needed for Qt5, not Qt6
//Q_DECLARE_METATYPE(Team)
