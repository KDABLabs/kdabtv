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

#include "CustomContextMenuAction.h"
namespace CustomContextMenu {

Action::Action(const QString &title, const Action::ActionFn &actionFn,
               const Action::PredicateFn &isEnabledFn, const PredicateFn &isVisibleFn)
    : m_titleFn([title](const QModelIndex &) { return title; })
    , m_enabledFn(isEnabledFn)
    , m_actionFn(actionFn)
    , m_isVisibleFn(isVisibleFn)
{
}

Action::Action(const Action::TitleFn &titleFn, const Action::ActionFn &actionFn,
               const Action::PredicateFn &isEnabledFn, const Action::PredicateFn &isVisibleFn)
    : m_titleFn(titleFn)
    , m_enabledFn(isEnabledFn)
    , m_actionFn(actionFn)
    , m_isVisibleFn(isVisibleFn)
{
}

QString Action::title(const QModelIndex &index) const
{
    return m_titleFn(index);
}

bool Action::isEnabled(const QModelIndex &index) const
{
    return m_enabledFn(index);
}

void Action::activate(const QModelIndex &index)
{
    m_actionFn(index);
}

bool Action::isVisible(const QModelIndex &index) const
{
    return m_isVisibleFn(index);
}

QIcon Action::icon() const
{
    return m_icon;
}

void Action::setTitle(const QString &title)
{
    m_titleFn = [title](const QModelIndex &) { return title; };
}

void Action::setTitleFN(const TitleFn &titleFn)
{
    m_titleFn = titleFn;
}

void Action::setAction(const ActionFn &actionFn)
{
    m_actionFn = actionFn;
}

void Action::setIsEnabledFN(const PredicateFn &isEnabledFn)
{
    m_enabledFn = isEnabledFn;
}

void Action::setIsVisibleFN(const PredicateFn &isVisibleFn)
{
    m_isVisibleFn = isVisibleFn;
}

void Action::setIcon(const QIcon &icon)
{
    m_icon = icon;
}

void Action::setMenu(const QString &menu)
{
    m_menu = menu;
}

QActionAction::QActionAction(QAction *action)
    : m_action(action)
{
}

QString QActionAction::title(const QModelIndex &) const
{
    if (m_action->shortcut().isEmpty())
        return m_action->text();
    else
        return QString("%1 (%2)").arg(m_action->text()).arg(m_action->shortcut().toString());
}

bool QActionAction::isEnabled(const QModelIndex &) const
{
    return m_action->isEnabled();
}

void QActionAction::activate(const QModelIndex &)
{
    m_action->trigger();
}

QIcon QActionAction::icon() const
{
    return m_action->icon();
}

} // namespace CustomContextMenu
