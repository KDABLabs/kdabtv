/*************************************************************************
 *
 * Copyright (c) 2024, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/
#pragma once

#include <QWidget>
#include <memory>

namespace Ui {
class Editor;
}

class Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

private:
    void load();
    void save();

    std::unique_ptr<Ui::Editor> ui;
};

