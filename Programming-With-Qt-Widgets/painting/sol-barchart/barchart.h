/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2011-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef PIECHART_H
#define PIECHART_H

#include <QtWidgets>

class BarChart : public QWidget
{
    Q_OBJECT

public:
    explicit BarChart(QWidget *parent = nullptr);

    void addBar(const QString &label, int percentage, const QColor &color);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    struct Bar
    {
        QString label;
        int value;
        QColor color;
        QRect paintedRect;
        bool isSelected = false;
    };

    QVector<Bar> m_bars;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // PIECHART_H
