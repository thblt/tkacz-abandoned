#!/usr/bin/env python3

import xml.sax as sax
import sys, os, time, socket
from thblt.strings import camelCase

""" 
This module will read three files, actions.xml, menus.xml and states.xml and outputs a 
python file with a single function, insertCoreLogic(target) which will append actions
objects in a hierarchical tree, creates a menubar and a QStateMachine in the target object.
Target is expected to be a QMainWindow will the action store method as defined in the 
tkacz.gui.mainwindow.MainWindow class.
"""

disambiguationString = "Core actions and menus (generated from XML)"

class Template( object ):
	# This is random garbage, used by beginFunction()
	NO_DEFAULT_VALUE = "__tz__methodParameterHasNoDefaultValue__9873494987957484__"

	_imports = None
	_code = None
	_inputFiles = None

	_indentLevel = None

	def __init__( self ):
		self._indentLevel = 0
		self._imports = dict()
		self._code = list()
		self._inputFiles = list()

	def addInputFile( self, path ):
		self._inputFiles.append( path )

	def addImport( self, what, importFrom=None ):
		if not importFrom in self._imports.keys():
			self._imports[importFrom] = set()
		self._imports[importFrom].update( what )

	def beginBlock( self, block ):
		self.appendLine( block )
		self._indentLevel += 1

	def endBlock( self ):
		assert self._indentLevel > 0
		self._indentLevel -= 1

	def beginFunction( self, name, parameters=None, args=False, kwargs=False ):
		assert type( name ) is str

		params = list()

		if parameters:
			assert type( parameters ) is dict
			for pname, defval in parameters.items():
				if defval != self.NO_DEFAULT_VALUE:
					params.append( "{0}={1}".format( pname, defval ) )
				else: params.append( pname )

		if args:
			params.append( "*args" )
		if kwargs:
			params.append( "**kwargs" )

		self.beginBlock( "def {0} ({1}):".format( name, ", ".join( params ) ) )

	def endFunction( self ):
		return self.endBlock()

	def appendLine( self, line="" ):
		lines = line.split( '\n' )
		for line in lines:
			self._code.append( '\t' * self._indentLevel + line )

	def __str__( self ):
		assert not( self._indentLevel )

		code = list()

		code.append( "########################################################" )
		code.append( "# /!\ ANY CHANGE MADE TO THIS FILE WILL BE LOST (SOON) #" )
		code.append( "# ---------------------------------------------------- #" )
		code.append( "# Edit XML files in TKACZ_SRC/xml/ instead; and see	#" )
		code.append( "# logicCompiler.py for more information.			   #" )
		code.append( "########################################################" )
		code.append( "# Generated {0} by {1}@{2}.".format( time.asctime(), os.getlogin(), socket.gethostname() ) )
		code.append( '' )

		for fr, im in self._imports.items():
			if fr:
				code.append( "from {fr} import {im}".format( fr=fr, im=', '.join( im ) ) )
			else:
				code.append( "import {im}".format( im=im ) )


		return ( "\n".join( code + self._code ) )

	def write( self, file_ ):
		file_.write( str( self ) )

class AbstractCompiler( sax.ContentHandler ):
	_input = None
	_output = None

	_stateDependantProperties = dict()  # These two dictionaries are shared by all compilers,
	_stateChangingSignals = dict()  # they get populated by Menus and Actions compilers, then
	# used by StateCompiler to generate transitions and properties setting.
	# _stateDependantProperties[objectName] = set(tuple(stateName, propertyName))
	# _stateChangingSignals[stateName] = set(tuple(objectName, signalIdentifier))

	def addStatePropertySetter( self, state, target, propName ):
		if not target in self._stateDependantProperties.keys():
			self._stateDependantProperties[target] = set()

		self._stateDependantProperties[target].add( ( state, propName ) )

	def addStateChangingSignal( self, obj, signal, state ):
		if not state in self._stateChangingSignals.keys():
			self._stateChangingSignals[state] = set()

		self._stateChangingSignals[state].add( ( obj, signal ) )

	def run( self ):
		line = "# {0}: {1}".format( self.__class__.__name__, self._input )
		self._output.appendLine()
		self._output.appendLine( line )
		self._output.appendLine( '# ' + '#' * ( len( line ) - 2 ) )
		self._output.appendLine()

		sax.parse( self._input, self )
		return True

	def __init__( self, xml, output ):
		sax.ContentHandler.__init__( self )
		self._input = xml
		self._output = output
		out.addInputFile( xml )

