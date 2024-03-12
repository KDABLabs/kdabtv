/*************************************************************************
 *
 * Copyright (c) 2008-2010, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "scribbleArea.h"

#include <QMouseEvent>
#include <QPainter>

ScribbleArea::ScribbleArea( QWidget* parent )
    : QWidget( parent ), m_drawing()
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

ScribbleArea::~ScribbleArea() {}

/**
  * This virtual method gets called whenever the users presses the
  * mouse over the window.
  */
void ScribbleArea::mousePressEvent( QMouseEvent* event )
{
    m_drawing.moveTo( event->pos() ); // record new mouse position
}


/**
  * This virtual method gets called whenever the user moves the mouse
  * while the mouse button is pressed (this is also known as
  * "dragging"). If we had called setMouseTracking( true ) before,
  * this method would also be called when the mouse was moved without
  * any button pressed. We know that we haven't, and thus don't have
  * to check whether any buttons are pressed.
  */
void ScribbleArea::mouseMoveEvent( QMouseEvent* event )
{
    // record a line from the last position to the current one
    m_drawing.lineTo( event->pos() );
    // schedule a repaint:
    update();
}



/**
  * This virtual method gets called whenever the widget needs
  * painting.
  */
void ScribbleArea::paintEvent( QPaintEvent* )
{
    /*
     * Draw the path (populated via mouse events) onto the widget itself.
     * Note that we don't need to clear the previous contents before
     * repainting -- this is automatically done by Qt for us
     * (cf. the Qt::WA_NoSystemBackground widget attribute).
     */

    QPainter painter( this );
    painter.setPen( QPen( Qt::black, 3 ) );
    painter.drawPath( m_drawing );
}
