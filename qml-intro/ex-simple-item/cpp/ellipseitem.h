/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef ELLIPSEITEM_H
#define ELLIPSEITEM_H

//--> slide
#include <QQuickPaintedItem>

class EllipseItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color
               WRITE setColor NOTIFY colorChanged)

public:
    explicit EllipseItem(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;
//<-- slide
    QColor color() const;
    void setColor(const QColor &newColor);

signals:
    void colorChanged();

private:
    QColor m_color;
};

#endif
