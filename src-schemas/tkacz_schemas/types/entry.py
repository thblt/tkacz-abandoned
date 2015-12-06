from tkacz.model.types import *

class Entry( TZType ):

				entryType = Taxonomy( "core.bib.entry.subtype" )

				title = TZString()
				title.required = True

				subTitle = TZString()
				subSubTitle = TZString()

				subSubTitle.enabled = IsSet( "subTitle" )  # IsSet and similar functions are *cool*,
																									 # because they directly hook up the th