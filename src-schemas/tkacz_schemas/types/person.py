from tkacz.mapper import *
from thblt.parsing import Language, TkRegExp, tokenize, TkConstruct, ParserRuntimeException
from symbol import except_clause


class PersonName( TZType ):

		informal = TZBoolean( False )
		""" 
		Whether this name is “informal”, and should be represented only as a string instead
		of being analized as title + first + middle etc. This applies to organizations of 
		any form as well as to some aliases.
		"""

		# Various components of a “name” in the more common form for a physical person.
		title = TZString()
		""" The title, as in Prof. X… """
		title.enabled = IfEquals( "informal", False )

		first = TZString()
		""" The first name, as in Prof. Sandra X """
		first.enabled = IfEquals( "informal", False )

		middle = TZString()
		""" The middle part of the name, as in Prof. Sandra Mary X """
		middle.enabled = IfEquals( "informal", False )

		von = TZString()
		""" The von part, as in Prof. Sandra Mary van Deecken """
		von.enabled = IfEquals( "informal", False )

		last = TZString()
		""" The last name or family name, as in Prof. Sandra Mary van Deecken """
		last.enabled = IfEquals( "informal", False )

		suffix = TZString()
		""" The name's suffix (Jr, Sr, and so on), as in Prof. Sandra Mary Roberts Jr. """
		suffix.enabled = IfEquals( "informal", False )

		informalName = TZString()
		""" If the name is called informal, then this property is the only one used. """
		informalName.enabled = IfEquals( "informal", True )

		_lang = Language()

		_lang.addToken( TkRegExp( "UPPER", '[A-Z][a-zA-Z]*\.?' ) )
		_lang.addToken( TkRegExp( "LOWER", '[a-z]+\.?' ) )
		_lang.addToken( TkRegExp( "COMMA", ',' ) )
		_lang.addToken( TkRegExp( "DASH", '\s*-+\s*' ) )
		_lang.addToken( TkRegExp( "WS", '\s+' ) )

		def set( self, val ):
			parser = SteppableParser(val, _lang)
			try:
				tokens = tokenize( val, self._nameParserTokens )
				print( tokens )
			except ParserRuntimeException as e:
				print( "Failed!", e._message, "at", e.codePoint )
				print( val + "\n" + e.codePoint * " " + "^" )



class Person( TZDocument ):

	class NameAssignedToPerson( TZType ):
		name = PersonName()
		status = TZOneOf( ( "Alias", "Aka", "Normal form", "Rejected form", "Known alias" ) )
		notes = TZString()

	names = NameAssignedToPerson()

	notes = TZString()


