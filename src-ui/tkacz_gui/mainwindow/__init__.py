import os

from PyQt4.QtCore import pyqtSlot, Qt
from PyQt4 import QtGui, QtCore, pyqtconfig
from thblt.system import is_macosx
from tkacz.core.models import  Collection, Page, TkaczBase
from tkacz.core.storage import FileLoaderException
from tkacz.core import tkaczRuntime
from tkacz.gui.models import CollectionsModel, PagesModel
from tkacz.gui.core import TZObject, TZView
from tkacz.gui.uibase import _mainWindow, _coreLogic

class MainWindow( QtGui.QMainWindow, _mainWindow.Ui_MainWindow, TZObject ):

	_controller = None
	_repository = None

	_views = None
	_currentView = None

	_stateMachine = None
	_statePages = None
	_statePagesBrowse = None
	_statePagesEdit = None
	_stateCollections = None
	_stateCollectionsBrowse = None
	_stateCollectionsEdit = None
	_stateConfigure = None

	#=====================================================================================================================
	# High level methods
	#=====================================================================================================================

	def editCollection( self, coll ):
		from tkacz.gui.dialogs.collectionEditor import CollectionEditor
		editor = CollectionEditor( self )
		editor.setCollection( coll )
		editor.setWindowModality( QtCore.Qt.WindowModal )
		return editor.exec_()

	@pyqtSlot( "QString" )
	def saveFile( self, file ):
		self.repository.save( file )
		self._updateTitle()

	def setView( self, view ):
		return False

	def commitChanges( self ):
		self.repository.commit()

	#=====================================================================================================================
	# Action store mechanism
	#=====================================================================================================================
	_actionsCatalog = None

	def action( self, identifier ):
		ret = self.actionsCatalog( identifier )
		assert ret and isinstance( ret, QtGui.QAction )
		return ret

	def actionsCatalog( self, prefix ):
		""" Returns a catalog dict for the given prefix. 
		You'll get a pointer to the real catalog, so copy() it if you need to make changes. """
		if type( prefix ) is str:
			prefix = self._splitActionIdentifier( prefix )
		point = self._actionsCatalog
		for part in prefix:
				point = point[part]
		return point

	def registerActionPrefix( self, identifier, name=id ):
		identifier = self._splitActionIdentifier( identifier )
		parent = self.actionsCatalog( identifier[:-1] )
		parent[identifier[-1]] = dict()

	def registerAction( self, prefix, identifier, action ):
		self.actionsCatalog( prefix )[identifier] = action

	def _splitActionIdentifier( self, identifier ):
		return identifier.split( '.' )

	#=====================================================================================================================
	# pseudo-protected high-level methods
	#=====================================================================================================================

	def _updateTitle( self ):
		tpl = "{0}" if is_macosx() else self.trUtf8( "{0} — Tkacz", "MainWindow" )
		file = self.repository.file if self.repository.file else None
		if not is_macosx():
			self.setWindowTitle( tpl.format( file if file else self.trUtf8( "Untitled", "MainWindow" ) ) )
		if file:
			self.setWindowFilePath( file )

	#=====================================================================================================================
	# Overloaded event methods
	#=====================================================================================================================

	def closeEvent( self, event ):
		if self.repository.modified:
			qd = QtGui.QMessageBox( self )
			qd.setIcon( QtGui.QMessageBox.Warning )
			qd.setText( self.trUtf8( "This repository has been modified.", "MainWindow" ) )
			qd.setInformativeText( self.trUtf8( "Do you want to save your changes?", "MainWindow" ) )
			qd.setStandardButtons( QtGui.QMessageBox.Save | QtGui.QMessageBox.Discard | QtGui.QMessageBox.Cancel )
			qd.setDefaultButton( QtGui.QMessageBox.Save )
			qd.setWindowModality( QtCore.Qt.WindowModal )
			ret = qd.exec_()
			if ret == QtGui.QMessageBox.Save:
				self.on_actionSave_triggered()
				event.accept()
			elif ret == QtGui.QMessageBox.Discard:
				event.accept()
			elif ret == QtGui.QMessageBox.Cancel:
				event.ignore()

	#=======================================================================================================================
	# Repository action listeners
	#=======================================================================================================================

	@pyqtSlot()
	def on_actionRepositorySaveAs_triggered( self ):
		# As of Qt-4.5, to show a dialog as a sheet on Mac, use QDialog::open()
		# instead. Using QDialog::exec() means that the dialog is supposed to
		# be 'application modal', and therefore show up as a normal dialog.
		# This behaviour change turned out necessary since sheets on Mac are
		# only supposed to be used when dialogs are 'window modal'.  So the
		# real bug you found was that whe dialog showed up as a sheet in the
		# first place. We'll look into that.  -Richard http://fr.it-usenet.org/thread/15042/881/ (gmane.comp.lib.qt.qt4)
		fd = QtGui.QFileDialog( self )
		fd.setFilter( "*.tkacz" )
		fd.setAcceptMode( QtGui.QFileDialog.AcceptSave )
		fd.setWindowModality( QtCore.Qt.WindowModal )
		fd.fileSelected.connect( self.saveFile )
		fd.open()

	@pyqtSlot()
	def on_actionRepositoryCreate_triggered( self ):
		self._controller.addMainWindow()

	@pyqtSlot()
	def on_actionRepositoryOpen_triggered( self ):
		# Make the open dialog
		fd = QtGui.QFileDialog( self, filter="*.tkacz" )
		fd.setAcceptMode( fd.AcceptOpen )
		fd.setFileMode( fd.ExistingFile )
		# Run it
		if fd.exec_():
			if False and self.repository.empty:  # @FIXME -False and (testing)
				try:
					self.repository.file = fd.selectedFiles()[0]
					self._updateTitle()
				except FileLoaderException as e :
					tkaczRuntime.info( "Exception on loading file", e )
					QtGui.QMessageBox( 
						QtGui.QMessageBox.Warning,
						"",
						self.trUtf8( "The file “{0}” cannot be opened.", "MainWindow" )
						.format( fd.selectedFiles()[0] ) ).exec_()
			else:
				from tkacz.core.storage.fs import FSRepository
				self._controller.addMainWindow( FSRepository( fd.selectedFiles()[0] ) )

	@pyqtSlot()
	def on_actionRepositorySave_triggered( self ):
		if self.repository.saved:
			self.saveFile( None )
		else: self.on_actionRepositorySaveAs_triggered()

	#=======================================================================================================================
	# Collection action listeners
	#=======================================================================================================================

	@pyqtSlot()
	def on_actionCollectionCreateEmpty_triggered( self ):
		coll = Collection()
		if self.editCollection( coll ):
			self.repository.addCollection( coll )

	#=======================================================================================================================
	# Page action listeners
	#=======================================================================================================================

	@pyqtSlot()
	def on_actionPageCreateSimple_triggered( self ):
		page = Page()
		self._repository.add( page )
		self.pageView.page = page

	#=======================================================================================================================
	# App action listeners
	#=======================================================================================================================

	@pyqtSlot()
	def on_actionAppQuit_triggered( self ):
		tkaczRuntime.info( "Quitting." )

	@pyqtSlot()
	def on_actionAppAbout_triggered( self ):
		from tkacz.gui.dialogs.aboutDialog import AboutDialog
		ad = AboutDialog( self )
		ad.show()

	#=======================================================================================================================
	# Window action listeners
	#=======================================================================================================================

	@pyqtSlot( "bool" )
	def on_actionWindowFullscreen_toggled( self, checked ):
		if checked:
			self._beforeFS = ( self.isMaximized(), self.saveGeometry() )
			self.showFullScreen()
		else:
			if self._beforeFS[0]: self.showMaximized()
			else: self.showNormal()
			self.restoreGeometry( self._beforeFS[1] )

	@pyqtSlot()
	def on_actionWindowLocationbar_triggered( self ):
		self.locationBar.editor.setFocus()

	#=====================================================================================================================
	# Public properties
	#=====================================================================================================================

	@property
	def repository( self ):
		return self._repository

	def __init__( self, controller, repository ):
		QtGui.QMainWindow.__init__( self )
		self._repository = repository
		self._controller = controller  # The GUI controller object
		self._actionsCatalog = dict()  # The Actions catalog.
		_mainWindow.Ui_MainWindow.setupUi( self, self )  # Initialize from pyuic4 code
		_coreLogic.insertCoreLogic( self )  # Initialize from uiLogicCompiler.py code
		QtCore.QMetaObject.connectSlotsByName( self )  # Attach signals and slots.

		#######################
		# State machine setup #
		#######################
		self.stateTkaczModesPage.addTransition( self.pageView, QtCore.SIGNAL( "pageSelected()" ), self.stateTkaczModesPageEdit )

		self.pageView.initView( self )
		self.configureView.initView( self )

		###########
		# Toolbar #
		###########
		from tkacz.gui.mainwindow.locationBar import LocationBar
		lb = self.locationBar = LocationBar()
		self.toolBar.addAction( self.action( "page.create.popup" ) )
		self.toolBar.insertWidget( None, lb )
		if not( is_macosx( "Lion" ) and pyqtconfig._pkg_config['qt_version'] >= 0x50000 ):
			self.toolBar.addAction( self.action( "window.fullscreen" ) )

		# Mac fixes
		# =========
		lb.editor.setAttribute( Qt.WA_MacShowFocusRect, 0 )
		self.listOfEntryPoints.collectionsTV.setAttribute( Qt.WA_MacShowFocusRect, 0 )

		self.listOfEntryPoints.collectionsTV.setModel( CollectionsModel( self.repository.collectionsList() ) )  # @TODO Testing only

		# Finalization
		# ====
		self.addAction( self.action( "window.locationbar" ) )
		self._updateTitle()
	