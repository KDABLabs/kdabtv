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

#include "MoneyDelegate.h"
#include "../Money.h"
#include "../MoneyEditor.h"

QWidget *MoneyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & /*option*/,
                                     const QModelIndex & /*index*/) const
{
    return new MoneyEditor(parent);
}

void MoneyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    static_cast<MoneyEditor *>(editor)->setValue(index.data().value<Money>());
}

void MoneyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    model->setData(index, QVariant::fromValue(static_cast<MoneyEditor *>(editor)->value()));
}

void MoneyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                         const QModelIndex & /*index*/) const
{
    const int hCell = option.rect.height();
    const int hEditor = editor->sizeHint().height();
    const int h = qMax(hCell, hEditor);
    QSize size = option.rect.size();
    size.setHeight(h);
    editor->setGeometry(QRect(option.rect.topLeft() - QPoint(0, (h - hCell) / 2), size));
}
