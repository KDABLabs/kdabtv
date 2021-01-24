#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
# All rights reserved.
#
# See the LICENSE.txt file shipped along with this file for the license.

import sys
import os
import datetime

from PyQt5.QtCore import pyqtSignal as Signal, pyqtSlot as Slot, pyqtProperty, QUrl, QObject, QTimer, QMetaEnum, Q_ENUM
from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import qmlRegisterType
from PyQt5.QtQuick import QQuickView

from user import *


if __name__ == "__main__":
    app = QGuiApplication(sys.argv)


    view = QQuickView()
    context = view.rootContext()
    qmlRegisterType(User, 'UserData', 1, 0, 'User')

    user_instance = User("Python Joe", datetime.datetime(1971, 7, 11))
    timer = QTimer()
    timer.start(3000)
    timer.timeout.connect(user_instance.changeRole)

    context.setContextProperty("_userData", user_instance)


    view.setResizeMode(QQuickView.SizeRootObjectToView)

    qmlFile = os.path.join(os.path.dirname(__file__), '../main.qml')
    view.setSource(QUrl.fromLocalFile(os.path.abspath(qmlFile)))
    if view.status() == QQuickView.Error:
        sys.exit(-1)
    view.show()

    res = app.exec_()
    del view
    sys.exit(res)
