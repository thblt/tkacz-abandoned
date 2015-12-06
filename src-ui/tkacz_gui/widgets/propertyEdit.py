from PyQt4 import QtCore, QtGui
from tkacz.gui.uibase._propertyEditWidget import Ui_PropertyEdit

class PropertyEdit(QtGui.QWidget, Ui_PropertyEdit):
	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QWidget.__init__(self, parent, f)

		self.setupUi(self)