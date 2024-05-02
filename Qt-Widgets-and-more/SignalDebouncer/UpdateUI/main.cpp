#include "Dashlet.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dashlet d;
#if 0
    d.setConfig({2020, "Teamlead", "Overtime"});
#endif
    d.show();
    return a.exec();
}
