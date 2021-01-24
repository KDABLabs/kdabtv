# This Python file uses the following encoding: utf-8
#
# Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
# All rights reserved.
#
# See the LICENSE.txt file shipped along with this file for the license.

import sys
import os

from PySide2.QtCore import QUrl
from PySide2.QtGui import QGuiApplication
from PySide2.QtQuick import QQuickView
from PySide2.QtQml import qmlRegisterType

from randomtimer import RandomTimer


if __name__ == "__main__":
    app = QGuiApplication(sys.argv)

    view = QQuickView()

    qmlRegisterType(RandomTimer, "CustomComponents", 1, 0, "RandomTimer")

    qmlFile = os.path.join(os.path.dirname(__file__), '../main.qml')
    view.setSource(QUrl.fromLocalFile(os.path.abspath(qmlFile)))
    if view.status() == QQuickView.Error:
        sys.exit(-1)
    view.show()
    res = app.exec_()
    sys.exit(res)
