#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
# All rights reserved.
#
# See the LICENSE.txt file shipped along with this file for the license.

from PySide2.QtCore import Signal, Property
from PySide2.QtGui import QPen, QColor
from PySide2.QtQuick import QQuickPaintedItem


class EllipseItem(QQuickPaintedItem):
    colorChanged = Signal()

    def __init__(self, parent = None):
        QQuickPaintedItem.__init__(self, parent)
        self._color = None

    def paint(self, painter):
        painter.save()
        pen = QPen(self._color)
        pen.setWidth(3)
        painter.setPen(pen)
        painter.drawEllipse(0, 0, self.width(), self.height())
        painter.restore()

    def getColor(self):
        return self._color

    def setColor(self, new_color):
        if self._color != new_color:
            self._color = new_color
            self.update()
            self.colorChanged.emit()

    color = Property(QColor, getColor, setColor, notify=colorChanged)
