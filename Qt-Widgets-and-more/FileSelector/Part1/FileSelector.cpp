/* MIT License

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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
#include <QImage>
#include <QPainter>
#include <QResizeEvent>
#include <QToolButton>

namespace FileSelectorHelper {
class SimpleButton : public QToolButton
{
    Q_OBJECT

public:
    explicit SimpleButton(QWidget *parent)
        : QToolButton(parent)
    {
        setCursor(Qt::ArrowCursor);
    }

protected:
    void paintEvent(QPaintEvent * /*event*/) override
    {
        QPainter painter(this);
        int size = height() - 4;
        painter.drawImage(2, 2,
                          QImage(":icons/folder.svg")
                              .scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
};
}

using namespace FileSelectorHelper;

FileSelector::FileSelector(Mode mode, QWidget *parent)
    : QLineEdit(parent)
{
    m_button = new SimpleButton(this);
    m_button->hide();
    setMode(mode);
    connect(m_button, &SimpleButton::clicked, this, &FileSelector::chooseFile);
}

void FileSelector::resizeEvent(QResizeEvent *event)
{
    const int size = event->size().height();
    m_button->resize(size, size);
    m_button->move(event->size().width() - size, 0);
    auto margins = textMargins();
    margins.setRight(size);
    setTextMargins(margins);

    QLineEdit::resizeEvent(event);
}

void FileSelector::chooseFile()
{
    const QString fileName = [this] {
        switch (mode()) {
        case FileOpen:
            return QFileDialog::getOpenFileName(this, QString(), text());
        case FileSave:
            return QFileDialog::getSaveFileName(this, QString(), text());
        case Directory:
            return QFileDialog::getExistingDirectory(this, QString(), text());
        }
        Q_UNREACHABLE();
    }();

    if (!fileName.isEmpty()) {
        setText(fileName);
        emit editingFinished();
    }
}

void FileSelector::setMode(Mode mode)
{
    const QString text = [mode] {
        switch (mode) {
        case Mode::FileOpen:
            return "Choose file to open";
        case Mode::FileSave:
            return "Choose file to save to";
        case Mode::Directory:
            return "Choose Directory";
        }
        Q_UNREACHABLE();
    }();
    setPlaceholderText(text);

    if (mode != m_mode) {
        m_mode = mode;
        emit modeChanged(mode);
    }
}

FileSelector::Mode FileSelector::mode() const
{
    return m_mode;
}

void FileSelector::focusInEvent(QFocusEvent *event)
{
    m_button->show();
    QLineEdit::focusInEvent(event);
}

void FileSelector::focusOutEvent(QFocusEvent *event)
{
    m_button->hide();
    QLineEdit::focusOutEvent(event);
}

#include "FileSelector.moc"
