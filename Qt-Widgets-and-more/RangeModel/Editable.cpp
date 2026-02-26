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

#include <QPushButton>
#include <QRangeModel>
#include <QTableView>
#include <QVBoxLayout>

namespace {
class EditableTables : public QWidget
{
public:
    EditableTables()
    {
        auto layout = new QVBoxLayout(this);
        auto showData = new QPushButton("Show data");
        layout->addWidget(showData);

        auto doEvil = new QPushButton("Modify people directly");
        layout->addWidget(doEvil);

        auto doItCorrectly = new QPushButton("Modify people via QAIM API");
        layout->addWidget(doItCorrectly);

        auto view1 = new QTableView;
        layout->addWidget(view1);

        auto view2 = new QTableView;
        layout->addWidget(view2);

        model = new QRangeModel(std::ref(people));
        view1->setModel(model);
        view2->setModel(model);

        connect(showData, &QPushButton::clicked, this, [this]() { qDebug() << people; });

        connect(doEvil, &QPushButton::clicked, this, [this]() { people.prepend({"Santa", 500}); });

        connect(doItCorrectly, &QPushButton::clicked, this, [this]() {
            model->insertRows(0, 1);
            model->setData(model->index(0, 0), "Santa's Wife");
            model->setData(model->index(0, 1), "400");
        });
    }

private:
    QList<QPair<QString, int>> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};
    QRangeModel *model = nullptr;
};
}

void editable()
{
    auto view = new EditableTables;
    view->show();
}
