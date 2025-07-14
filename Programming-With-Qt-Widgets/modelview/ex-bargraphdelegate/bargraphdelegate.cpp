/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "bargraphdelegate.h"


const int MAX_VALUE = 100;
const int MIN_BAR_WIDTH = 64;

BarGraphDelegate::BarGraphDelegate(QObject *parent) :
    QAbstractItemDelegate(parent)
{
}

//--> slide
void BarGraphDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (index.data(Qt::UserRole).userType() == QVariant::Int) {
        const int value = index.data(Qt::UserRole).toInt();

        // rect with width proportional to value
        QRect rect(option.rect.adjusted(4,4,-4,-4));
        rect.setWidth(rect.width()*value/MAX_VALUE);

        // draw the value bar
        painter->fillRect(rect, QBrush(QColor("steelblue")
                                       .lighter(200-value)));
    }

    // Paint the text
    const QString text = index.data(Qt::DisplayRole).toString();
    painter->drawText(option.rect, Qt::AlignCenter, text);
}
//<-- slide

QSize BarGraphDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(MIN_BAR_WIDTH, option.fontMetrics.height());
}
