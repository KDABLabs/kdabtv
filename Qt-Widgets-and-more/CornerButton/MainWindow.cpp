#include "MainWindow.h"
#include "BurgerButton.h"
#include "ui_MainWindow.h"

#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto button = BurgerButton::addButtonToCorner(this);
    auto action = new QAction("About KDAB", this);
    connect(action, &QAction::triggered, [] { QDesktopServices::openUrl(QUrl("kdab.com")); });
    button->addAction(action);

    action = new QAction("Help", this);
    connect(action, &QAction::triggered, [] {
        QDesktopServices::openUrl(
            QUrl("https://www.youtube.com/playlist?list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI"));
    });
    button->addAction(action);
}

MainWindow::~MainWindow()
{
    delete ui;
}
