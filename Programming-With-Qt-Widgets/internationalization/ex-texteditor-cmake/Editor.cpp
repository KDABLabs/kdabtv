/*************************************************************************
 *
 * Copyright (c) 2024, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "Editor.h"
#include "ui_Editor.h"
#include <QFileDialog>
#include <QMessageBox>

Editor::Editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Editor)
{
    ui->setupUi(this);

    connect(ui->action_Open, &QAction::triggered, this, &Editor::openFile);
    connect(ui->action_Save, &QAction::triggered, this, &Editor::saveFile);
    connect(ui->action_Quit, &QAction::triggered, this, &Editor::quit);
    connect(ui->actionAbout, &QAction::triggered, this, &Editor::about);
    connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

Editor::~Editor()
{
    delete ui;
}

void Editor::openFile()
{
    const QString fileName = QFileDialog::getOpenFileName(this);

    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Failed to open file"),
                              tr("Couldn't open the file. The error was:") + f.errorString());
        return;
    }

    QTextStream stream(&f);
    ui->textEdit->setPlainText(stream.readAll());

    statusBar()->showMessage("File Loaded", 2000);
}

void Editor::saveFile()
{
    const QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return;

    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Failed to save file",
                              "Couldn't save the file. The error was: " + f.errorString());
        return;
    }

    QTextStream stream(&f);
    stream << ui->textEdit->toPlainText();
}

void Editor::quit()
{
    qApp->quit();
}

void Editor::about()
{
    QMessageBox::about(this, "About Text Editor", "Super wiz-bang text editor");
}

void Editor::aboutQt()
{
    QMessageBox::aboutQt(this);
}
