#!/usr/bin/env python

import os, sys

def mkalias(name):
	name = os.path.split(name)[1]
	if name.startswith("."): return False
	return os.path.splitext(name)[0]

def dir2qrc( root, qrc, aliaser=mkalias ):
	'''
	Creates a Qt QRC files out of resources in dir
	:param root: The directory to take files from.
	:type root: str
	:param qrc: The file to write QRC XML. This must be the name of the file, and not a file object.
	:type qrc: string
	:param aliaser: A function to call for each file to calculate its alias. The default simply returns the file name without extension. If the method returns False, Null or an empty string, the file is ignored. 
	:type aliaser function
	'''

	if not os.path.isdir( root ):
		raise( Exception( "Can't read from {0}".format( root ) ) )

	root = os.path.abspath( root )
	qrcpath = os.path.abspath( qrc )
	qrc = open( qrc, 'w' )

	qrc.write( "<RCC>\n" )
	for file1 in os.listdir( root ):
		absFile1 = os.path.join( root, file1 )
		# Subdir
		if os.path.isdir( absFile1 ):
			qrc.write( "\t<qresource prefix=\"{0}\">\n".format( file1 ) )
			# There's no need to go recursive here, as Qt doesn't handle nested prefixes.
			for file2 in os.listdir( absFile1 ):
				absFile2 = os.path.join( absFile1, file2 )
				if os.path.isdir( absFile2 ):
					raise( Exception( "Nesting not allowed: ".format( absFile2 ) ) )
				alias = aliaser( absFile2 )
				if alias: qrc.write( "\t\t<file alias=\"{alias}\">{file}</file>\n".format( alias=alias, file=absFile2 ) )
			qrc.write( "\t</qresource>\n".format( dir ) )
		# /Subdir
		else:
			alias = aliaser( absFile1 )
			if alias:
				qrc.write( "\t<file alias=\"{alias}\">{file}</file>\n".format( alias=aliaser( absFile1 ), file=absFile1 ) )
	qrc.write( "</RCC>" )
	qrc.close()

if __name__ == '__main__':
	if len( sys.argv ) < 2:
		name = path.split( sys.argv[0] )[-1]
		print( "Creates Qt QRC files from file filesystem resources.\n" )
		print( "Usage:" )
		print( "\t{0} [-multi] directory qrc".format( name ) )
		print( "\t{0} [-multi] directory [directory...]\n".format( name ) )
		print( "Options:" )
		print( "-multi\tCreates a QRC file for every subdirectory of dir,\n" +
		"\tgiving the directory's name with a .qrc extension. With this\n" +
		"          option, QRC files are created at the directory's root" )
		exit( -1 )
	if sys.argv[1] == '-multi':
		for input in sys.argv[2:]:
			for dir in os.listdir( input ):
				path = os.path.join( input, dir )
				absPath = os.path.abspath( path )
				if os.path.isdir( absPath ):
# 					print( "{0} > {1}".format( path, path + ".qrc" ) )
					dir2qrc( absPath, absPath + ".qrc" )