class StatesCompiler( AbstractCompiler ):

	_parent = None
	_states = None

	class State():
		root = False
		name = None
		children = None
		parallel = False
		parent = None

		def addChild( self, c ):
			self.children.add( c )
			c.parent = self

		def getChild( self, name ):
			for c in self.children:
				if c.name == name:
					return c
			return None

		def getChildren( self, excludes=[] ):
			return [x for x in self.children if not x in excludes]

		def allParents( self ):
			""" Returns a set containing this State's parent hierarchy members, ie all its
			ancestors up to root (excluded) """
			ret = set()
			p = self.parent
			while not p.root:
				ret.add( p )
				p = p.parent
			return ret

		def __init__( self, name, parallel=False, root=False, parent=None ):
			self.name = name
			self.parallel = parallel
			self.root = root
			self.parent = parent
			self.children = set()

		def __repr__( self ):
			return "<{0}: {1}>".format( self.__class__.__name__, str( self ) )

		def __str__( self ):
			point = self
			hierarchy = list()
			while not point.root:
				hierarchy.append( point.name )
				point = point.parent
			hierarchy.reverse()
			return ".".join( hierarchy )

		def pyName( self ):
			point = self
			hierarchy = list()
			while not point.root:
				hierarchy.append( point.name )
				point = point.parent
			hierarchy.reverse()
			if hierarchy:
				return camelCase( ['state'] + hierarchy )
			else: return self.name

		def asciiDump( self, depth=0 ):
			ret = list()
			if not self.root:
				ret.append( '# ' + '  ' * ( depth - 1 ) + ( " + " if self.parent and self.parent.parallel else " - " ) + str( self ) + ( ' (parallel)' if self.parallel else ' (exclusive)' if self.children else '' ) )
			for c in self.children:
				ret.extend( c.asciiDump( depth=depth + 1 ) )
			return ret

	def addState( self, sid, parallel=False, statesDict=None ):
		if type( sid ) is str: sid = sid.split( '.' )

		state = self.State( sid[-1] )
		parent = self._states

		for point in sid[:-1]:
			parent = parent.getChild( point )

		parent.addChild( state )
		return state

	def _doFindState( self, identifier, root ):
		""" See findState(rawId) """
		ret = list()
		for st in root.children:
			if st.name == identifier[0]:
				if len( identifier ) == 1:
					ret.append( st )
				else:
					ret.extend( self._doFindState( identifier[1:], st ) )
			else:
				ret.extend( self._doFindState( identifier, st ) )
		return ret;

	def findState( self, rawId ):
		""" Finds a state in this Compiler by a name which may be only the final part
		of the state. This is meant to make it easy to modify the states tree (eg, insert
		a new global parent, etc) without having to modify every state attribute in actions 
		and menus XML files. """

		if type( rawId ) is str:
			identifier = rawId.split( '.' )
		else: identifier = rawId  # We expect an iterable.

		ret = self._doFindState( identifier, self._states )
		if len( ret ) == 0:
			raise Exception( 'No such state "{0}".'.format( rawId ) )
		if len( ret ) > 1:
			raise Exception( 'Ambiguous state identifier "{0}", matches {1}.'.format( rawId, '"' + ( ', "'.join( [str( x ) for x in ret] ) ) + '"' ) )
		return ret[0]

	def reverseStateList( self, states ):
		""" Returns the shortest list of states which are exclusive to the provided states. 
		:param states : an iterable of State objects 
		:return: a set of tuples representing the minimum set of states """
		ret = set()

		for st in states:
			point = st.parent
			while not point.root:
				if not point.parallel:
					ret.update( point.getChildren( excludes=states.union( st.allParents() ) ) )
				point = point.parent
		return ret

	def startDocument( self ):
		self._output.appendLine( "target.{smName} =  QStateMachine()".
			format( smName=self._states.pyName() ) )
		self._output.appendLine( "target.{smName}.setGlobalRestorePolicy(QStateMachine.RestoreProperties)".
			format( smName=self._states.pyName() ) )

	def endDocument( self ):

		self._output.appendLine( "\n# Generated state hierarchy\n# -------------------------" )
		self._output.appendLine( '\n'.join( self._states.asciiDump() ) )
		self._output.appendLine( "\n# States properties setter\n" )


		for item, props in self._stateDependantProperties.items():
			properties = dict()  # properties[propName] = list(state id as tuple)

			for prop in props:
				if not prop[1] in properties.keys():
					properties[prop[1]] = set()
				properties[prop[1]].add( self.findState( prop[0] ) )

			for propertyName, statesTrue in properties.items():
