/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

class Test : public QWidget
{
public:
    void paintEvent(QPaintEvent *) override
    {
        // Time to bring up your magnifying glass.
        QPainter p(this);

        // First, lets draw the guiding lines
        p.setPen(Qt::green);
        p.drawLine(QPoint(9,0), QPoint(9,115));
        p.drawLine(QPoint(30,0), QPoint(30,115));

        p.setBrush(Qt::black);
        p.setPen(Qt::black);

        // This is the baseline, where you can see the 20x20 pixels painted
        p.fillRect(QRectF(QPointF(10.0, 2.0), QSizeF(20.0, 20.0)), Qt::SolidPattern);

        // The border is painted half of the border size (which is 1 pixel) on each side
        // so from -0.5 to 0.5. and from 19.5 to 20.5.
        // This can clearly be seen when anitializing is enabled.
        p.setRenderHint(QPainter::Antialiasing);
        p.drawRect(QRectF(QPointF(10.0, 32.0), QSize(20.0, 20.0)));

        // HOWEVER! when anitializing is not enabled, we cannot paint half pixels,
        // so the border will be from 0 to 1 and from 20 to 21 (due to rounding up)
        // that is it will be one pixel wider than the size given
        p.setRenderHint(QPainter::Antialiasing, false);
        p.setBrush(Qt::red);
        p.drawRect(QRectF(QPointF(10.0, 62.0), QSizeF(20.0, 20.0)));

        // This is just to show that the painting can go well beyond the area
        // when painting with large pens.
        p.setRenderHint(QPainter::Antialiasing);
        QPen pen = p.pen();
        pen.setWidth( 5 );
        p.setPen( pen );
        p.drawRect(QRectF(QPointF(10.0, 92.0), QSizeF(20.0, 20.0)));
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Test test;
    test.resize(40, 115);
    test.show();
    return app.exec();
}
