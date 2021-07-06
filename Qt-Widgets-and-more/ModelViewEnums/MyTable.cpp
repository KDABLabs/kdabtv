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
#include "MyTable.h"
#include "EnumConverters.h"
#include "MyModel.h"

#include <QMessageBox>

MyTable::MyTable(QWidget *parent)
    : QTableView(parent)
{
    connect(this, &QTableView::doubleClicked, this, &MyTable::printDaysToBirthday);
}

void MyTable::printDaysToBirthday(const QModelIndex &index)
{
    const auto name = index.data(+MyModel::Role::Name).toString();
    const auto birthday = index.data(+MyModel::Role::Birthday).toDate();
    const auto today = QDate::currentDate();
    const auto thisYearsBirthday = QDate(today.year(), birthday.month(), birthday.day());

    const int delta = today.daysTo(thisYearsBirthday);

    const QString message = (delta > 0)
        ? QString("%1 days till %2's birthday").arg(delta).arg(name)
        : QString("Sorry, %1 already had his birthday this year, you are late!").arg(name);
    QMessageBox::information(this, "Birthday Information", message);
}
