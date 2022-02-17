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
#include <QAction>
#include <QFileDialog>
#include <QImage>
#include <QPainter>
#include <QResizeEvent>
#include <QToolButton>
#include <QValidator>

namespace {

class ModeValidator : public QValidator
{
    Q_OBJECT
public:
    explicit ModeValidator(FileSelector *selector, QObject *parent)
        : QValidator(parent)
        , m_selector(selector)
    {
    }

    State validate(QString &input, int & /*pos*/) const override
    {
        if (input.isEmpty())
            return Acceptable;
        switch (m_selector->mode()) {
        case FileSelector::Directory:
            return QFileInfo(input).isDir() ? Acceptable : Intermediate;
        case FileSelector::FileOpen:
            return QFileInfo(input).isFile() ? Acceptable : Intermediate;
        case FileSelector::FileSave:
            if (QFileInfo(input).isWritable())
                return Acceptable;
            if (QFileInfo(QFileInfo(input).absoluteDir().absolutePath()).isWritable())
                return Acceptable;
            return Intermediate;
        }
        Q_UNREACHABLE();
    }

private:
    FileSelector *m_selector = nullptr;
};
}

FileSelector::FileSelector(QWidget *parent)
    : FileSelector(FileSave, parent)
{
}

FileSelector::FileSelector(Mode mode, QWidget *parent)
    : QLineEdit(parent)
    , m_validator(new ModeValidator(this, this))
{
    m_action = new QAction(this);
    m_action->setIcon(QPixmap(":icons/folder.svg"));
    addAction(m_action, QLineEdit::TrailingPosition);
    setMode(mode);
    setValidator(m_validator);
    connect(m_action, &QAction::triggered, this, &FileSelector::chooseFile);
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
        QString name = fileName;
        int pos = 0;
        if (m_validator->validate(name, pos) == QValidator::Acceptable)
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

#include "FileSelector.moc"
