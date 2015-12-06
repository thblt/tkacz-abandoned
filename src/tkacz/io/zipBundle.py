from tkacz.core.storage import MalformedFileException, NewerFormatVersionException
import tempfile, zipfile, yaml, os
from thblt.filesystem import splitPath

class ZipBundle( object ):
	""" Accesses a tkacz repository as a zip bundle. """

	_F_META_FILENAME = "Meta"
	_F_DB_FILENAME = "db"
	_F_MEDIA_DIRNAME = "m"
	_F_META_FORMAT_VERSION_KEY = "tzZipBundleFormatVersion"
	_F_META_FORMAT_VERSION = 0x00001

	_TEMPLATE = {
		_F_DB_FILENAME: None,
		_F_META_FILENAME: yaml.dump( {_F_META_FORMAT_VERSION_KEY: _F_META_FORMAT_VERSION} ),
		_F_MEDIA_DIRNAME: {}
				}

	_fileName = None
	fileName = property( lambda self: self._fileName )
	# The name of the user-provided .tkacz file
	_tempDir = None
	# The name of the temporary directory to which the file _fileName gets expanded and accessed from.
	_tempDirObj = None
	# The python tempfile.TemporaryDirectory object representing _tempDir """

	saved = property( lambda self: bool( self._fileName ), None, None, \
					"""Whether this object corresponds to a defined file.
					If False, save() must be invoked with a file path as parameter""" )

	def isSaved( self ):
		return self._fileName

	@property
	def dbUrl( self ):
		return "sqlite:///" + self._getFilePath( self._F_DB_FILENAME )

	def _getFile( self, name, mode='r', create=False ):
		return open( self._getFilePath( name, create ), mode )

	def _getFilePath( self, name, create=False ):
		target = os.path.join( self._tempDir, name )
		assert os.path.abspath( target ).startswith( self._tempDir )

		if os.path.exists( target ): return target
		if create:
			path = os.path.split( target )[0]
			if not os.path.exists( path ):
				part = ""
				for dir_ in splitPath( path ):
					# @TODO This is not really safe, and not the best way to do.
					part = os.path.join( part, dir_ )
					if not ( os.path.exists( part ) ):
						os.mkdir( path )
			open( target, 'w' ).close()
			return target
		else:
			return None

	def _zipDir( self, zipFile, root, path="" ):
		rootLen = len( splitPath( root ) )

		for f in os.listdir( os.path.join( root, path ) ):
			fullpath = os.path.join( root, path, f )
			if os.path.islink( fullpath ): continue
			if os.path.isdir( fullpath ):
				self._zipDir( zipFile, root, os.path.join( path, f ) )
			elif os.path.isfile( fullpath ):
				shortPath = '/'.join( splitPath( fullpath )[rootLen:] )
				zipFile.write( fullpath, shortPath )

	def save( self, newFileName=None ):
		file = newFileName if newFileName else self._fileName
		if not file:
			raise Exception( "No destination for save()." )

		zf = zipfile.ZipFile( file, mode='w', allowZip64=True )
		self._zipDir( zf, self._tempDir )
		zf.close()

		self._fileName = file

	def close( self ):
		self._tempDirObj.cleanup()
		self._fileName = None

	def _initTempDir( self, populate=False ):
		assert not self._tempDirObj

		self._tempDirObj = tempfile.TemporaryDirectory()
		self._tempDir = self._tempDirObj.name

		if populate:
			for name, contents in self._TEMPLATE.items():
				fullpath = os.path.join( self._tempDir, name )
				if type( contents ) is dict:
					os.mkdir( fullpath )
					# @TODO Populate /media/ directory --- not needed now (0.0.1)
				else:
					with open( fullpath, 'w' ) as f:
						if contents: f.write( contents )

	def __init__( self, filename=None, init=False ):
		if filename:
			if not zipfile.is_zipfile( filename ): raise MalformedFileException()
			try:
				zf = zipfile.ZipFile( filename, mode='r', allowZip64=True )
				Meta = yaml.safe_load( zf.open( self._F_META_FILENAME ) )
				if not self._F_META_FORMAT_VERSION_KEY in Meta.keys():
					raise MalformedFileException()
				elif not int( Meta[self._F_META_FORMAT_VERSION_KEY] ) == self._F_META_FORMAT_VERSION:
					raise NewerFormatVersionException()

				try:
					zf.getinfo( self._F_DB_FILENAME )
				except KeyError as e:
					raise MalformedFileException( e )

				self._initTempDir()

				zf.extractall( self._tempDir )

				self._fileName = filename
			except ( IOError, KeyError, RuntimeError, yaml.error.YAMLError ) as e:
				raise MalformedFileException( e )