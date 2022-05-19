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

#include "Demo.h"
#include "ReverseRowsProxyModel.h"
#include "ui_Demo.h"
#include <QDebug>
#include <QStandardItemModel>

Demo::Demo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Demo)
{
    ui->setupUi(this);
    ui->table->setSortingEnabled(true);

    m_proxy = new ReverseRowsProxyModel;
    setNewModel();
    ui->table->setModel(m_proxy);

    connect(ui->addRow, &QPushButton::clicked, this, &Demo::addRow);
    connect(ui->addColumn, &QPushButton::clicked, this, &Demo::addColumn);
    connect(ui->removeRow, &QPushButton::clicked, this, &Demo::removeRow);
    connect(ui->removeColumn, &QPushButton::clicked, this, &Demo::removeColumn);
    connect(ui->resort, &QPushButton::clicked, this, &Demo::resort);
    connect(ui->updateRandom, &QPushButton::clicked, this, &Demo::updateRandom);
    connect(ui->setNewModel, &QPushButton::clicked, this, &Demo::setNewModel);
}

Demo::~Demo() = default;
void Demo::addRow()
{
    auto row = currentIndex().row();
    QList<QStandardItem *> list;
    for (int i = 0; i < m_model->columnCount(); ++i)
        list.append(new QStandardItem(QString::number(std::rand() % 100)));
    m_model->insertRow(row, list);
}

void Demo::addColumn()
{
    auto column = currentIndex().column();
    QList<QStandardItem *> list;
    for (int i = 0; i < m_model->rowCount(); ++i)
        list.append(new QStandardItem(QString::number(std::rand() % 100)));
    m_model->insertColumn(column, list);
}

void Demo::removeRow()
{
    m_model->removeRow(currentIndex().row(), {});
}

void Demo::removeColumn()
{
    m_model->removeColumn(currentIndex().column(), {});
}

void Demo::resort()
{
    QModelIndex index = m_proxy->index(0, 0);
    QPersistentModelIndex persistentIndex(index);

    qDebug() << "===== BEFORE =====";
    qDebug() << "index: " << index << index.data();
    qDebug() << "Persistent index" << persistentIndex << persistentIndex.data();

    static bool ascending = true;
    ascending = !ascending;
    m_model->sort(1, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);

    qDebug() << "===== AFTER =====";
    qDebug() << "index: " << index << index.data();
    qDebug() << "Persistent index" << persistentIndex << persistentIndex.data();
}

void Demo::updateRandom()
{
    const int row = std::rand() % m_model->rowCount();
    const int column = std::rand() % m_model->columnCount();
    m_model->setData(m_model->index(row, column), std::rand() % 100);
}

void Demo::setNewModel()
{
    constexpr int rows = 10;
    constexpr int columns = 5;
    m_model = new QStandardItemModel(rows, columns);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            m_model->setItem(row, col, new QStandardItem(QString("(%1,%2)").arg(row).arg(col)));
        }
    }

    m_proxy->setSourceModel(m_model);
}

QModelIndex Demo::currentIndex() const
{
    return m_proxy->mapToSource(ui->table->currentIndex());
}
