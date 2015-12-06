from PyQt4 import QtCore, QtGui
from tkacz.gui.uibase._mwLocationBar import Ui_LocationBar

class LocationBar(QtGui.QFrame, Ui_LocationBar):
	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QFrame.__init__(self, parent, f)

		self.setupUi(self)