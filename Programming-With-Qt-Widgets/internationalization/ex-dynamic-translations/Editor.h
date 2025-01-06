/*************************************************************************
 *
 * Copyright (c) 2024, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#pragma once

#include <QMainWindow>

namespace Ui {
class Editor;
}

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

protected:
    void changeEvent(QEvent *event) override;

signals:
    void languageChangeRequested(const QString &locale);

private:
    void openFile();
    void saveFile();
    void quit();
    void about();
    void aboutQt();
    void translateMenu();

    Ui::Editor *ui;
    QActionGroup* m_group;
};
