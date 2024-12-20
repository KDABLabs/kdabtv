/*************************************************************************
 *
 * Copyright (c) 2011-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

class CustomWidget : public QWidget {
Q_OBJECT

public:
    CustomWidget( QWidget* parent = nullptr )
        :QWidget( parent )
    {
        auto timer = new QTimer( this );
        connect( timer, &QTimer::timeout, this, &CustomWidget::advance );
        timer->start( 2000 );
        m_pixmap = QPixmap(":/background.png");
        setFixedSize( m_pixmap.size() );
    }

protected slots:
    void advance()
    {
        m_step = (m_step + 1) % 10;
        update();
    }

protected:
    void paintEvent( QPaintEvent* ) override
    {
        // draw backGround;
        QPainter painter( this );
        painter.drawPixmap( 0, 0, m_pixmap );

        // Draw Text
        // Defines Yellow color with transparency!!
        QColor textColor = Qt::yellow;
        textColor.setAlpha( 256*m_step/10 );
        painter.setPen( textColor );
        QFont f = painter.font();
        f.setPixelSize( 130 );
        painter.setFont( f );

        painter.drawText( 10, 150, "Transparent" );

        // Draw Boxes
        QColor boxColor = Qt::yellow;
        for ( int i = 0; i < 10; ++i ) {
            boxColor.setAlpha( 256*i/10 );
            painter.setPen( i == m_step ? Qt::red : boxColor );
            painter.setBrush( boxColor );
            painter.drawRect( (i%5)*110 +150, 300 + (110 * (i/5)), 100, 100 );
        }
    }

private:
    int m_step = 0;
    QPixmap m_pixmap;
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    CustomWidget win;
    win.show();
    return app.exec();
}

#include "main.moc"
