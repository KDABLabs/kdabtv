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

#include <FileSelector.h>
#include <QApplication>
#include <QGridLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto top = new QWidget;
    auto layout = new QGridLayout(top);
    int row = -1;

    auto *checkLabel = new QLabel;

    auto addItem = [&](const QString &text, FileSelector::Mode mode) {
        layout->addWidget(new QLabel(text), ++row, 0);
        auto selector = new FileSelector(mode);
        layout->addWidget(selector, row, 1);
        QObject::connect(selector, &FileSelector::editingFinished, checkLabel,
                         [selector, checkLabel, text] {
                             checkLabel->setText(QString("%1: %2").arg(text, selector->text()));
                         });
    };

    addItem("Load a File", FileSelector::FileOpen);
    addItem("Save File", FileSelector::FileSave);
    addItem("Choose a Directory", FileSelector::Directory);

    layout->addWidget(new QLabel("File to load:"), ++row, 0);
    layout->addWidget(checkLabel, row, 1);

    top->resize(600, top->sizeHint().height());
    top->show();
    return QApplication::exec();
}
