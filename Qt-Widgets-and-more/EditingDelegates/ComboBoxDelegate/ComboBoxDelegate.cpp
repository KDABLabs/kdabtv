/* MIT License

Copyright (C) 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "ComboBoxDelegate.h"
#include <QComboBox>

namespace {
// Support templates for variants - See the example in
// https://en.cppreference.com/w/cpp/utility/variant/visit
// ------------------------------------------------->
template <class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
// <// -------------------------------------------------
} // End of namespace

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

ComboBoxDelegate::ComboBoxDelegate(const QStringList &values, QObject *parent)
    : QStyledItemDelegate(parent)
    , m_data(values)
{
}

ComboBoxDelegate::ComboBoxDelegate(const ItemFactory &factory, QObject *parent)
    : QStyledItemDelegate(parent)
    , m_data(factory)
{
}

void ComboBoxDelegate::setEditable(bool b)
{
    m_isEditable = b;
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & /*option*/,
                                        const QModelIndex & /*index*/) const
{
    auto *comboBox = new QComboBox(parent);
    comboBox->setEditable(m_isEditable);
    comboBox->addItems(items());
    if (m_isEditable) {
        // Ensure that we finish editing as soon as an item is selected in an editable combobox
        // The alternative is that it only emit done editing when we move focus out.
        // This is in contrast to read only combo boxes, whuch does it as soon as an item is
        // selected.
        for (auto child : comboBox->children()) {
            // clazy:excludeall=old-style-connect
            if (qstrcmp(child->metaObject()->className(), "QComboBoxPrivateContainer") == 0)
                connect(child, SIGNAL(itemSelected(QModelIndex)), this, SLOT(doneEditing()));
        }
    } else
        connect(comboBox, qOverload<int>(&QComboBox::activated), this,
                &ComboBoxDelegate::doneEditing);
    m_comboBox = comboBox;
    return comboBox;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    static_cast<QComboBox *>(editor)->setCurrentText(index.data().toString());
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    model->setData(index, static_cast<QComboBox *>(editor)->currentText());
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                            const QModelIndex & /*index*/) const
{
    const int hCell = option.rect.height();
    const int hEditor = editor->sizeHint().height();
    const int h = qMax(hCell, hEditor);
    QSize size = option.rect.size();
    size.setHeight(h);
    editor->setGeometry(QRect(option.rect.topLeft() - QPoint(0, (h - hCell) / 2), size));
}

QStringList ComboBoxDelegate::items() const
{
    return std::visit(overloaded{[](const QStringList &list) { return list; },
                                 [](const ItemFactory &factory) { return factory(); }},
                      m_data);
}

void ComboBoxDelegate::doneEditing()
{
    emit commitData(m_comboBox);
    emit closeEditor(m_comboBox);
}
