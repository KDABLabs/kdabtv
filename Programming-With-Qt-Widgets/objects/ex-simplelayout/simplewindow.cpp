/*************************************************************************
 *
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "simplewindow.h"

#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

SimpleWindow::SimpleWindow(QWidget *parent) :
    QWidget(parent)
{
    auto noteLabel = new QLabel("Note:", this);
    auto noteEdit = new QTextEdit(this);
    auto clearButton = new QPushButton("Clear", this);
    auto saveButton = new QPushButton("Save", this);

    // outer horizontal-layout
    auto outer = new QVBoxLayout;
    outer->addWidget(noteLabel);
    outer->addWidget(noteEdit);
    {
        // nested inner layout
        auto inner = new QHBoxLayout;
        inner->addWidget(clearButton);
        inner->addWidget(saveButton);
        outer->addLayout(inner);
    }
    this->setLayout(outer);
}
