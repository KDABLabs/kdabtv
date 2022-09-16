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

#pragma once

#include <QComboBox>
#include <QStyledItemDelegate>
#include <functional>
#include <variant>

// Delegate class for entry with a ComboBox
// Observe this class doesn't work with persistent editors (See
// QAbstractItemView::openPersistentEditor), as it keeps the editor as a state variable, and
// therefore would break if there were several editors visible at a time.
class ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using ItemFactory = std::function<QStringList()>;

    ComboBoxDelegate(QObject *parent = nullptr);
    ComboBoxDelegate(const QStringList &values, QObject *parent = nullptr);
    ComboBoxDelegate(const ItemFactory &factory, QObject *parent = nullptr);

    void setEditable(bool b = true);

    // QStyledItemDelegate API
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

protected:
    virtual QStringList items() const;

private slots:
    void doneEditing(); // We need this as a slot as we connect via macros

private:
    mutable QComboBox *m_comboBox = nullptr;

    std::variant<QStringList, ItemFactory> m_data;
    bool m_isEditable = false;
};