# 				statesFalse = self.reverseStateList( statesTrue )

				self._output.appendLine( '{item}.set{property}( False )'
					.format
					( item=item
					, property=propertyName.capitalize()
					) )

				for st in statesTrue:
					self._output.appendLine( 
						'target.{stateName}.assignProperty({item}, "{property}", True)'.format
						( item=item
						, stateName=st.pyName()
						, property=prop[1] ) )

		self._output.appendLine( "\n# Transitions\n" )

		for state, props in self._stateChangingSignals.items():
			state = self.findState( state )

			for obj, signal in props:
				for st in self.reverseStateList( {state} ):
					self._output.appendLine( 'target.{fromState}.addTransition({object}, SIGNAL("{signal}"), target.{toState})'.format( 
						fromState=st.pyName(),
						object=obj,
						signal=signal,
						toState=state.pyName() ) )

		# print(statesProperties)
		# for item in visible:
		# 		print(item)

		self._output.appendLine( "target.{smName}.start()".format( smName=self._states.pyName() ) )

		return True

	def startElement( self, name, attrs ):
		if name == "state":
			stateId = attrs['id'].lower()
			state = self.State( name=stateId )
			self._parent.addChild( state )

			self._output.appendLine( "target.{state} = QState(target.{parent})".format( 
				state=state.pyName(),
				parent=self._parent.pyName() ) )

			self._output.appendLine( 'target.{state}.setObjectName("{name}")'.format( 
				state=state.pyName(),
				name=state ) )

			if 'parallel' in attrs.keys():
				state.parallel = True
				self._output.appendLine( "target.{state}.setChildMode(QState.ParallelStates)".
					format( state=state.pyName() ) )
			if 'initial' in attrs.keys():
				assert attrs['initial'] == 'true'
				self._output.appendLine( 'target.{parent}.setInitialState(target.{this})'.format( parent=self._parent.pyName(), this=state.pyName() ) )
			self._parent = state
		elif name == 'assign':
			self._output.appendLine( 'target.{state}.assignProperty({object}, "{property}", {value})'
					.format( state=self._parent.pyName(),
						object=attrs['object'],
						property=attrs['property'],
						value=attrs['value'] ) )

	def endElement( self, name ):
		if name == "state":
			self._parent = self._parent.parent

	def __init__( self, xml, out ):
		AbstractCompiler.__init__( self, xml, out )
		self._states = self.State( 'stateMachine', root=True )
		self._parent = self._states

