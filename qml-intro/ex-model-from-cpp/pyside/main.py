#!/usr/bin/env python3
#
# Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
# All rights reserved.
#
# See the LICENSE.txt file shipped along with this file for the license.
#
#

# This Python file uses the following encoding: utf-8

import os
import sys

from PySide2.QtGui import QGuiApplication
from PySide2.QtCore import QUrl
from PySide2.QtQuick import QQuickView

from mymodel import *


if __name__ == "__main__":
    app = QGuiApplication(sys.argv)
    myModel = MyModel()

    view = QQuickView()
    qmlFile = os.path.join(os.path.dirname(__file__), '../main.qml')

    context = view.rootContext()
    context.setContextProperty("_myModel", myModel)

    view.setSource(QUrl.fromLocalFile(os.path.abspath(qmlFile)))

    if view.status() == QQuickView.Error:
        sys.exit(-1)
    view.show()
    res = app.exec_()
    sys.exit(res)
