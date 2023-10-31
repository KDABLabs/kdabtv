/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "eventlogwindow.h"

EventLogWindow::EventLogWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Event Logger");

    m_edit = new QTextEdit;
    m_edit->setFontFamily("Courier");
    m_edit->setReadOnly(true);

    auto clear = new QPushButton("Clear");
    connect(clear, &QAbstractButton::clicked, m_edit, &QTextEdit::clear);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_edit);
    layout->addWidget(clear);
}

void EventLogWindow::logEvent(const QString &message, QEvent *event)
{
    QString out;
    QDebug(&out) << message.leftJustified(24, '.') << event;
    m_edit->append(out);
}
