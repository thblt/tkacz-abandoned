# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file './ui/mwToolBarWidget.ui'
#
# Created: Sun Mar 31 21:15:20 2013
#      by: PyQt4 UI code generator 4.10
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui
from tkacz.gui.uibase._mwToolBarWidget import Ui_ToolBar

class ToolBar(QtGui.QFrame, Ui_ToolBar):
	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QFrame.__init__(self, parent, f)

		self.setupUi(self)

