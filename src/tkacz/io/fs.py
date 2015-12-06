from .zipBundle import ZipBundle

class FSRepository( object ):
	""" Models a repository stored on a local or remote filesystem, accessed through direct SQL queries. """

	_file = None  # The underlying file object (as of 0.0.1, this must be a ZipBundle object)
	_modified = False  # Whether or not this repository was modified since last save.

	_sessionClass = None  # The SQLAlchemy session class
	_session = None  # The SQLAlchemy session object

	_lists = None # A WeakSet of lists which requested updating from this repository

	@property
	def empty( self ):
		""" Returns whether this repository is empty, ie contains neither pages nor collections. """
		return not bool( self._session.query( Collection ).limit( 1 ).count() + self._session.query( Page ).limit( 1 ).count() )

	def pagesList( self, filtr=None, sorter=None, autoUpdate=False ):
		""" Returns a PagesList object with the filter `filter`, sorted by `sorter`. """
		return PagesList( self )

	def collectionsList( self, filtr=None, sorter=None, autoUpdate=False ):
		""" Returns a CollectionsList object with the filter `filter`, sorted by `sorter`. """
		return CollectionsList( self )

	def commit( self ):
		modified = self._session.dirty
		added = self._session.new

		self._session.commit()

		for o in modified:
			self._trigger( "on{0}Modified".format( o.__class__.__name__ ), {o} )

		for o in added:
			self._trigger( "on{0}Added".format( o.__class__.__name__ ), {o} )


	def pages( self, filtr=None, sorter=None ):
		# @TODO Implement sorting and filtering
		return self._session.query( Page ).all()

	def collections( self, filtr=None, sorter=None ):
		# @TODO Implement sorting and filtering
		return self._session.query( Collection ).all()

	modified = property( lambda self: self._modified )  # pylint: disable=W0212
	saved = property( lambda self: self._file.saved )  # pylint: disable=W0212

	@property
	def file( self ):
		if self._file: return self._file.fileName
		return None

	@file.setter
	def file( self, value=None ):
		if not value or type( value ) is str:
			self._file = ZipBundle( value )
		else:
			self._file = value  # @TODO

		return self._initEngine()

	def save( self, filename=None ):
		""" Saves this file back to the original file, or to filename if provided. """
		self._session.commit()
		self._file.save( filename )
		if filename:
			self._initEngine()
			# @TODO: self._trigger( "onRepositoryChanged" )
		self._modified = False

	def _initEngine( self ):
		self._engine = create_engine( self._file.dbUrl, echo=False )
		TkaczBase.metadata.create_all( self._engine )
		self._sessionClass.configure( bind=self._engine )
		return True

	def __init__( self, file=None ):
		self._sessionClass = sessionmaker()
		self.file = file

		self._session = self._sessionClass()
