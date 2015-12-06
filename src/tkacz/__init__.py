import sys, os
from thblt.system import Version
from thblt.logger import Logger
from tkacz.mapper import TZDocument

logger = Logger()
class Tkacz( object ):
	""" This is the core Tkacz controller. It doesn't do much. """

	_dataDir = os.path.dirname( __file__ )

	_types = dict()

	def discover(self, tztype):
		pass

	def makeCard(self, tztype):
		if type(tztype) is str:
			tztype = self._types[tztype]
		assert issubclass(tztype, TZDocument)
		return tztype()

	def _initTypes(self, types):
		for t in types :
			assert issubclass(t, TZDocument)
			typeId = "{0}.{1}" .format(t.__module__, t.__name__)
			logger.info("I now know `{0}' as a card type.".format(typeId))
			
			self._types[typeId] = t
		
	def __init__( self, repo, create=False, **kwargs ):
		logger.info("Tkacz heating up.")
		
		'''
		Creates a new Tkacz object.
		:param repo: The full path to the data repository.
		:type repo: str
		:param create: Whether to create the repository if missing.
		:type create: bool
		'''
		
		from tkacz_schemas import root
		self._initTypes(root)