/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef EVENTLOGWINDOW_H
#define EVENTLOGWINDOW_H

#include <QtWidgets>

class EventLogWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EventLogWindow(QWidget *parent = nullptr);

public slots:
    void logEvent(const QString &message, QEvent *event);

private:
    QTextEdit *m_edit;
};

#endif // EVENTLOGWINDOW_H
