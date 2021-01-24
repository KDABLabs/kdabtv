# This Python file uses the following encoding: utf-8
#
# Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
# All rights reserved.
#
# See the LICENSE.txt file shipped along with this file for the license.

import random

from PyQt5.QtCore import QObject, QTimer, pyqtSignal as Signal, pyqtSlot as Slot, pyqtProperty


class RandomTimer(QObject):
    timeout = Signal()
    intervalChanged = Signal()
    activeChanged = Signal()

    def __init__(self, parent=None):
        super(RandomTimer, self).__init__()

        self.timer = QTimer()
        self.timer.timeout.connect(self.timeout)

    @Slot()
    def start(self):
        print("timer start")
        if not self.timer.isActive():
            self.timer.start()
            self.activeChanged.emit()

    @Slot()
    def stop(self):
        print("timer stop")
        if self.timer.isActive():
            self.timer.stop()
            self.activeChanged.emit()

    @Slot(int, int, result=int)
    def randomInterval(self, min, max):
        range = max - min
        msec = min + random.randint(0, range)
        return msec

    @pyqtProperty(int, notify=intervalChanged)
    def interval(self):
        return self.timer.interval()

    @interval.setter
    def interval(self, msec):
        if self.timer.interval() != msec:
            self.timer.setInterval(msec)
            self.intervalChanged.emit()
            print("interval = {}".format(self.timer.interval()))

    @pyqtProperty(bool, notify=activeChanged)
    def active(self):
        return self.timer.isActive()
