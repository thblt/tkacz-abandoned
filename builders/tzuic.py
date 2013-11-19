#!/usr/bin/env python
# ! -*- coding: utf-8 -*-

##
## \defgroup builders Build utilities
##

## @package tzuic
## A compiler which reads XML files and produces a MainWindow template with menus, actions
## and a state machine.

## @addtogroup builders
## @{
## @addtogroup builders 

from _classgen import *
import sys

disambiguationString = "Core actions and menus (generated from XML)"

def mkName(typeName, path):
	if type(path) is str or type(path) is unicode:
		path = path.split(".")
	return typeName + camelCase(path, True)

"""
@ingroup building
"""
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

	ACTION_DECLARE = u"QAction *{name};"
	ACTION_INIT = u'{name} = new QAction(QStringLiteral("{id}"), mainWindow);\n{name}->setObjectName("{objName}");'
	#ACTION_REGISTER = u'actionStore["{id}"] = {name};'
	ACTION_SHORTCUT_LITT = u"{action}->setShortcut(QKeySequence(mainWindow->trUtf8(\"{shortcut}\", \"{disamb}\")));"
	ACTION_SHORTCUT_STD = u"{action}->setShortcut(QKeySequence::{shortcut});"
	ACTION_TEXT = u"{action}->setText(mainWindow->trUtf8(\"{text}\", \"{disamb}\"));"
	ACTION_ROLE = u'{action}->setMenuRole(QAction::{role});'
	ACTION_TOGGLABLE = u'{action}->setCheckable({value});'
	ICON_SIMPLE = u'{action}->setIcon(QIcon(QPixmap(":/actions/{iconName}")));'

	def startDocument( self ):
		pass
		# This was a map to store actions by name.
		#self._output.addAttribute("std::unordered_map<std::string, QAction*> actionStore;", CPPClass.PUBLIC)

	def startElement( self, tag, attrs ):
		if tag == "prefix":
			self._prefixes.append( attrs['name'] )
		if tag == "action":
			path = self._prefixes + [attrs['name']]
			id = ".".join(path)
			objName = "_".join(path)
			name = mkName("action", path)
			self._lastActionObjectName = name
			self._lastActionId = attrs['name']
			self._output.addAttribute( self.ACTION_DECLARE.format( name=name ), CPPClass.PUBLIC)
			self._output.appendLine("// "+">".join(path) )
			self._output.appendLine( self.ACTION_INIT.format( name=name, objName=objName, id=name, disamb=disambiguationString ))
			#self._output.appendLine( self.ACTION_REGISTER.format( name=name, id=id ) )
			if "shortcut" in attrs.keys():
				sc = attrs["shortcut"]
				if sc in self.stdShortcuts:
					self._output.appendLine( self.ACTION_SHORTCUT_STD.format( action=name, shortcut=sc, disamb=disambiguationString ) )
				else:
					self._output.appendLine( self.ACTION_SHORTCUT_LITT.format( action=name, shortcut=sc, disamb=disambiguationString ) )

			if "togglable" in attrs.keys():
				self._output.appendLine( self.ACTION_TOGGLABLE.format( action=name, value=attrs['togglable'] ) )
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

