#!/Library/Frameworks/Python.framework/Versions/3.3/bin/python3.3

import copy

""" 
Defines the abstract types, objects and extensions used by Tkacz. This is the very basic
API for a schema.
"""

class TZAbstractDatum( object ):
	tzType = property( lambda self: self.__class__.__module__ + '.' + self.__class__.__name__ )
	
	def set( self, value ):
		raise Exception( "Direct input unavailable for {0}".format( self.tzType ) )

##########################################################################################
# Primitives																			 #
##########################################################################################

class TZPrimitive( TZAbstractDatum ):
	''' 
	A TZPrimitive is a single piece of data. Types are made of primitives or other Types.
	
	Primitives are only used in Types. Cards can't be Primitives only.
	
	The standard definition of a Primitive is a) it has no member data and b) it (should)
	serializes to a string instead of a dict.
	'''

	def set( self, value ):
		self._value = self.decode( value )

	value = property( lambda self: self._value, set )
	
	def __init__(self):
		self._value = None
		self.__tzDict__ = dict()
		
	def __repr__(self):
		return (str(self._value))
	
	def serialize (self):
		return self._value 

class TZString( TZPrimitive ):
	""" A String """
	def decode( self, value ):
		return str( value )

class TZBoolean( TZPrimitive ):
	def decode( self, value ):
		return bool( value )

	def __init__( self, default=False ):
		super(TZBoolean, self).__init__()
		self.default = property( default )

class TZInteger( TZPrimitive ):
	def decode( self, value ):
		return int( value )

class TZFloat( TZPrimitive ):
	def decode( self, value ):
		return float( value )

class TZList( TZPrimitive ):
	pass

class TZSet( TZPrimitive ):
	pass

class TZOneOf( TZPrimitive ):
	def __init__( self, values ):
		super(TZOneOf, self).__init__()
		self.amongst = values
	
	def decode(self, val):
		if val in self.amongst:
			self._value = val
		else:
			raise Exception("Illegal input.")

class TZSomeOf( TZPrimitive ):
	def __init__( self, values ):
		self.values = property( values )

##########################################################################################
# Types					 					 					 					 					 					 					 					   #
##########################################################################################

class TZType( TZAbstractDatum ):
	'''
	A Type is a the description of a meaningful set of other types and primitives. It can be 
	represented by a Python dict.
	
	Warning, there's some black magic here. TZTypes are meant to be easy to create, and
	making a new type is as simple as adding fields such as:
	something = TZString()
	to a new class inheriting TZTypes. When instantiating the object, it creates an internal
	dictionary (at instance level) to hold the effective values, and uses 
	'''
	
	def __setattr__(self, name, val):
		target = getattr(self, name)
		if isinstance(target, TZAbstractDatum):
			return target.set(val)
		else:
			target = val
	
	def serialize(self):
		out = dict()
		
		for name, val in self.__dict__.items():
			out[name] = val.serialize()

		return out
	
	def __init__( self ):
		# Copy class objects into instance objects. 
		for name, value in self.__class__.__dict__.items():
			if isinstance( value, TZAbstractDatum ):
				object.__setattr__(self, name, copy.copy(value))

class TZDocument( TZType ):
	
	__tzCollection__ = 'cards'
	__tzDocId = 14
	
	def serialize(self, atRoot = False):
		if atRoot:
			out = super(TZDocument, self).serialize()
		else:
			out = { '_link': True }
		out['_type'] = self.tzType
		out['_id'] = self.__tzDocId
		return out

##########################################################################################
# Tests																				  #
##########################################################################################

class TZTest( object ):
	pass

class IfEquals( TZTest ):
	def __init__( self, prop, value ):
		self._property = prop
		self._value = value

	def evaluate( self, target ):
		return target.findProperty( self._property ).equals( self._value )