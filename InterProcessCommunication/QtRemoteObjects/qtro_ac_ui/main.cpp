#include "widget.h"

#include <QApplication>
#include <QRemoteObjectNode>

using namespace Qt::StringLiterals;

int main(
    int argc, char *argv[])
{
    QApplication a(argc, argv);

    QRemoteObjectNode node;
    if (!node.connectToNode(QUrl{u"local:replica"_s})) {
        qWarning("Could not connect to device!");
        return -1;
    }
    Widget w{node.acquire<SensorsReplica>()};
    w.show();
    return a.exec();
}
