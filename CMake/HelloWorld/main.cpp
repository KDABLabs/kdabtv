#include "mainwindow.h"
#include "object.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    My obj;
    return a.exec();
}
