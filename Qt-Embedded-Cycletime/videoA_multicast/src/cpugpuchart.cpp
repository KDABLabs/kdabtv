#include "cpugpuchart.h"
#include <QPainter>
#include <QTimer>

CpuGpuchart::CpuGpuchart(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(1000);
    m_updateTimer->start();
    connect(m_updateTimer, &QTimer::timeout, this, [this](){
        QFile gpuInfoFile;
        gpuInfoFile.setFileName("/tmp/gpuinfo");
        gpuInfoFile.open(QFile::ReadOnly);

        const auto wholefile = gpuInfoFile.readAll();
        if(wholefile.isEmpty()) return;
        auto lines = wholefile.split('\n');
        lines.removeLast();
        const auto firstline = lines.first();
        const auto lastline = lines.last();

        const auto headerInfo = firstline.simplified().split(' ');
        const auto dataInfo = lastline.simplified().split(' ');

        m_gpuinfo.clear();
        for(int i=0; i< headerInfo.size(); i++) {
            m_gpuinfo.insert(headerInfo[i],dataInfo[i]);
        }

        qDebug() << "Christoph" << m_gpuinfo;
        update();
    });

}


void CpuGpuchart::paint(QPainter *painter)
{
    if(isVisible())
    {
        const QRectF origBoundingRect = painter->clipBoundingRect();

        auto pen = painter->pen();
        pen.setColor(Qt::white);
        painter->setPen(pen);
        painter->drawRect(10,10,width()-20, height()-20);

        auto pos = 0;
        for (auto [key, value]: asKeyValueRange(m_gpuinfo)) {
            painter->drawText(QPoint(10, pos), key);
            painter->drawText(QPoint(50, pos), value);

            pos = pos + 50;
        }
    }
}
