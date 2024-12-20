/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2011-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

class QAction;
class QLabel;
class TextEdit;

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);

protected slots:
    void slotFileOpen();
    void slotFileSave();
    void slotFilePrint();
    void slotQuit();

    void slotAbout();
    void slotAboutQt();

    void slotTextChanged();
    void slotCursorPositionChanged();

protected:
    void closeEvent(QCloseEvent *) override;

private:
    QAction   *m_fileSave;
    QAction   *m_filePrint;
    TextEdit  *m_edit;
    QLabel    *m_fileLabel;
    QLabel    *m_modifiedLabel;
    QLabel    *m_cursorPosLabel;

    QString    m_fileName;
};

#endif // EDITOR_H
