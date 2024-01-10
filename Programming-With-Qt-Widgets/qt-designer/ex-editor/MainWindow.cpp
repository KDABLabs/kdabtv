#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "SearchDialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->edit->setPlainText("Hello class");
  connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
  connect(ui->actionSearch, &QAction::triggered, this, &MainWindow::search);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::save() {
  auto text = ui->edit->toPlainText();
  qDebug() << "Saving" << text;
}

void MainWindow::search() {
  SearchDialog dialog;
  dialog.exec();
}
