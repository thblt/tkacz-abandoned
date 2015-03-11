from tkacz import *

class BibTexImporter(TZImporter):
	"""
	Imports a BibTex database into the refman schema.
	"""
	
	__tzid__ = "bibtex"
	
	theFile = TZArgument(TZFile, auto=true)