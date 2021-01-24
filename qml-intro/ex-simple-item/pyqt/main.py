#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
# All rights reserved.
#
# See the LICENSE.txt file shipped along with this file for the license.

import sys
import os

from PyQt5.QtGui import QGuiApplication
from PyQt5.QtCore import QUrl
from PyQt5.QtQml import qmlRegisterType
from PyQt5.QtQuick import QQuickView

from ellipseitem import EllipseItem


if __name__ == '__main__':
    app = QGuiApplication(sys.argv)

    qmlRegisterType(EllipseItem, 'Shapes', 1, 0, 'Ellipse')

    view = QQuickView()
    view.setResizeMode(QQuickView.SizeRootObjectToView)

    qmlFile = os.path.join(os.path.dirname(__file__), '../main.qml')
    view.setSource(QUrl.fromLocalFile(os.path.abspath(qmlFile)))
    if view.status() == QQuickView.Error:
        sys.exit(-1)
    view.show()

    res = app.exec_()
    sys.exit(res)
