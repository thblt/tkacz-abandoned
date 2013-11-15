#!/usr/bin/env python
# ! -*- coding: utf-8 -*-

""" A very rudimentary generator for C++ code """

import xml.sax as sax
import sys, os, time, socket
import codecs

def camelCase( strings, initCaps=False ):
	if initCaps:
		initial = strings[0][0].upper() + strings[0][1:].lower()
	else:
		initial = strings[0].lower()

	ret = [x[0].upper() + x[1:].lower() for x in strings[1:]]
	ret.insert( 0, initial )
	return ''.join( ret )

class Template( object ):
	_code = None
	_blocks = None
	_includes = None
	_indentLevel = None
	_inputFiles = None

	def __init__( self ):
		self._indentLevel = 0
		self._includes = set()
		self._code = list()
		self._inputFiles = list()
		self._blocks = list()

	def addInclude( self, inc ):
			self._includes.add( inc )

	def beginBlock( self, block ):
		self._appendLine()
		self._appendLine( block + " {" )
		self._blocks.append( block )
		self._indentLevel += 1

	def endBlock( self ):
		assert self._indentLevel > 0
		self._indentLevel -= 1
		self._appendLine( "}}; /* {0} */".format( self._blocks.pop() ) )

	def _appendLines( self, lines ):
		self._code.extend( ['\t' * self._indentLevel + l for l in lines] )

	def appendLines( self, lines ):
		self._appendLines(lines)

	def _appendLine( self, line="" ):
		self._appendLines( line.split( "\n" ) )

	def appendLine( self, line="" ):
		self._appendLine( line )

	def addInputFile( self, path ):
		self._inputFiles.append( path )

	def _mkInputList( self ):
		code = list()

		for f in self._inputFiles:
			code.append( "// - {0}".format( f ) )
		code.append ( "*/" )

		return code;

	def lines( self ):
		assert not( self._indentLevel )
		return ( self._code )

	def __str__( self ):
		return "\n".join( self._code )

	def write( self, file_ ):
		file_.write( str( self ) )

class CPPBase( Template ):
	def beginFunction( self, returns, name, parameters=None ):
		assert type( name ) is str

		params = list()

		if parameters:
			assert type( parameters ) is dict
			for ptype, pname in parameters.items():
					if type( pname ) is str:
						params.append( "{0} {1}".format( ptype, pname) )
					else:  # We have a default value.
						assert ( type ( pname ) is tuple or type( pname ) is list ) and len( pname ) == 2
						params.append( "{0} {1}={2}".format( ptype, pname[0], pname[1] ) )

		self.beginBlock( "{0} {1} ({2})".format( returns, name, ", ".join( params ) ) )

	def endFunction( self ):
		return self.endBlock()

class CPPClass( CPPBase ):
	UNQUALIFIED = 0
	PUBLIC = 1
	PROTECTED = 2
	PRIVATE = 3

	_name = None
	_super = None

	_cppfile = None

	_methods = None
	_attributes = None

	_methStack = None

	def addAttribute( self, declaration, access=UNQUALIFIED ):
		self._attributes[access].appendLine( declaration ) 

	def beginMethod( self, returns, name, parameters=None, access=UNQUALIFIED ):
		self._methods[access].beginFunction( returns, name, parameters )
		self._methStack.append( access )

	def endMethod( self ):
		self._methods[self._methStack.pop()].endFunction()

	def appendLine( self, line="" ):
		self._methods[self._methStack[-1]].appendLine( line )

	def appendLines( self, lines ):
		self._methods[self._methStack[-1]].appendLines( lines )

	def lines( self ):

		if self._super:
			self.beginBlock( "class {name} : {ancestors}".format( name=self._name, ancestors=",".join( self._super ) ) )
		else:
			self.beginBlock( "class {name}".format( name=self._name ) )

		for i in range( 0, 3 ):
			if not ( self._methods[i].lines() or self._attributes[i].lines() ):
				continue
			if i:
				self._appendLine( ( "public:", "protected:", "private:" )[i - 1] )

			self._appendLines( self._attributes[i].lines() )
			self._appendLines( self._methods[i].lines() )

		self.endBlock()
		
		return self._code

	def __init__( self, name, super=() ):
		CPPBase.__init__( self )
		self._name = name
		self._super = super
		
		self._methods = dict()
		self._attributes = dict()
		for i in range( 0, 3 ):
			self._methods[i] = CPPBase()
			self._attributes[i] = Template()

		self._methStack = list()
		self._attrStack = list()

class CPPFile( CPPBase ):
	_classes = None
	_functions = None
	_namespace = None
	_inputFiles = None

	def __init__( self, namespace=None ):
		CPPBase.__init__( self )
		self._namespace = namespace
		self._classes = list()
		self._functions = Template()
		self._inputFiles = list()

	def addClass( self, clazz ):
		self._classes.append( clazz )

	def mkClass( self, name, super=() ):
		c = CPPClass( name, super )
		self.addClass( c )
		return c

	def lines( self ):
		code = list()
		later = list()

		self.appendLines( ( "/************************************",
		" * /!\ GENERATED FILE - DO NOT EDIT *",
		"*************************************",
		"Generated {0} by {1}@{2} from:".format( time.asctime(), os.getlogin(), socket.gethostname() ) ) )

		inF = self._inputFiles
		for c in self._classes:
			inF.extend( c._inputFiles )
		for f in inF:
			self.appendLine( " - {0}".format( f ) )
		self.appendLine ( "*/" )

		if self._includes:
			self.appendLine( "" )
			inc = list()
			inc.extend(self._includes)
			inc.sort()
			for im in inc:
				if im.lower().endswith( ".h" ) or im.lower().endswith( ".hpp" ):
					later.append( '#include "{0}"'.format( im ) )
				else:
					self.appendLine( '#include <{0}>'.format( im ) )

			if len( later ):
				self.appendLine(  )
				self.appendLines( later )

		if self._namespace:
			self.beginBlock( "namespace {0}".format( self._namespace ) )

		self.appendLines( self._functions.lines() )
		for c in self._classes:
			self.appendLines( c.lines() )

		if self._namespace:
			self.endBlock( )	

		return self._code

class AbstractCompiler( sax.ContentHandler ):
	_input = None
	_output = None

	_stateDependantProperties = dict()  # These two dictionaries are shared by all compilers,
	_stateChangingSignals = dict()  # they get populated by Menus and Actions compilers, then

	def addStatePropertySetter( self, state, target, propName ):
		if not target in self._stateDependantProperties.keys():
			self._stateDependantProperties[target] = set()

		self._stateDependantProperties[target].add( ( state, propName ) )

	def addStateChangingSignal( self, obj, signal, state ):
		if not state in self._stateChangingSignals.keys():
			self._stateChangingSignals[state] = set()

		self._stateChangingSignals[state].add( ( obj, signal ) )

	def run( self ):
		sax.parse( self._input, self )
		return True

	def __init__( self, xml, output ):
		sax.ContentHandler.__init__( self )
		self._input = xml
		self._output = output
		output.addInputFile( xml )
if __name__ == "__main__":
	sys.stderr.write( "This library file can't be invoked directly.\n" )
	exit( 1 )
