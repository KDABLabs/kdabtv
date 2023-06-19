#pragma once

#include <QToolButton>

class QMenu;

class BurgerButton : public QToolButton
{
    Q_OBJECT
public:
    explicit BurgerButton(QWidget *parent = nullptr);
    static BurgerButton *addButtonToCorner(QWidget *parent, const QPoint &offset = QPoint(0, 0));

private:
    void populateMenu();
    void showHelp();
};
