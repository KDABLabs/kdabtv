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

#include <QAbstractItemView>
#include <QAction>
#include <QModelIndex>

namespace CustomContextMenu {
inline bool True(const QModelIndex &)
{
    return true;
}

inline bool isValidModelIndex(const QModelIndex &index)
{
    return index.isValid();
};

inline auto hasSelection(QAbstractItemView *view)
{
    return [view](const QModelIndex &) { return view->selectionModel()->hasSelection(); };
};

inline auto hasExactlyOneSelectedRow(QAbstractItemView *view)
{
    return
        [view](const QModelIndex &) { return view->selectionModel()->selectedRows().count() == 1; };
};

inline auto anyItemFromSelectionMatching = [](QAbstractItemView *view, auto fn) {
    return [view, fn](const QModelIndex &) {
        auto selection = view->selectionModel()->selectedRows();
        return std::any_of(selection.cbegin(), selection.cend(), fn);
    };
};

inline auto allItemFromSelectionMatching = [](QAbstractItemView *view, auto fn) {
    return [view, fn](const QModelIndex &) {
        auto selection = view->selectionModel()->selectedRows();
        return std::all_of(selection.cbegin(), selection.cend(), fn);
    };
};

inline auto onlyOneCellSelected(QAbstractItemView *view)
{
    return [view](const QModelIndex &) {
        return view->selectionModel()->selectedIndexes().count() == 1;
    };
}

// clazy:excludeall=copyable-polymorphic - Needed for version 2
class ActionBase
{
public:
    ActionBase() = default;
    virtual ~ActionBase() { }

    virtual QString title(const QModelIndex &index = QModelIndex()) const = 0;
    virtual bool isEnabled(const QModelIndex &) const { return true; }
    virtual bool isVisible(const QModelIndex &) const { return true; }
    virtual void activate(const QModelIndex &index) = 0;
    virtual QIcon icon() const { return {}; }
#if VERSION == 1
    Q_DISABLE_COPY(ActionBase)
#endif
};

class Action : public ActionBase
{
public:
    using PredicateFn = std::function<bool(const QModelIndex &)>;
    using ActionFn = std::function<void(const QModelIndex &)>;
    using TitleFn = std::function<QString(const QModelIndex &)>;

    Action(const QString &title = {}, const ActionFn & = {},
           const PredicateFn &isEnabledFn = CustomContextMenu::True,
           const PredicateFn &isVisibleFn = CustomContextMenu::True);
    Action(const TitleFn &titleFn, const ActionFn &,
           const PredicateFn &isEnabledFn = CustomContextMenu::True,
           const PredicateFn &isVisibleFn = CustomContextMenu::True);

    QString title(const QModelIndex &index = {}) const override;
    bool isEnabled(const QModelIndex &index) const override;
    void activate(const QModelIndex &index) override;
    bool isVisible(const QModelIndex &index) const override;
    QIcon icon() const override;

    void setTitle(const QString &title);
    void setTitleFN(const TitleFn &titleFn);
    void setAction(const ActionFn &actionFn);
    void setIsEnabledFN(const PredicateFn &isEnabledFn);
    void setIsVisibleFN(const PredicateFn &isVisibleFn);
    void setIcon(const QIcon &icon);
    void setMenu(const QString &menu);

private:
#if VERSION == 1
    Q_DISABLE_COPY(Action)
#endif
    TitleFn m_titleFn;
    PredicateFn m_enabledFn;
    ActionFn m_actionFn;
    PredicateFn m_isVisibleFn;
    QIcon m_icon;
    QString m_menu;
};
class QActionAction : public ActionBase
{
public:
    explicit QActionAction(QAction *action);

    QString title(const QModelIndex &index = QModelIndex()) const override;
    bool isEnabled(const QModelIndex &) const override;
    void activate(const QModelIndex &index) override;
    QIcon icon() const override;

private:
#if VERSION == 1
    Q_DISABLE_COPY(QActionAction)
#endif
    QAction *m_action = nullptr;
};

class Separator : public ActionBase
{
public:
    explicit Separator(const QString &path = {})
        : m_path(path)
    {
    }

    QString title(const QModelIndex &index = QModelIndex()) const override
    {
        return m_path.isEmpty() ? m_path : m_path + "/dummy";
    }
    void activate(const QModelIndex &index) override { Q_UNUSED(index); }

private:
    QString m_path;
#if VERSION == 1
    Q_DISABLE_COPY(Separator)
#endif
};
} // namespace CustomContextMenu
