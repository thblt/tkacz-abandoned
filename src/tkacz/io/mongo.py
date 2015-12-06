class MongoDB( object ):

	def __init__( self, server=None, dbpath=None, dbname="tkacz", lazy=True ):
		'''
		Initializes a new MongoDB abstraction layer.
		
		:param server: the URI to the MongoDB server. If this parameter is provided, dbpath
		and dbname will be ignored.
		:type server: URI string.
		:param dbpath: The path the databases files. If this parameter is provided, a mongod 
		instance will be started.
		:type dbpath: String
		:param dbname: The name of the database to create.
		:type dbname: String
		:param lazy: Whether to enable the lazy loader. Default is true.
		:type lazy: bool
		'''
