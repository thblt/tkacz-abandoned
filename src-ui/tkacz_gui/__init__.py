# -*- coding: UTF-8 -*-

from PyQt4 import pyqtconfig, QtCore, QtGui
from thblt.system import user_locale
from tkacz.core import tkaczRuntime
from tkacz.gui.uibase import common_rc
from tkacz.gui.mainwindow import MainWindow
from tkacz.core.storage.fs import FSRepository
import sys

class GuiController(QtGui.QApplication):
	_instances = None
	
	def addMainWindow(self, repository=FSRepository()):
		#@FIXME Make sure a newly created MainWindow has a different position than the 
		# one it's been created from, like x+100, y+100.
		mw = MainWindow(self, repository)
		self._instances.add(mw)
		mw.show()
		mw.raise_()
		return mw
		
	def startApp(self, args=[]):

		#Logging signature
		qtVer = pyqtconfig._pkg_config['qt_version']
		tkaczRuntime.message(
			"{tkacz} with Qt {qtMajor}.{qtMinor}.{qtMicro}/PyQt {pyQtVersion}, on Python {pyMajor}.{pyMinor}.{pyMicro} {pyReleaseLevel}."
			.format(
				tkacz=tkaczRuntime.version['signature'],
				qtMajor=int((qtVer & 0xF0000) / 0x10000),
				qtMinor=int((qtVer & 0xFF00) / 0x100),
				qtMicro=int((qtVer & 0xFF)),
				pyQtVersion=pyqtconfig._pkg_config['pyqt_version_str'],
				pyMajor=sys.version_info.major,
				pyMinor=sys.version_info.minor,
				pyMicro=sys.version_info.micro,
				pyReleaseLevel=sys.version_info.releaselevel,
				pySerial=sys.version_info.serial))
		
		self._instances = set()
		translator = QtCore.QTranslator(self)
		translator.load(':/i18n/tkacz_{0}'.format(user_locale()[0]))
		self.installTranslator(translator)

		# Fonts, regular
		assert QtGui.QFontDatabase.addApplicationFont(":/laf/font-Regular") >= 0	
		assert QtGui.QFontDatabase.addApplicationFont(":/laf/font-Bold") >= 0
		assert QtGui.QFontDatabase.addApplicationFont(":/laf/font-Italic") >= 0
		assert QtGui.QFontDatabase.addApplicationFont(":/laf/font-BoldItalic") >= 0
		# … light
		assert QtGui.QFontDatabase.addApplicationFont(":/laf/font-Light") >= 0
		assert QtGui.QFontDatabase.addApplicationFont(":/laf/font-LightItalic") >= 0
		assert QtGui.QFontDatabase.addApplicationFont(":/laf/font-ExtraBoldItalic") >= 0
		assert QtGui.QFontDatabase.addApplicationFont(":/laf/font-ExtraBoldItalic") >= 0
		# … semi bold		
		assert QtGui.QFontDatabase.addApplicationFont(":/laf/font-Semibold") >= 0
		assert QtGui.QFontDatabase.addApplicationFont(":/laf/font-SemiboldItalic") >= 0

		self.setApplicationName(tkaczRuntime.version['name'])
		self.setApplicationVersion(tkaczRuntime.version['version'])
		
		self.addMainWindow()		
		
		self.exec()
		
	def __init__(self, argv=list()):
		QtGui.QApplication.__init__(self, argv)