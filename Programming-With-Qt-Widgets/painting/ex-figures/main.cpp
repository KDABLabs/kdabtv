/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

class DrawingBoard : public QWidget
{
public:
    QSize sizeHint() const override {
        return QSize(640, 490);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.translate(20, 20);
        QPolygon points;
        points << QPoint(10, 10) << QPoint(30, 90) << QPoint(70, 90) << QPoint(90, 10);

        p.setRenderHint(QPainter::Antialiasing);
        p.setRenderHint(QPainter::TextAntialiasing);
        p.setRenderHint(QPainter::SmoothPixmapTransform);
        QFont font = p.font();
        font.setPixelSize(10);
        p.setFont(font);

        p.setPen(QPen(Qt::red, 2));
        p.setBrush(Qt::yellow);

        drawBox(&p);
        p.drawPoint(points[0]);
        drawTitle(&p, "drawPoint()");

        nextColumn(&p);
        drawBox(&p);
        p.drawLine(points[0], points[1]);
        drawTitle(&p, "drawLine()");

        nextColumn(&p);
        drawBox(&p);
        p.drawPolyline(points);
        drawTitle(&p, "drawPolyline()");

        nextColumn(&p);
        drawBox(&p);
        p.drawPoints(points);
        drawTitle(&p, "drawPoints()");

        nextColumn(&p);
        drawBox(&p);
        p.drawLines(points);
        drawTitle(&p, "drawLines()");

        nextColumn(&p);
        drawBox(&p);
        p.drawPolygon(points);
        drawTitle(&p, "drawPolygon()");

        nextRow(&p);
        drawBox(&p);
        p.drawRect(QRect(10, 10, 80, 80));
        drawTitle(&p, "drawRect()");

        nextColumn(&p);
        drawBox(&p);
        p.drawRoundedRect(QRect(10, 10, 80, 80), 8, 8);
        drawTitle(&p, "drawRoundedRect()");

        nextColumn(&p);
        drawBox(&p);
        p.drawEllipse(QRect(10, 20, 80, 60));
        drawTitle(&p, "drawEllipse()");

        nextColumn(&p);
        drawBox(&p);
        p.drawArc(QRect(10, 20, 80, 60), 16 * 45, 16 * 135);
        drawTitle(&p, "drawArc()");

        nextColumn(&p);
        drawBox(&p);
        p.drawChord(QRect(10, 20, 80, 60), 16 * 45, 16 *135);
        drawTitle(&p, "drawChord()");

        nextColumn(&p);
        drawBox(&p);
        p.drawPie(QRect(10, 20, 80, 60), 16 * 45, 16 * 135);
        drawTitle(&p, "drawPie()");

        nextRow(&p);
        drawBox(&p);
        p.drawRect(QRect(10, 20, 80, 60));
        p.drawText(QRect(10, 20, 80, 60), Qt::AlignCenter, "Qt");
        drawTitle(&p, "drawText()");

        nextColumn(&p);
        drawBox(&p);
        p.drawPixmap(QRect(10,10,80,80), QPixmap(":bg1.jpg"));
        drawTitle(&p, "drawPixmap()");

        nextColumn(&p);
        drawBox(&p);
        QPainterPath path;
        path.addEllipse(QRectF(10, 20, 80, 60));
        path.addRect(QRect(10, 10, 80, 80));
        p.drawPath(path);

        drawTitle(&p, "drawPath()");
    }

    void drawTitle(QPainter *p, const QString &text)
    {
        p->save();
        p->setPen(Qt::blue);
        p->drawText(QRect(0, 100, 100, 50), text, QTextOption(Qt::AlignCenter));
        p->restore();
    }

    void nextColumn(QPainter *p)
    {
        p->translate(100, 0);
    }

    void nextRow(QPainter *p)
    {
        p->translate(-p->transform().dx() + 20, 150);
    }

    void drawBox(QPainter *p)
    {
        p->save();
        p->setPen(Qt::blue);
        p->setBrush(Qt::NoBrush);
        p->drawRect(0, 0, 100, 100);
        p->restore();
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DrawingBoard board;
    board.show();
    return app.exec();
}
