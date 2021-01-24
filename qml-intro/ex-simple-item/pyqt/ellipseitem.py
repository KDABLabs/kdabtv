#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
# All rights reserved.
#
# See the LICENSE.txt file shipped along with this file for the license.

from PyQt5.QtGui import QPen
from PyQt5.QtCore import pyqtProperty, pyqtSignal
from PyQt5.QtQuick import QQuickPaintedItem


class EllipseItem(QQuickPaintedItem):
    colorChanged = pyqtSignal()

    def __init__(self, parent=None):
        QQuickPaintedItem.__init__(self, parent)
        self._color = None

    def paint(self, painter):
        painter.save()
        pen = QPen(self._color)
        pen.setWidth(3)
        painter.setPen(pen)
        painter.drawEllipse(0, 0, self.width(), self.height())
        painter.restore()

    @pyqtProperty('QColor', notify=colorChanged)
    def color(self):
        return self._color

    @color.setter
    def color(self, new_color):
        if self._color != new_color:
            self._color = new_color
            self.update()
            self.colorChanged.emit()
