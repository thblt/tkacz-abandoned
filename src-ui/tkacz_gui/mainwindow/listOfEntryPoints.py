from PyQt4 import QtGui, QtCore
from tkacz.gui.core import TZObject
from tkacz.gui.uibase._mwListOfEntryPoints import Ui_ListOfEntryPoints

class ListOfEntryPoints(QtGui.QFrame, Ui_ListOfEntryPoints, TZObject):
	
	COLLECTIONS = 1;
	SETTINGS = 1024
	_selection = COLLECTIONS

	@QtCore.pyqtSignature("")
	def on_collectionsButton_clicked(self):
		pass
	
	@QtCore.pyqtSignature("")
	def on_settingsButton_clicked(self):
		pass
	
	@QtCore.pyqtSignature	("QModelIndex")
	def on_collectionsTV_clicked(self, index):
		#@FIXME Use selectionChanged on the model
		self.selection = index
		
	def getSelection(self):
		return self._selection
	def setSelection(self, value):
		if value == self._selection: return
		self._selection = value
		if type(value) is QtCore.QModelIndex:
			self.fakeButton.setChecked(True)
		else:
			self.collectionsTV.clearSelection()
		self.emit(QtCore.SIGNAL("selectionChanged()"))
		
	selection = property(getSelection, setSelection, "selection's docstring")

	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QFrame.__init__(self, parent, f)
		self.setupUi(self)
		self.fakeButton.setVisible(False) 
		# The fake button is there because there
		# doesn't seem to be a way to have a button group have nothing selected once
		# some button has been checked — and we need this if the user selects the 
		# treeview 