from tkacz.gui.uibase._dlgCollectionEditor import Ui_CollectionEditor
from PyQt4 import QtGui, QtCore
from tkacz.gui.core import TZObject
from tkacz.gui.models import CollectionsModel

class CollectionEditor(QtGui.QDialog, Ui_CollectionEditor, TZObject):
	_collection = None
	
	def setCollection(self, collection):
		self._collection = collection
		self.collectionNameLE.setText(collection.name)
	
	@QtCore.pyqtSlot()
	def onAccept(self):
		self.tzEnterContext("modified")
		if not self._collection:
			return
		self._collection.name = self.collectionNameLE.text()
		selection = self.parentTreeView.selectedIndexes()
		if len(selection):
			self._collection.parent = self.parentTreeView.model().nodeFromIndex(selection[0])
	
	def on_dynamicCollectionRB_toggled(self, value):
		self.tabWidget.setTabEnabled(1, value)

	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QFrame.__init__(self, parent, f)
		self.setupUi(self)
		
		self.connect(self, QtCore.SIGNAL("accepted()"), self, QtCore.SLOT("onAccept()"))
		
		self.parentTreeView.setModel(CollectionsModel(parent.repository))
		self.tabWidget.setTabEnabled(1, False)