class MenuCompiler( AbstractCompiler ):
	_menus = None
	_lastNumber = None
	_lastTitle = None

	disambiguationString = "Generated menu code"

	MENU_INSERT = "{parent}->addAction({menu}->menuAction());"
	MENU = 'QMenu* {menu} = new QMenu(mainMenu);\n{menu}->setObjectName(QStringLiteral("{menu}")); {menu}->setTitle(mainWindow->trUtf8("{title}","{disamb}"));'
	ACTION = '{menu}->addAction({id});'
	TITLE = 'QAction *title{number} = new QAction(mainWindow->trUtf8("{title}", "{disamb}"), mainWindow); title{number}->setEnabled(false); {menu}->addAction(title{number});'
	SEPARATOR = '{menu}->addSeparator();'

	def startDocument( self ):
		self._output.addAttribute("QMenuBar* mainMenu;", CPPClass.PUBLIC)
		self._output.appendLine("mainMenu = new QMenuBar(mainWindow);")
		self._menus.append( "mainMenu" )

	def startElement( self, name, attrs ):
		parentMenu = self._menus[-1]

		if name == "menu":
			menuName = "menu{0}".format( self._lastNumber )
			self._lastNumber += 1
			if 'inStates' in attrs.keys():
				for s in [x.strip() for x in attrs['inStates'].split( ',' )]:
					self.addStatePropertySetter( s, menuName + ".menuAction()", "visible" )
			
			self._output.appendLine( self.MENU.format( menu=menuName, title = attrs['title'], disamb=self.disambiguationString ) )
			self._output.appendLine(self.MENU_INSERT.format(menu = menuName, parent=self._menus[-1]))
			
			self._menus.append( menuName )
		elif name == "action":
			self._output.appendLine( self.ACTION.format( id=mkName("action", attrs['name']), menu=parentMenu ) )
		elif name == "title":
			self._output.appendLine( self.TITLE.format( number = self._lastTitle, title=attrs['title'], menu=parentMenu, disamb=self.disambiguationString ) )
			self._lastTitle += 1;
		elif name == "separator":
			self._output.appendLine( self.SEPARATOR.format( menu=parentMenu ) )

	def endElement( self, name ):
		if name == "menu":
			self._menus.pop()
			

	def __init__( self, xml, out ):
		AbstractCompiler.__init__( self, xml, out )
		self._lastNumber = 0
		self._lastTitle = 0
		self._menus = list()
		out.addInclude( "QtWidgets/QMenuBar" )

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

		def cppName( self ):
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
				ret.append( ' * ' + '  ' * ( depth - 1 ) + ( " + " if self.parent and self.parent.parallel else " - " ) + str( self ) + ( ' (parallel)' if self.parallel else ' (exclusive)' if self.children else '' ) )
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
			format( smName=self._states.cppName() ) )
		self._output.appendLine( "target.{smName}.setGlobalRestorePolicy(QStateMachine.RestoreProperties)".
			format( smName=self._states.cppName() ) )

	def endDocument( self ):

		self._output.appendLine()
		self._output.appendLine( "/* Generated state hierarchy\n * -------------------------" )
		self._output.appendLines( self._states.asciiDump() )
		self._output.appendLine( " */" )
		self._output.appendLine( "\n// States properties setter\n" )


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
						, stateName=st.cppName()
						, property=prop[1] ) )

		self._output.appendLine( "\n# Transitions\n" )

		for state, props in self._stateChangingSignals.items():
			state = self.findState( state )

			for obj, signal in props:
				for st in self.reverseStateList( {state} ):
					self._output.appendLine( 'target.{fromState}.addTransition({object}, SIGNAL("{signal}"), target.{toState})'.format( 
						fromState=st.cppName(),
						object=obj,
						signal=signal,
						toState=state.cppName() ) )

		# print(statesProperties)
		# for item in visible:
		# 		print(item)

		self._output.appendLine( "target.{smName}.start()".format( smName=self._states.cppName() ) )

		return True

	def startElement( self, name, attrs ):
		if name == "state":
			stateId = attrs['name'].lower()
			state = self.State( name=stateId )
			self._parent.addChild( state )

			self._output.appendLine( "target.{state} = QState(target.{parent})".format( 
				state=state.cppName(),
				parent=self._parent.cppName() ) )

			self._output.appendLine( 'target.{state}.setObjectName("{name}")'.format( 
				state=state.cppName(),
				name=state ) )

			if 'parallel' in attrs.keys():
				state.parallel = True
				self._output.appendLine( "target.{state}.setChildMode(QState.ParallelStates)".
					format( state=state.cppName() ) )
			if 'initial' in attrs.keys():
				assert attrs['initial'] == 'true'
				self._output.appendLine( 'target.{parent}.setInitialState(target.{this})'.format( parent=self._parent.cppName(), this=state.cppName() ) )
			self._parent = state
		elif name == 'assign':
			self._output.appendLine( 'target.{state}.assignProperty({object}, "{property}", {value})'
					.format( state=self._parent.cppName(),
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

##########################################################################################

def usage( error=None ):
	if error:
		print( "ERROR: {0}\n".format( error ) )
	print( "Usage: {command} in out".format( command=sys.argv[0] ) )
	print( "\tin\tPath to the the XML files directory." )
	print( "\tout\tPath to the .h file to generate. If exists, will be overwritten." )
	exit( 1 )

# # MAIN ##

if  len( sys.argv ) != 3 :
	usage()

xmlpath = sys.argv[1]
cpp = sys.argv[2]

try:
	out = codecs.open( sys.argv[2], 'w', encoding="utf-8" )
except IOError:
	usage( 'Can\'t open "{0}" file for writing.' % sys.argv[2] )

tpl = CPPFile("tzgui")
tpl.addInclude( "QtCore/QObject" )
tpl.addInclude( "QtCore/QString" )
tpl.addInclude( "QtCore/QVariant" )
tpl.addInclude( "QtWidgets/QAction" )
tpl.addInclude( "QtWidgets/QMenuBar" )
tpl.addInclude( "QtGui/QKeySequence" )
tpl.addInclude( "QtWidgets/QMainWindow" )

clazz = tpl.mkClass( "Base_MainWindow", [] )

clazz.beginMethod( "void", "tzSetupUi", {"QMainWindow" : "*mainWindow"}, CPPClass.PUBLIC )
compilerS = StatesCompiler( os.path.join( xmlpath, "states.xml" ), clazz )
compilerA = ActionsCompiler( os.path.join( xmlpath, "actions.xml" ), clazz )
compilerM = MenuCompiler( os.path.join( xmlpath, "menus.xml" ), clazz )

if compilerA.run() & compilerM.run(): # compilerS.run()  
	clazz.endMethod()

	out.write( "\n".join( tpl.lines() ) )
	out.close()
	exit( 0 )
exit( -1 )

