from PyQt4 import QtGui, QtCore
from tkacz.core import tkaczRuntime

class TZObject(QtCore.QObject):
	_tzMainWindow = None

	def _tzGetMainWindow(self):
		""" Returns the first parentWidget() of this object which is a 
		tkacz.gui.mainwindow.MainWindow. (There should be only one) """ 
		if self._tzMainWindow: return self._tzMainWindow
		from tkacz.gui.mainwindow import MainWindow
		o = self
		while not isinstance(o, MainWindow):
			o = o.parentWidget()
		self._tzMainWindow = o
		return o

	def tzAction(self, action):
		""" @see tkacz.gui.mainwindow.MainWindow.action() """
		return self._tzGetMainWindow().action(action)

	def tzCommitChanges(self):
		return self._tzGetMainWindow().commitChanges()
	
class TZView(TZObject):
	__context__ = None
	
	def initView(self, mainWindow, **kwargs):
		self._tzMainWindow = mainWindow
		self.startView(mainWindow, **kwargs)
		
	def startView(self, mainWindow, **kwargs):
		pass