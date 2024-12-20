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

//#define SHOW_PAINTERPATH

class Test : public QWidget
{
public:
    Test(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QFont fnt = font();
        fnt.setFamily("Liberation Serif");
        fnt.setPixelSize(100);
        setFont(fnt);
        const QFontMetrics fm(fontMetrics());
        auto size = fm.size(Qt::TextSingleLine, "Hello World");
#ifdef SHOW_PAINTERPATH
        size.setHeight(size.height() * 2);
#endif
        setMinimumSize(size);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        const QFontMetrics fm(painter.fontMetrics());
        const auto size = fm.size(Qt::TextSingleLine, "Hello World");
        QLinearGradient gradient(0, 0, size.width(), size.height());
        gradient.setColorAt(0, Qt::red);
        gradient.setColorAt(0.5, Qt::green);
        gradient.setColorAt(1, Qt::blue);
        QBrush b(gradient);
        QPen pen(b, 0);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawText(0, 100, "Hello World");

#ifdef SHOW_PAINTERPATH
        // What if we wanted a different color for the outline and for the fill?
        // QPainterPath can do that.
        QPainterPath path;
        path.addText(0, 200, painter.font(), "Hello World");
        painter.setPen(Qt::black);
        painter.setBrush(b); // try Qt::NoBrush for an outline effect
        painter.drawPath(path);
#endif
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Test test;
    test.show();

    return app.exec();
}
