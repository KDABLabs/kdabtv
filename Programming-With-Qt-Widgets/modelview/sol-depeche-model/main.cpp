#include "DepecheModel.h"
#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView view;
    DepecheModel model;
    view.setModel(&model);

    view.resize(800, 600);
    view.show();
    return a.exec();
}
