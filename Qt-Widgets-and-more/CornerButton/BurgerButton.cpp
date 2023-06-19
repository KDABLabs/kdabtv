#include "BurgerButton.h"
#include "CornerLayout.h"
#include <QDesktopServices>
#include <QEvent>
#include <QFileInfo>
#include <QMenu>
#include <QResizeEvent>
#include <QShortcut>

BurgerButton::BurgerButton(QWidget *parent)
    : QToolButton(parent)
{
    setIcon(QPixmap(":/burger-menu.png"));
    setPopupMode(QToolButton::InstantPopup);
    setStyleSheet("QToolButton::menu-indicator { image: none; }");
}

BurgerButton *BurgerButton::addButtonToCorner(QWidget *parent, const QPoint &offset)
{
    auto button = new BurgerButton;
    button->show();
    button->resize(button->minimumSizeHint());

    auto layout = new CornerLayout(parent);
    layout->addWidget(button, Qt::TopRightCorner, offset);

    return button;
}

#include "moc_BurgerButton.cpp"
