/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(const QString &styleSheetText, bool noStyle, QWidget *parent = nullptr);
    ~MainDialog();

private:
    void start();
    void stop();
    void increaseProgress();
    void decreaseProgress();
    void activateStylesheet(bool dark);

private:
    Ui::MainDialog *ui;
    QTimer *m_timer;
    QString m_styleSheetText;
};

#endif // MAINDIALOG_H
