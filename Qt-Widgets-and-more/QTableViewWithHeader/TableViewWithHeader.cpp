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

#include "TableViewWithHeader.h"
#include <QHeaderView>
#include <QLabel>
#include <QPalette>
#include <QScrollBar>
#include <QVBoxLayout>

TableViewWithHeader::TableViewWithHeader(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_headerArea = new QWidget;
    layout->addWidget(m_headerArea);

    m_tableView = new QTableView;
    layout->addWidget(m_tableView);

    connect(m_tableView->horizontalHeader(), &QHeaderView::sectionResized, this,
            &TableViewWithHeader::doLayoutTitles);
    connect(m_tableView->horizontalScrollBar(), &QScrollBar::valueChanged, this,
            &TableViewWithHeader::doLayoutTitles);
}

void TableViewWithHeader::addHeader(HeaderSpanInfo info)
{
    auto label = new QLabel(info.title, m_headerArea);

    label->setAutoFillBackground(true);
    QPalette pal;
    pal.setBrush(QPalette::Window, info.color);
    label->setPalette(pal);

    QFont font = label->font();
    font.setPointSize(font.pointSize() * 1.5);
    label->setFont(font);

    label->setAlignment(Qt::AlignCenter);

    info.label = label;
    m_headerSpanInfo.append(std::move(info));
    doLayoutTitles();
}

/* I forgot to talk about this in the recording - but it really isn't that good an idea after all,
   as this syntax doesn't work:

   auto table = new TableViewWithHeader;
   table->setModel(...)

   instead I need to write
   (*table)->setModel(...)
*/

QTableView *TableViewWithHeader::operator->() const
{
    return m_tableView;
}

void TableViewWithHeader::setModel(QAbstractItemModel *model)
{
    m_tableView->setModel(model);
}

void TableViewWithHeader::doLayoutTitles()
{
    auto *header = m_tableView->horizontalHeader();
    const int offset =
        m_tableView->viewport()->x() - 1; // one pixel offset due to border, see gammaray

    int height = 0;
    for (const HeaderSpanInfo &info : qAsConst(m_headerSpanInfo)) {
        height = std::max(height, info.label->sizeHint().height());
    }

    for (const HeaderSpanInfo &info : qAsConst(m_headerSpanInfo)) {
        const int start = header->sectionViewportPosition(info.firstColumn);
        const int end =
            header->sectionViewportPosition(info.lastColumn) + header->sectionSize(info.lastColumn);

        info.label->move(start + offset, 0);
        info.label->resize(end - start, height);
    }
    m_headerArea->setFixedHeight(height);
}
