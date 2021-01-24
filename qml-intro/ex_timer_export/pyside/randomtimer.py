# This Python file uses the following encoding: utf-8
#
# Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
# All rights reserved.
#
# See the LICENSE.txt file shipped along with this file for the license.

import random

from PySide2.QtCore import QObject, QTimer, Signal, Slot, Property


class RandomTimer(QObject):
    timeout = Signal()
    intervalChanged = Signal()
    activeChanged = Signal()

    def __init__(self):
        super(RandomTimer, self).__init__()

        self.timer = QTimer()
        self.timer.timeout.connect(self.timeout)

    def interval(self):
        return self.timer.interval()

    def setInterval(self, msec):
        if self.timer.interval() != msec:
            self.timer.setInterval(msec)
            self.intervalChanged.emit()
            print("interval = {}".format(self.timer.interval()))

    @Slot()
    def isActive(self):
        return self.timer.isActive()

    @Slot()
    def start(self):
        if not self.timer.isActive():
            self.timer.start()
            self.activeChanged.emit()

    @Slot()
    def stop(self):
        if self.timer.isActive():
            self.timer.stop()
            self.activeChanged.emit()

    @Slot(int, int, result=int)
    def randomInterval(self, min, max):
        range = max - min
        msec = min + random.randint(0, range)
        return msec

    interval = Property(int, interval, setInterval, notify=intervalChanged)
    active = Property(bool, isActive, notify=activeChanged)

