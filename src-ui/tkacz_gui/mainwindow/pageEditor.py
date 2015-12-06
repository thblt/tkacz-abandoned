# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file './ui/mwPageEditor.ui'
#
# Created: Sun Mar 31 16:25:28 2013
#      by: PyQt4 UI code generator 4.10
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui
from tkacz.gui.uibase._mwPageEditor import Ui_PageEditor
from tkacz.gui.core import TZObject

class PageEditor(QtGui.QWidget, Ui_PageEditor, TZObject):
	
	_page = None
	
	@property
	def page(self):
		return self._page
	
	@page.setter
	def page(self, page):
		self._page = page
		if page:
			self.title.setText(page.titleCache)
			(self.body if page.titleCache else self.title).setFocus()
		
	@QtCore.pyqtSlot("QString")
	def on_title_textChanged(self, title):
		title = title.strip()
		if len(title):
			self._page.titleCache = title
			self.tzCommitChanges()
	
	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QWidget.__init__(self, parent, f)

		self.setupUi(self)
