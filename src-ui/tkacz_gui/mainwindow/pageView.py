# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file './ui/mwPageView.ui'
#
# Created: Sun Mar 31 16:25:28 2013
#      by: PyQt4 UI code generator 4.10
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui
from tkacz.gui.uibase._mwPageView import Ui_PageView
from tkacz.gui.models import PagesModel
from tkacz.gui.core import TZView

class PageView(QtGui.QWidget, Ui_PageView, TZView):
	__context__ = "page"
	_page = None
	
	pageSelected = QtCore.pyqtSignal()
	selectionCleared = QtCore.pyqtSignal()
	
	@property
	def page(self):
		return self._page
	
	@page.setter
	def page(self, page):
		if self.page and not page:
			self.selectionCleared.emit()
			
		self.pageEditor.page = page
		self.pagesList.page = page
		
		if page:
			self.pageSelected.emit()
			

	@QtCore.pyqtSlot("QModelIndex")
	def on_selectionChanged(self, index):
		self.page = self.pagesList.listView.model().nodeFromIndex(index)
	
	def startView(self, mainWindow):
		self.pagesList.listView.setModel(PagesModel(mainWindow.repository.pagesList()))
		self.pagesList.listView.clicked.connect(self.on_selectionChanged)
	
	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QWidget.__init__(self, parent, f)

		self.setupUi(self)
		
		self.page = None