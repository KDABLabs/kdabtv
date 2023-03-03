/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#include "maindialog.h"
#include "colorrepository.h"
#include "ui_maindialog.h"

#include <QDebug>
#include <QShortcut>
#include <QTextStream>
#include <QTimer>

MainDialog::MainDialog(const QString &styleSheetText, bool noStyle, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
    , m_timer(new QTimer(this))
    , m_styleSheetText(styleSheetText)
{
    m_timer->setInterval(50);

    // QSS: Because QDialogButtonBox can't adjust to changes of properties dynamically, this needs to be done
    // before creating the child widgets...
    if (!styleSheetText.isEmpty()) {
        activateStylesheet(true /*dark*/);
    }

    ui->setupUi(this);

    if (noStyle) {
        ui->labelToggleSwitch->hide();
        ui->toggleSwitch->hide();
        ui->disabledToggleSwitch->hide();
        ui->labelDisabledToggleSwitch->hide();
    }

    connect(ui->darkModeCheckBox, &QCheckBox::clicked, this, [](bool checked) { ColorRepository::setDarkMode(checked); });
    if (!styleSheetText.isEmpty()) {
        ui->label->setText(tr("This application uses a QSS stylesheet to style widgets"));
        connect(ui->darkModeCheckBox, &QCheckBox::clicked, this, [this](bool checked) { activateStylesheet(checked); });
    }

    connect(ui->startButton, &QPushButton::clicked, this, &MainDialog::start);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainDialog::stop);
    connect(m_timer, &QTimer::timeout, this, &MainDialog::increaseProgress);

    auto *plusShortcut = new QShortcut(Qt::Key_Plus, this);
    connect(plusShortcut, &QShortcut::activated, this, &MainDialog::increaseProgress);
    auto *minusShortcut = new QShortcut(Qt::Key_Minus, this);
    connect(minusShortcut, &QShortcut::activated, this, &MainDialog::decreaseProgress);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::start()
{
    m_timer->start();
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void MainDialog::stop()
{
    m_timer->stop();
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

void MainDialog::increaseProgress()
{
    const int value = (ui->progressBar->value() + 1) % 101;
    ui->progressBar->setValue(value);
}

void MainDialog::decreaseProgress()
{
    const int value = (ui->progressBar->value() + 100) % 101;
    ui->progressBar->setValue(value);
}

void MainDialog::activateStylesheet(bool dark)
{
    QStringList lines = m_styleSheetText.split('\n');
    const auto removeLine = [dark](const QString &line) {
        if (line.contains("[DARK]"))
            return !dark;
        else if (line.contains("[LIGHT]"))
            return dark;
        return false;
    };
    lines.erase(std::remove_if(lines.begin(), lines.end(), removeLine), lines.end());
    // qDebug() << lines;
    qApp->setStyleSheet(lines.join('\n'));
}
