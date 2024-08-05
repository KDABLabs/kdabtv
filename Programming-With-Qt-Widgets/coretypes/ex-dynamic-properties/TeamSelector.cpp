#include "TeamSelector.h"
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVariant>

Teams TeamSelector::getTeams()
{
    Teams teams{{1,"Initrode"}, {2, "Initech"}, {3, "RoyalBlue"}};

    QList<QCheckBox*> checkBoxes;
    auto layout = new QVBoxLayout(this);
    for (const auto& team: teams) {
        auto cb = new QCheckBox(team.name);
        layout->addWidget(cb);
        cb->setProperty("TEAM", QVariant::fromValue(team));
        checkBoxes.append(cb);
    }

    auto button = new QPushButton("Go!");
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, &QDialog::accept);
    exec();

    Teams result;
    for (auto cb : checkBoxes) {
        if (cb->isChecked())
            result.append(cb->property("TEAM").value<Team>());
    }
    return result;
}
