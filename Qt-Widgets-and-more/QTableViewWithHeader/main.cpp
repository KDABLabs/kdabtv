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

#include "DepecheModel.h"
#include "EnumConverters.h"
#include "TableViewWithHeader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TableViewWithHeader *view = new TableViewWithHeader;
    DepecheModel *model = new DepecheModel;
    // This is the syntax if using the overloaded operator->
    // (*view)->setModel(model);
    view->setModel(model);

    {
        TableViewWithHeader::HeaderSpanInfo info;
        info.firstColumn = +DepecheModel::Column::CD;
        info.lastColumn = +DepecheModel::Column::download;
        info.title = "Media Released On";
        info.color = Qt::green;
        view->addHeader(std::move(info));
    }

    {
        TableViewWithHeader::HeaderSpanInfo info;
        info.firstColumn = +DepecheModel::Column::UK;
        info.lastColumn = +DepecheModel::Column::US;
        info.title = "Peak Chart Position";
        info.color = QColor(Qt::blue).lighter(180);
        view->addHeader(std::move(info));
    }
    view->resize(1000, 600);
    view->show();

    return a.exec();
}
