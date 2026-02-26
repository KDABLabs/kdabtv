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

#include <QRangeModel>
#include <QTableView>

struct Book
{
    Q_GADGET
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(double price MEMBER price)

public:
    QString title;
    int price;
};

void gadgets()
{
    QList<Book> books{{"Why Perl is a better programming language than C++", -10},
                      {"20 Ways to make AI do your work", 20},
                      {"The printed copy of Wikipidia", 1234567}};
    auto model = new QRangeModel(books);
    auto view = new QTableView;
    view->setModel(model);
    view->show();
}

#include "Gadgets.moc"
