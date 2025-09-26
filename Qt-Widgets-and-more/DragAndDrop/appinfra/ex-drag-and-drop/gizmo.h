/*************************************************************************
 *
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef GIZMO_H
#define GIZMO_H

#include <QColor>
#include <QFrame>

class QPaintEvent;
class QMimeData;

class Gizmo : public QFrame
{
public:
    explicit Gizmo(const QColor &, const QColor &, Qt::Orientation, QWidget *parent = nullptr);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    bool shouldStartDrag(QMouseEvent *event);
    QMimeData *mimeData() const;
    bool decodeMimeData(const QMimeData *mimeData);

    QColor m_color1, m_color2;
    Qt::Orientation m_orientation;
    QPoint m_pressPos;
};

#endif /* GIZMO_H */