class MenuCompiler( AbstractCompiler ):
	_menus = None
	_lastNumber = None

	MENU = '{menu} = mb.addMenu(target.trUtf8("{text}", "{disamb}"))'
	ACTION = '{menu}.addAction(target.action("{id}"))'
	TITLE = 'title = QAction(target.trUtf8("{text}", "{disamb}"), {menu}); title.setEnabled(False); {menu}.addAction(title);'
	SEPARATOR = '{menu}.addSeparator()'

	def startDocument( self ):
		self._output.appendLine( "mb = target.menuBar" )  # @FIXME This depends on the mainwindow design.
		self._menus.append( "mb" )

	def startElement( self, name, attrs ):

		parentMenu = self._menus[-1]

		if name == "menu":
			menuName = "menu{0}".format( self._lastNumber )
			self._menus.append( menuName )
			self._lastNumber += 1
			if 'inStates' in attrs.keys():
				for s in [x.strip() for x in attrs['inStates'].split( ',' )]:
					self.addStatePropertySetter( s, menuName + ".menuAction()", "visible" )

			self._output.appendLine( self.MENU.format( text=attrs['text'], menu=menuName, disamb=disambiguationString ) )
			parentMenu = menuName
		elif name == "action":
			self._output.appendLine( self.ACTION.format( id=attrs['id'], menu=parentMenu ) )
		elif name == "title":
			self._output.appendLine( self.TITLE.format( text=attrs['text'], menu=parentMenu, disamb=disambiguationString ) )
		elif name == "separator":
			self._output.appendLine( self.SEPARATOR.format( menu=parentMenu ) )

	def endElement( self, name ):
		if name == "menu":
			self._menus.pop()

	def __init__( self, xml, out ):
		AbstractCompiler.__init__( self, xml, out )
		self._lastNumber = 0
		self._menus = list()

class ActionsCompiler( AbstractCompiler ):

	_prefixes = None  # The stack of action prefixes
	_lastActionObjectName = None  # The name of the last created action.
	_lastActionId = None  # The id of the last created action (name without prefixes)
	stateDependantActions = None  # The action which are enabled only in certain states.
	stateChangingActions = \
	None, None, None, None, None

	stateDependantActions = None
	stateChangingActions = None

	stdShortcuts = ( "AddTab", "Back", "Bold", "Close", "Copy", "Cut", "Delete", "DeleteEndOfLine", "DeleteEndOfWord",
				"DeleteStartOfWord", "Find", "FindNext", "FindPrevious", "Forward", "HelpContents", "InsertLineSeparator",
				"InsertParagraphSeparator", "Italic", "MoveToEndOfBlock", "MoveToEndOfDocument", "MoveToEndOfLine",
				"MoveToNextChar", "MoveToNextLine", "MoveToNextPage", "MoveToNextWord", "MoveToPreviousChar",
				"MoveToPreviousLine", "MoveToPreviousPage", "MoveToPreviousWord", "MoveToStartOfBlock",
				"MoveToStartOfDocument", "MoveToStartOfLine", "New", "NextChild", "Open", "Paste", "Preferences",
				"PreviousChild", "Print", "Quit", "Redo", "Refresh", "Replace", "SaveAs", "Save", "SelectAll",
				"SelectEndOfBlock", "SelectEndOfDocument", "SelectEndOfLine", "SelectNextChar", "SelectNextLine",
				"SelectNextPage", "SelectNextWord", "SelectPreviousChar", "SelectPreviousLine", "SelectPreviousPage",
				"SelectPreviousWord", "SelectStartOfBlock", "SelectStartOfDocument", "SelectStartOfLine", "Underline",
				"Undo", "UnknownKey", "WhatsThis", "ZoomIn", "ZoomOut" )

	PREFIX_ADD = "target.registerActionPrefix(\"{id}\", target.trUtf8(\"{name}\", '{disamb}'))"
	ACTION_INIT = '{action} = QAction("{id}", target)\n{action}.setObjectName("{action}")'
	ACTION_SHORTCUT_LITT = "{action}.setShortcut(QKeySequence(target.trUtf8(\"{shortcut}\", '{disamb}')))"
	ACTION_SHORTCUT_STD = "{action}.setShortcut(QKeySequence.{shortcut})"
	ACTION_TEXT = "{action}.setText(target.trUtf8(\"{text}\", '{disamb}'))"
	ACTION_END = 'target.registerAction("{prefix}", "{name}", {action})'
	ACTION_ROLE = '{action}.setMenuRole(QAction.{role})'
	ACTION_TOGGLABLE = '{action}.setCheckable({value})'
	ICON_SIMPLE = '{action}.setIcon(QIcon(QPixmap(":/actions/{iconName}")))'

	def startElement( self, tag, attrs ):
		if tag == "prefix":
			self._prefixes.append( attrs['id'] )
			self._output.appendLine( self.PREFIX_ADD.format( id=".".join( self._prefixes ), name=attrs['name'] if 'name' in attrs.keys() else attrs['id'], disamb=disambiguationString ) )
		if tag == "action":
			path = self._prefixes + [attrs['id']]
			name = "action" + camelCase( path, True )
			self._lastActionObjectName = name
			self._lastActionId = attrs['id']
			self._output.appendLine( self.ACTION_INIT.format( action=name, id=attrs['id'], disamb=disambiguationString ) )
			if "shortcut" in attrs.keys():
				sc = attrs["shortcut"]
				if sc in self.stdShortcuts:
					self._output.appendLine( self.ACTION_SHORTCUT_STD.format( action=name, shortcut=sc, disamb=disambiguationString ) )
				else:
					self._output.appendLine( self.ACTION_SHORTCUT_LITT.format( action=name, shortcut=sc, disamb=disambiguationString ) )

			if "togglable" in attrs.keys():
				self._output.appendLine( self.ACTION_TOGGLABLE.format( action=name, value=True if attrs['togglable'] == "true" else False ) )
			if "icon" in attrs.keys():
				icon = attrs['icon']
				iconName = ''.join( [name[6:7].lower(), name[7:]] )
				if icon == "simple":
					self._output.appendLine( self.ICON_SIMPLE.format( action=name, iconName=iconName ) )
			if 'inStates' in attrs.keys():
				for s in [x.strip() for x in attrs['inStates'].split( ',' )]:
					self.addStatePropertySetter( s, name, "enabled" )
			if 'enterStates' in attrs.keys():
				for s in [x.strip() for x in attrs['enterStates'].split( ',' )]:
					self.addStateChangingSignal( name, "triggered()", s )
			if "role" in attrs.keys():
				self._output.appendLine( self.ACTION_ROLE.format( action=name, role=attrs['role'] ) )


	def endElement( self, name ):
		if name == "prefix":
			self._prefixes.pop()
		if name == "action":
			self._output.appendLine( self.ACTION_END.format( action=self._lastActionObjectName, name=self._lastActionId, prefix='.'.join( self._prefixes ), disamb=disambiguationString ) )

	def characters( self, content ):
		text = list( content.strip() )
		if not len( text ): return
		try:
			text[text.index( '_' )] = "&"
		except ValueError: pass
		self._output.appendLine( self.ACTION_TEXT.format( action=self._lastActionObjectName, text="".join( text ), disamb=disambiguationString ) )

	def __init__( self, xml, out ):
		AbstractCompiler.__init__( self, xml, out )
		self._prefixes = list()
		self.stateDependantActions = dict()
		self.stateChangingActions = dict()

