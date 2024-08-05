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
#include <QDir>
#include <QFile>
#include <QFileDialog>

#define USE_TEXT_STREAM 0

Editor::Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
    connect(ui->load, &QPushButton::clicked, this, &Editor::load);
    connect(ui->save, &QPushButton::clicked, this, &Editor::save);
}

Editor::~Editor() = default;

void Editor::load()
{
    auto fileName = QFileDialog::getOpenFileName(this, "File to load");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Couldn't load the file.";
        return;
    }
#if USE_TEXT_STREAM
    QTextStream stream(&file);
    // Force UTF-32 encoding
    stream.setEncoding(QStringConverter::Utf32);
    const QString str = stream.readAll();
#else
    const QString str = QString::fromUtf8(file.readAll());
#endif
    ui->edit->setPlainText(str);
}

void Editor::save()
{
    auto fileName = QFileDialog::getSaveFileName(this, "File to load");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Couldn't save the file.";
        return;
    }

    const QString text = ui->edit->toPlainText();
#if USE_TEXT_STREAM
    QTextStream stream(&file);
    // Force UTF-32 encoding
    stream.setEncoding(QStringConverter::Utf32);
    stream << text;
#else
    file.write(text.toUtf8());
#endif
}
