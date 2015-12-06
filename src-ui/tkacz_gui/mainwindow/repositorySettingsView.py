from PyQt4 import QtGui, QtCore
from tkacz.gui.uibase._mwRepositorySettingsView import Ui_RepositorySettingsView
from tkacz.gui.core import TZView

class RepositorySettingsView(QtGui.QFrame, Ui_RepositorySettingsView, TZView):
	__context__ = "configure"
	
	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QFrame.__init__(self, parent, f)
		self.setupUi(self)