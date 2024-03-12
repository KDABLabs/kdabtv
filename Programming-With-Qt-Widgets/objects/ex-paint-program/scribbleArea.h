/*************************************************************************
 *
 * Copyright (c) 2008-2010, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QWidget>
#include <QPainterPath>

class QResizeEvent;
class QPaintEvent;
class QMouseEvent;

/**
  * A class that lets the user draw scribbles with the mouse. The
  * window knows how to redraw itself.
  */
class ScribbleArea : public QWidget
{
  Q_OBJECT
public:
  explicit ScribbleArea( QWidget* parent=nullptr );
  ~ScribbleArea() override;

protected:
  void mousePressEvent( QMouseEvent* ) override;
  void mouseMoveEvent( QMouseEvent* ) override;
  void paintEvent( QPaintEvent* ) override;

private:
  QPainterPath m_drawing;
};

#endif /* SCRIBBLEAREA_H */

