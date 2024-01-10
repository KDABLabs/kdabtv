/* MIT License

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company,
info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "FileSelector.h"
#include <QFileDialog>
#include <QLayout>
#include <QLineEdit>
#include <QToolButton>

FileSelector::FileSelector(QWidget *parent) : QWidget(parent) {
  auto *layout = new QHBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  m_lineEdit = new QLineEdit(this);
  layout->addWidget(m_lineEdit);

  connect(m_lineEdit, &QLineEdit::editingFinished, this,
          &FileSelector::emitPathChanged);

  auto *button = new QToolButton(this);
  button->setText("...");
  layout->addWidget(button);

  connect(button, &QToolButton::clicked, this, &FileSelector::chooseFile);

  setFocusProxy(m_lineEdit);
}

void FileSelector::setMode(int mode) {
  if (mode != m_mode) {
    m_mode = (Mode)mode;
    emit modeChanged((Mode)mode);
  }
}

FileSelector::Mode FileSelector::mode() const { return m_mode; }

void FileSelector::setPath(const QString &fileName) {
  m_lineEdit->setText(fileName);
  m_lastEmittedPath = fileName;
}

QString FileSelector::path() const { return m_lineEdit->text(); }

void FileSelector::chooseFile() {
  QString fileName;
  if (mode() == FileOpen)
    fileName =
        QFileDialog::getOpenFileName(this, QString(), m_lineEdit->text());
  else if (mode() == FileSave)
    fileName =
        QFileDialog::getSaveFileName(this, QString(), m_lineEdit->text());
  else
    fileName =
        QFileDialog::getExistingDirectory(this, QString(), m_lineEdit->text());

  if (!fileName.isEmpty()) {
    m_lineEdit->setText(fileName);
    emitPathChanged();
  }
}

void FileSelector::emitPathChanged() {
  QString newPath = m_lineEdit->text();
  if (newPath != m_lastEmittedPath) {
    m_lastEmittedPath = newPath;
    emit pathChanged(newPath);
  }
}
