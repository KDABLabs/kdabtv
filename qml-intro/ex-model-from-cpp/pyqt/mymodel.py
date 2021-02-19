#!/usr/bin/env python3
#
# Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
# All rights reserved.
#
# See the LICENSE.txt file shipped along with this file for the license.
#
#

# This Python file uses the following encoding: utf-8

import random

from PyQt5.QtCore import QAbstractListModel, QObject, QMetaEnum, QTimer, pyqtSlot as Slot, QModelIndex, QVariant


class Data:
    def __init__(self, name, flag, population):
        super(Data, self).__init__()

        self.name = name
        self.flag = flag
        self.population = population


class MyModel(QAbstractListModel, QObject):

    def __init__(self):
        super(MyModel, self).__init__()

        self._m_data = [Data("Denmark", "images/denmark.jpg", 5.6),
                        Data("Sweden", "images/sweden.jpg", 9.6),
                        Data("Iceland", "images/iceland.jpg", 0.3),
                        Data("Norway", "images/norway.jpg", 5.1),
                        Data("Finland", "images/finland.jpg", 5.4)]

        growthTimer = QTimer(self)
        growthTimer.timeout.connect(self.growPopulation)
        growthTimer.start(2000)
        self.RAND_MAX = 2147483647

    class Roles(QMetaEnum):
        NameRole = 0
        FlagRole = 1
        PopulationRole = 2

    def rowCount(self, parent):
        if parent.isValid():
            return 0
        return len(self._m_data)

    def data(self, index, role):
        if not index:
            return QVariant

        if role == self.Roles.NameRole:
            return self._m_data[index.row()].name
        elif role == self.Roles.FlagRole:
            return self._m_data[index.row()].flag
        elif role == self.Roles.PopulationRole:
            return self._m_data[index.row()].population
        else:
            return QVariant

    def roleNames(self):
        _name = "name".encode('utf-8')
        _flag = "flag".encode('utf-8')
        _population = "population".encode('utf-8')

        mapping = {self.Roles.NameRole: _name,
                   self.Roles.FlagRole: _flag,
                   self.Roles.PopulationRole: _population}
        return mapping

    @Slot(int)
    def duplicateData(self, row):
        if row < 0 | row > len(self._m_data):
            return

        data = self._m_data[row]
        rowOfInsert = row + 1

        QAbstractListModel.beginInsertRows(self, QModelIndex(), rowOfInsert, rowOfInsert)
        self._m_data.insert(rowOfInsert, data)
        QAbstractListModel.endInsertRows(self)

    @Slot(int)
    def removeData(self, row):
        if row < 0 | row > len(self._m_data):
            return

        data = self._m_data[row]

        QAbstractListModel.beginRemoveRows(self, QModelIndex(), row, row)
        self._m_data.remove(data)
        QAbstractListModel.endRemoveRows(self)

    @Slot()
    def growPopulation(self):
        growthFactor = 0.01 / self.RAND_MAX

        count = len(self._m_data)
        for i in range(0, count):
            self._m_data[i].population += self._m_data[i].population * random.randint(1, self.RAND_MAX) * growthFactor

        startIndex = QAbstractListModel.index(self, 0, 0)
        endIndex = QAbstractListModel.index(self, count - 1, 0)

        self.dataChanged.emit(startIndex, endIndex, [self.Roles.PopulationRole])
