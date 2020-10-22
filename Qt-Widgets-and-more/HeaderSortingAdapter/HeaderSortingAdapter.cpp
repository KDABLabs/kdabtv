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

#include "HeaderSortingAdapter.h"
#include <QApplication>
#include <QEvent>
#include <QHeaderView>
#include <QMouseEvent>
#include <QTableView>

HeaderSortingAdapter::HeaderSortingAdapter(QTableView *table)
    : QObject(table)
    , m_table(table)
{
    QHeaderView *headerView = table->horizontalHeader();

    headerView->setSortIndicator(-1, Qt::AscendingOrder);
    headerView->setSortIndicatorShown(false);
    headerView->viewport()->installEventFilter(this);
}

bool HeaderSortingAdapter::eventFilter(QObject * /*watched*/, QEvent *event)
{
    auto mouseEvent = [event] { return static_cast<QMouseEvent *>(event); };
    auto headerView = [this] { return m_table->horizontalHeader(); };

    switch (event->type()) {
    case QEvent::MouseButtonPress:
        if (mouseEvent()->button() != Qt::LeftButton)
            return false;
        m_pressPos = mouseEvent()->pos();
        break;

    case QEvent::MouseMove:
        if (mouseEvent()->buttons().testFlag(Qt::LeftButton)
            && (m_pressPos - mouseEvent()->pos()).manhattanLength() > qApp->startDragDistance()) {
            m_isMoving = headerView()->sectionsMovable();
        }
        break;

    case QEvent::MouseButtonRelease: {
        if (mouseEvent()->button() != Qt::LeftButton)
            return false;

        // If we were dragging a section, then pass the event on.
        if (m_isMoving) {
            m_isMoving = false;
            return false;
        }

        auto header = headerView();
        const int indexAtCursor = header->logicalIndexAt(mouseEvent()->pos());

        if (indexAtCursor == -1)
            ; // Do nothing, we clicked outside the headers
        else if (header->sortIndicatorSection() != indexAtCursor) {
            header->setSortIndicator(indexAtCursor, Qt::AscendingOrder);
            header->setSortIndicatorShown(true);
        } else if (header->sortIndicatorOrder() == Qt::AscendingOrder) {
            header->setSortIndicator(indexAtCursor, Qt::DescendingOrder);
        } else {
            header->setSortIndicator(-1, Qt::AscendingOrder);
            header->setSortIndicatorShown(false);
        }
        emit header->sectionClicked(indexAtCursor);
        return true;
    }
    default:
        break;
    }
    return false;
}
