#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
# All rights reserved.
#
# See the LICENSE.txt file shipped along with this file for the license.

import datetime

from PyQt5.QtCore import pyqtSignal as Signal, pyqtSlot as Slot, pyqtProperty, QObject, QMetaEnum, Q_ENUM


class Role(QMetaEnum):
    Developer = 0
    Tester = 1
    ProjectManager = 2


class User(QObject):

    nameChanged = Signal()
    ageChanged = Signal()
    roleChanged = Signal()
    loginChanged = Signal()
    Q_ENUM(Role)

    def __init__(self, name, birthDay):
        super(User, self).__init__()
        self._name = name
        self._birthDay = birthDay
        self._role = Role.ProjectManager
        self._age = 0
        self._loggedIn = False

    @pyqtProperty(str, notify=nameChanged)
    def name(self):
        return self._name

    @name.setter
    def name(self, newName):
        if self._name != newName:
            self._name = newName
            self.nameChanged.emit()

    @pyqtProperty(int, notify=ageChanged)
    def age(self):
        self._age = datetime.datetime.now().year - self._birthDay.year
        return self._age

    @pyqtProperty(int, notify=roleChanged)
    def role(self):
        return self._role

    def setRole(self, newRole):
        if self._role != newRole:
            self._role = newRole
            self.roleChanged.emit()

    @Slot()
    def changeRole(self):
        if self.role == Role.Developer:
            self.setRole(Role.Tester)
        else:
            self.setRole(Role.Developer)
        print('Timer fired')

    @pyqtProperty(bool, notify=loginChanged)
    def loggedIn(self):
        return self._loggedIn

    @loggedIn.setter
    def loggedIn(self, loggedIn):
        if not self._loggedIn == loggedIn:
            self._loggedIn = loggedIn
            self.loginChanged.emit()
