/* MIT License

Copyright (C) 2025 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include <QApplication>
#include <QListView>
#include <QRangeModel>
#include <QTableView>
#include <QKeyEvent>

void simpleList();
void simpleTable();
void tableWithHeaders();
void Struct();
void gadgets();
void editable();
void listRoles();
void tableRoles();
void trees();
void normalTableModel();
void treesOfGadgets();

class QuitHandler : public QObject {
public:
    QuitHandler() {
        qApp->installEventFilter(this);
    }

    bool eventFilter(QObject *watched, QEvent *event) override {
        if (event->type() == QEvent::KeyRelease) {
            auto keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Q && keyEvent->modifiers() == Qt::ControlModifier) {
                qApp->quit();
            }
        }
        return QObject::eventFilter(watched, event);
    }
};
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QuitHandler dummy;

    // normalTableModel();
    simpleList();
    simpleTable();
    tableWithHeaders();
    Struct();
    gadgets();
    editable();
    listRoles();
    tableRoles();
    trees();
    treesOfGadgets();

    app.exec();

    return 0;
}
