# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file './src/tkacz/gui/pagePropertiesEditor.ui'
#
# Created: Mon Mar 25 14:40:23 2013
#      by: PyQt4 UI code generator 4.10
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui
from tkacz.gui.uibase._mwPagePropertiesEditor import Ui_PagePropertiesEditor

class PagePropertiesEditor(QtGui.QWidget, Ui_PagePropertiesEditor):
	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QWidget.__init__(self, parent, f)

		self.setupUi(self)

