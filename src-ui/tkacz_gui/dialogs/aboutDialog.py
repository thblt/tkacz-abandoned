from tkacz.gui.uibase import _dlgAbout, common_rc
from PyQt4 import QtCore, QtGui
import webbrowser
from thblt.qt import loadResourceText
from tkacz.core import tkaczRuntime

class AboutDialog(QtGui.QDialog, _dlgAbout.Ui_AboutDialog):
	""" The About Tkacz dialog. 
	@TODO Shouldn't be maximizable on MacOS X """
	
	def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
		QtGui.QDialog.__init__(self, parent, f)
		self.setupUi(self)
		
		self.pages.setCurrentWidget(self.logoPage)
		self.versionLabel.setText(self.versionLabel.text().format(
			version=tkaczRuntime.version['version'],
			maturity =
				{tkaczRuntime._MATURITY_NIGHTLY:self.trUtf8(" nightly", "AboutDialog"),
				tkaczRuntime._MATURITY_ALPHA:self.trUtf8(" alpha", "AboutDialog"),
				tkaczRuntime._MATURITY_BETA:self.trUtf8(" beta", "AboutDialog"),
				tkaczRuntime._MATURITY_STABLE:"",
				}[tkaczRuntime.version['maturity']]))
		
	def on_backButton_clicked(self):
		self.pages.setCurrentWidget(self.logoPage)
		
	def on_textBrowser_anchorClicked(self, link):
		webbrowser.open(link.toString())
		
	def on_versionLabel_linkActivated(self, link):
		self.pages.setCurrentWidget(self.browserPage)
		if link == "license":
			self.textBrowser.setText(loadResourceText(":/tkacz/license"))
		elif link == "others":
			self.textBrowser.setText(loadResourceText(":/tkacz/credits"))

	def on_linkLabel_linkActivated(self, link):
		webbrowser.open("http://www.tkacz.org")
