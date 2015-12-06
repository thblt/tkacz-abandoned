from PyQt4.QtCore import QAbstractItemModel, QModelIndex, QAbstractListModel
from PyQt4 import QtCore, QtGui

class CollectionsRoot( object ):
	_model = None

	id = None
	name = "[root]"
	parent = None

	def __init__( self, model ):
		self._model = model

	def childrenCount( self ):
		return len( self.getChildren() )

	def getChildren( self ):
		return self._model.source.collections
	children = property( getChildren )

class CollectionsModel( QAbstractItemModel ):

	_source = None

	_items = None  # dict: _items[QModelIndex] = Collection
	_indexes = None  # dict: _items[Collection] = QModelIndex

	source = property( lambda self: self._source )

	def index( self, row, column, parent ):
		if row < 0 or column < 0 or row >= self.rowCount( parent ) or column >= self.columnCount( parent ):
			return QtCore.QModelIndex()

		if not parent.isValid():
			parentItem = self.rootItem
		else:
			parentItem = self.nodeFromIndex( parent )

		childItem = parentItem.children[row]

		if childItem:
			return self.createIndex( row, column, childItem )
		else:
			return QModelIndex()

	def hasChildren( self, parent ):
		return bool( len( self.nodeFromIndex( parent ).children ) )

	def nodeFromIndex( self, idx ):
		if idx in self._items.keys():
			return self._items[idx]
		return self.rootItem

	def parent( self, index ):
		if not index.isValid():
			return QtCore.QModelIndex()

		childItem = self.nodeFromIndex( index )

		parentItem = childItem.parent
		return self.createIndex( 0, 0, parentItem ) if parentItem else QModelIndex()

	def createIndex( self, row, column, item ):
		ret = QAbstractItemModel.createIndex( self, row, column, item )
		self._items[ret] = item
		return ret

	def rowCount( self, parent ):
		if parent.column() > 0:
			return 0

		if not parent.isValid():
			parentItem = self.rootItem
		else:
			parentItem = self.nodeFromIndex( parent )

		return parentItem.childrenCount()

	def columnCount( self, QModelIndex, parent=QModelIndex ):
		return 1

	def fromIndex( self, index ):
		return self._items[index]

	def data( self, index, role ):

		if not index.isValid():
			return None
		coll = self.nodeFromIndex( index )
		if role == QtCore.Qt.DisplayRole:
			return coll.name
		elif role == QtCore.Qt.DecorationRole:
			if coll.magic:
				return QtGui.QIcon( QtGui.QPixmap( ":/collections/collection-dynamic/" ) )
			if coll.dynamic:
				return QtGui.QIcon( QtGui.QPixmap( ":/collections/collection-dynamic/" ) )
			else:
				return QtGui.QIcon( QtGui.QPixmap( ":/collections/collection-static/" ) )

	def __init__( self, source ):
		QAbstractItemModel.__init__( self )
		self._source = source
		self._items = dict()
		self.rootItem = CollectionsRoot( self )
		# repository.addListener( self )

class PagesRoot( object ):
	id = None
	name = "[root]"

	_pages = None

	def __init__( self, source ):
		self._pages = source.pages

	def childrenCount( self ):
		return len( self._pages )

	def childIndex( self, page ):
		return self._pages.index( page )

	def getChildren( self ):
		return self._pages
	children = property( getChildren )


class PagesModel( QAbstractListModel ):
	_repository = None

	_items = None  # dict: _items[QModelIndex] = Page
	# _indexes = None  # dict: _items[Collection] = QModelIndex

	def rowCount( self, parent ):
		parentItem = self.nodeFromIndex( parent )
		if not parentItem == self.rootItem: return 0

		return parentItem.childrenCount()

	def index( self, row, column, parent ):
		if row < 0 or column < 0 or row >= self.rowCount( parent ) or column >= self.columnCount( parent ):
			return QtCore.QModelIndex()

		if not parent.isValid():
			parentItem = self.rootItem
		else:
			parentItem = self.nodeFromIndex( parent )

		childItem = parentItem.children[row]

		if childItem:
			return self.createIndex( row, column, childItem )
		else:
			return QModelIndex()

	def hasChildren( self, parent ):
		return bool( len( self.nodeFromIndex( parent ).children ) )

	def nodeFromIndex( self, idx ):
		if idx in self._items.keys():
			return self._items[idx]
		return self.rootItem

	def parent( self, index ):
		if not index.isValid():
			return QtCore.QModelIndex()

		childItem = self.nodeFromIndex( index )

		parentItem = childItem.parent
		return self.createIndex( 0, 0, parentItem ) if parentItem else QModelIndex()

	def createIndex( self, row, column, item ):
		ret = QAbstractItemModel.createIndex( self, row, column, item )
		self._items[ret] = item
		return ret

	def columnCount( self, QModelIndex, parent=QModelIndex ):
		return 1

	def fromIndex( self, index ):
		return self._items[index]

	def data( self, index, role ):
		if not index.isValid():
			return None
		page = self.nodeFromIndex( index )
		if role == QtCore.Qt.DisplayRole:
			return page.titleCache
		elif role == QtCore.Qt.DecorationRole:
			return QtGui.QIcon( QtGui.QPixmap( ":/types/person" ) )
# 			if coll.dynamic:
# 				return QtGui.QIcon(QtGui.QPixmap(":/collections/collection-dynamic/"))
# 			else:
# 				return QtGui.QIcon(QtGui.QPixmap(":/collections/collection-static/"))

	def __init__( self, source, checkable=False ):
		QAbstractListModel.__init__( self )
		self._items = dict()
		self.rootItem = PagesRoot( source )
