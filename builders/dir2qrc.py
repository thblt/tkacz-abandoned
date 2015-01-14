#!/usr/bin/env python

#                                                                 [licblock]
# This file is part of Tkacz. 
# Copyright (c) 2012-2015 Thibault Polge. All rights reserved.
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
# 
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#                                                                [/licblock]

## @file
## @brief Reads directories and generate Qt QRC files pointing to their contents, 
# using subdirectories as prefixes and filenames without extensions as aliases.

import os, sys

def mkalias( name ):
	name = os.path.split( name )[1]
	if name.startswith( "." ): return False
	return os.path.splitext( name )[0]

def dir2qrc( root, qrc, aliaser=mkalias ):
	'''
	Creates a Qt QRC files out of resources in dir
	:param root: The directory to take files from.
	:type root: str
	:param qrc: The QRC file to write. This must be the name of the file, and not a file object.
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
					raise( Exception( "Prefix nesting not allowed: {0}.".format( absFile2 ) ) )
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
		name = os.path.split( sys.argv[0] )[-1]
		print( "Creates Qt QRC files from file filesystem resources.\n" )
		print( "Usage:" )
		print( "\t{0} directory qrc".format( name ) )
		print( "\t{0} -multi target_dir source_directory [source_directory...]\n".format( name ) )
		print( "Options:" )
		print( "-multi\tCreates a QRC file for every subdirectory of dir,\n" +
		"\tgiving the directory's name with a .qrc extension. With this\n" +
		"          option, QRC files are created at the directory's root" )
		exit( -1 )
	if sys.argv[1] == '-multi':
		for input in sys.argv[3:]:
			for dir in os.listdir( input ):
				path = os.path.join( input, dir )
				absPath = os.path.abspath( path )
				if os.path.isdir( absPath ):
					dir2qrc( absPath, os.path.join( sys.argv[2], os.path.split( path )[1] + ".qrc" ) )