def usage( error=None ):
	if error:
		print( "ERROR: " + error + "\n" )
	print( "Usage: {command} XML_DIR OUTPUT_FILE".format( command=sys.argv[0] ) )
	print( "XML_DIR	 : Path to the directory containing the XML definitions." )
	print( "OUTPUT_FILE : Path to the Python file to write." )
	exit( 1 )

out = Template()
out.addImport( {'QKeySequence', 'QIcon', 'QPixmap', 'QAction'}, 'PyQt4.QtGui' )
out.addImport( {'QState', 'QStateMachine', 'SIGNAL'}, 'PyQt4.QtCore' )

if not ( len( sys.argv ) == 3 ):
	usage()

statesXml = os.path.abspath( os.path.join( sys.argv[1], "states.xml" ) )
actionsXml = os.path.abspath( os.path.join( sys.argv[1], "actions.xml" ) )
menusXml = os.path.abspath( os.path.join( sys.argv[1], "menus.xml" ) )

try:
	pyOut = open( sys.argv[2], 'w', encoding="utf-8" )
except IOError:
	usage( 'Can\'t open "{0}" file for writing.' % sys.argv[2] )

actions = ActionsCompiler( actionsXml, out )
menus = MenuCompiler( menusXml, out )
states = StatesCompiler( statesXml, out )

out.beginFunction( "insertCoreLogic", {'target':Template.NO_DEFAULT_VALUE} )

if actions.run() & menus.run() & states.run():
	out.endFunction()
	pyOut.write( str( out ) )
	pyOut.close()
	exit( 0 )
exit( -1 )
