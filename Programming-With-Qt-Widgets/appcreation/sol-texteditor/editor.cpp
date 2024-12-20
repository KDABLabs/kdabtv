/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2011-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "editor.h"

#include "textedit.h"

#include <QtWidgets>

Editor::Editor(QWidget *parent) : QMainWindow(parent) {
  // -------------------------------------------------- Actions

  // Open
  auto fileOpenAction = new QAction(this);
  fileOpenAction->setText("&Open");
  fileOpenAction->setToolTip("Open a file for editing");
  fileOpenAction->setIcon(QIcon(QPixmap(":/fileopen.png")));
  connect(fileOpenAction, &QAction::triggered, this, &Editor::slotFileOpen);

  // Save
  m_fileSave = new QAction(this);
  m_fileSave->setText("&Save");
  m_fileSave->setToolTip("Save current file");
  m_fileSave->setIcon(QIcon(QPixmap(":/filesave.png")));
  connect(m_fileSave, &QAction::triggered, this, &Editor::slotFileSave);

  // Print
  m_filePrint = new QAction(this);
  m_filePrint->setText("&Print");
  m_filePrint->setToolTip("Print current file");
  m_filePrint->setIcon(QIcon(QPixmap(":/fileprint.png")));
  connect(m_filePrint, &QAction::triggered, this, &Editor::slotFilePrint);

  // Quit
  auto quitAction = new QAction(this);
  quitAction->setText("&Quit");
  quitAction->setToolTip("Quit the text editor");
  connect(quitAction, &QAction::triggered, this, &Editor::slotQuit);

  // About
  auto aboutAction = new QAction(this);
  aboutAction->setText("About");
  aboutAction->setToolTip("About this application");
  connect(aboutAction, &QAction::triggered, this, &Editor::slotAbout);

  // About Qt
  auto aboutQtAction = new QAction(this);
  aboutQtAction->setText("About Qt");
  aboutQtAction->setToolTip("About the Qt framework");
  connect(aboutQtAction, &QAction::triggered, this, &Editor::slotAboutQt);

  // -------------------------------------------------- Menubar
  auto fileMenu = new QMenu("&File", menuBar());
  menuBar()->addMenu(fileMenu);

  fileMenu->addAction(fileOpenAction);
  fileMenu->addAction(m_fileSave);
  fileMenu->addAction(m_filePrint);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAction);

  auto helpMenu = new QMenu("&Help", menuBar());
  menuBar()->addMenu(helpMenu);

  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);

  // -------------------------------------------------- Toolbar
  auto toolbar = new QToolBar("Main Toolbar", this);
  addToolBar(toolbar);

  toolbar->addAction(fileOpenAction);
  toolbar->addAction(m_fileSave);
  toolbar->addAction(m_filePrint);

  // -------------------------------------------------- Statusbar, Editor
  m_fileLabel = new QLabel("Unsaved", statusBar());
  statusBar()->addPermanentWidget(m_fileLabel, 0);

  m_modifiedLabel = new QLabel(statusBar());
  m_modifiedLabel->setPixmap(QPixmap(":/filesave.png").scaled(16, 16));
  statusBar()->addPermanentWidget(m_modifiedLabel);

  m_cursorPosLabel = new QLabel(statusBar());
  statusBar()->addPermanentWidget(m_cursorPosLabel);

  // Set application icon
  setWindowIcon(QPixmap(":/editor.png"));

  // The editor widget:
  m_edit = new TextEdit(this);
  m_edit->setFocus();
  m_edit->setWordWrapMode(QTextOption::WordWrap);
  m_edit->document()->setModified(false);
  setCentralWidget(m_edit);

  connect(m_edit->document(), &QTextDocument::contentsChanged, this,
          &Editor::slotTextChanged);
  connect(m_edit, &QTextEdit::cursorPositionChanged, this,
          &Editor::slotCursorPositionChanged);
  slotTextChanged();
  slotCursorPositionChanged();
}

void Editor::closeEvent(QCloseEvent *event) {
  if (m_edit->document()->isModified()) {
    QMessageBox::StandardButton r = QMessageBox::warning(
        this, "Save before quit", "The document is not saved",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
        QMessageBox::Cancel);
    switch (r) {
    case QMessageBox::Save:
      slotFileSave();
      break;
    case QMessageBox::Cancel:
      event->setAccepted(false); // same as event->ignore();
      break;
    default: // QMessageBox::Discard
      break;
    }
  }
}

void Editor::slotFileOpen() {
  m_fileName = QFileDialog::getOpenFileName(this);
  if (!m_edit->load(m_fileName)) {
    return;
  }

  m_fileLabel->setText(
      m_fileName.mid(m_fileName.lastIndexOf(QDir::separator()) + 1));
  m_edit->document()->setModified(false);
  slotTextChanged();
}

void Editor::slotFileSave() {
  QString candidate = QFileDialog::getSaveFileName(this, QString(), m_fileName);
  if (!candidate.isEmpty()) {
    if (!m_edit->save(candidate)) {
      return;
    }
    m_fileName = candidate;
    m_edit->document()->setModified(false);
    m_fileLabel->setText(
        m_fileName.mid(m_fileName.lastIndexOf(QDir::separator()) + 1));
    slotTextChanged();
  } else {
    // Cancel, do nothing
  }
}

void Editor::slotFilePrint() { qDebug() << "Printing is not implemented yet"; }

void Editor::slotQuit() { close(); }

void Editor::slotAbout() {
  QMessageBox::about(this, "About Text Editor", "Super wiz-bang text editor");
}

void Editor::slotAboutQt() { QMessageBox::aboutQt(this); }

void Editor::slotTextChanged() {
  bool modified = m_edit->document()->isModified();
  bool hasContent = !m_edit->document()->isEmpty();
  m_fileSave->setEnabled(modified);
  m_filePrint->setEnabled(hasContent);
  m_modifiedLabel->setVisible(modified);
}

void Editor::slotCursorPositionChanged() {
  const QTextCursor cursor = m_edit->textCursor();
  const int line = cursor.blockNumber() + 1;
  const int column = cursor.columnNumber() + 1;

  m_cursorPosLabel->setText(
      QString("Line: %1, Column: %2").arg(line).arg(column));
}
