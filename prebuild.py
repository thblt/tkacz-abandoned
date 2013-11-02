#!/usr/bin/env python
# -*- coding: utf-8 -*-
from subprocess import call
from os import sys, path
import re, os, sys

def run(args, announce=None):
	command = path.split(args[0])[1]
	if announce:
		sys.stdout.write("{0}".format(announce))
	else:
		sys.stdout.write("Running {0}: ".format(command))
	try:
		ret = call(args)
	except Exception as e:
		print("Failed.\nTrying to run {0} raised an {1}:".format(command, e.__class__.__name__))
		print(e)
		print("Full command line was:\n{0}".format(' '.join(args)))
		exit(-1)
	
	if ret:
		print("Failed.\n{0} exited with error {1}".format(command, ret))
		print("Full command line was:\n{0}".format(' '.join(args)))
		exit(ret)
	print ("Done.")

 ## ########################################### ##
## ############ Where it all begins ############ ##   
 ## ########################################### ##

print("Hai! I iz teh dirty Tkacz builder. I iz a sekret!\n")

#=======================================================================================================================
# Start here
#=======================================================================================================================


run(["builders/dir2qrc.py", '-multi', 'resources/qrc'], "Assembling QRC files: ")

run(["qmake", "-project", "-o", "Tkacz.pri"])

# This is dirty, but we can't just append the template to the generated file, because
# we need our directives to come first.
# with open("Tkacz.pro", 'a') as out:
# 	with open("tkacz.pro.tpl", 'r') as in_:
# 		for line in in_:
# 			out.write(line)
		
print("\nAll done, seemingly successfully.")
print("Now run qmake")