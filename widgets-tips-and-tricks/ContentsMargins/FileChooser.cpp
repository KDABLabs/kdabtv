/* MIT License

Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "FileChooser.h"
#include <QFileDialog>
#include <QLayout>
#include <QLineEdit>
#include <QToolButton>

FileChooser::FileChooser(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QHBoxLayout(this);
    // This is the line that makes all the difference
    layout->setContentsMargins(0, 0, 0, 0);

    m_lineEdit = new QLineEdit(this);
    layout->addWidget(m_lineEdit);

    connect(m_lineEdit, &QLineEdit::textChanged, this, &FileChooser::pathChanged);

    auto *button = new QToolButton;
    button->setText("...");
    layout->addWidget(button);

    connect(button, &QToolButton::clicked, this, &FileChooser::chooseFile);

    setFocusProxy(m_lineEdit);
}

void FileChooser::setMode(Mode mode)
{
    m_mode = mode;
}

FileChooser::Mode FileChooser::mode() const
{
    return m_mode;
}

void FileChooser::setPath(const QString &fileName)
{
    m_lineEdit->setText(fileName);
}

QString FileChooser::path() const
{
    return m_lineEdit->text();
}

void FileChooser::chooseFile()
{
    QString fileName;
    switch (m_mode) {
    case FileOpen:
        fileName = QFileDialog::getOpenFileName(this, QString(), m_lineEdit->text());
        break;
    case FileSave:
        fileName = QFileDialog::getSaveFileName(this, QString(), m_lineEdit->text());
        break;
    case Directory:
        fileName = QFileDialog::getExistingDirectory(this, QString(), m_lineEdit->text());
        break;
    }

    if (!fileName.isEmpty())
        m_lineEdit->setText(fileName);
}
