from PyQt4 import QtCore, QtGui
from tkacz.gui.uibase._mwPagesList import Ui_PagesList
from tkacz.gui.core import TZObject

class PagesList(QtGui.QWidget, Ui_PagesList, TZObject):
	
	pageSelected = QtCore.pyqtSignal()
	selectionCleared = QtCore.pyqtSignal()
	
	@property
	def selection(self):
		return self._selection
	
	@selection.setter
	def selection(self, page):
		self._selection = page
		if page: self.pageSelected.emit()
		else: self.selectionCleared.emit()
	
	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QWidget.__init__(self, parent, f)
		self.setupUi(self)
		
		self.listView.setWordWrap(True)