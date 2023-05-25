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

#include "CustomContextMenuAdapter.h"
#include "CustomContextMenuAction.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QModelIndex>
#include <QTableView>
#include <QTreeView>

namespace CustomContextMenu {

template <typename View>
void Adapter<View>::addActionsToMenu(QMenu *menu, const QModelIndex &index) const
{
    QHash<QString, QMenu *> menus;

    for (auto &action : m_actions) {
        if (action->isVisible(index)) {
            QMenu *destMenu = menu;

            QStringList subMenuNames = action->title(index).split("/");
            const QString title = subMenuNames.last();
            subMenuNames.removeLast();
            QString currentPath;

            for (const QString &subMenuName : qAsConst(subMenuNames)) {
                currentPath += "/" + subMenuName;
                auto currentMenu = destMenu;
                destMenu = menus.value(currentPath);
                if (!destMenu) {
                    destMenu = currentMenu->addMenu(subMenuName);
                    menus.insert(currentPath, destMenu);
                }
            }

            if (dynamic_cast<CustomContextMenu::Separator *>(action.get())) {
                destMenu->addSeparator();
            } else {
                QAction *menuAction = destMenu->addAction(title);
                menuAction->setEnabled(action->isEnabled(index));
                menuAction->setIcon(action->icon());

                QObject::connect(menuAction, &QAction::triggered, this,
                                 [index, &action] { action->activate(index); });
            }
        }
    }
}

template <typename View>
void Adapter<View>::contextMenuEvent(QContextMenuEvent *event)
{
    const QModelIndex index = View::indexAt(event->pos());
    QMenu menu(this);

    addActionsToMenu(&menu, index);

    menu.exec(QCursor::pos());
}
} // namespace CustomContextMenu

// clazy:excludeall=missing-qobject-macro
template class CustomContextMenu::Adapter<QTreeView>;
template class CustomContextMenu::Adapter<QTableView>;
