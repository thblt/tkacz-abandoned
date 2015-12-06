from subprocess import call
from os import sys, path
import re, os, sys

def run(args, announce=None):
	command = path.split(args[0])[1]
	if announce:
		sys.stdout.write("{0}: {1}".format(command, announce))
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

def buildUIs(root="./ui", path=""):
	for f in os.listdir(os.path.join(root, path)):
		fullpath = os.path.join(root, path, f)
		if os.path.isdir(fullpath) and f != ".git" :
			buildUIs(root, os.path.join(path, f))
		else:
			name, ext = os.path.splitext(f)
			if ext==".ui":
				
				outPath = os.path.join("src/tkacz/gui/uibase", path)

				out = os.path.join(outPath, ("_{0}.py".format(name)))
				if not (os.path.exists(out)) or os.path.getmtime(fullpath) > os.path.getmtime(out):
					ann =  ("{0} => {1}: ".format(f, os.path.split(out)[1]))
					run(["pyuic4", "-w", "--from-imports", "--indent", "0", "-o", out, fullpath], ann)

 ## ########################################### ##
## ############ Where it all begins ############ ##   
 ## ########################################### ##

print(
"""         88
  ,d     88
  88     88
MM88MMM  88   ,d8   ,adPPYYba,   ,adPPYba,  888888888  
  88     88 ,a8\"    \"\"     `Y8  a8\"     \"\"       a8P\"  
  88     8888[      ,adPPPPP88  8b            ,d8P'
  88,    88`\"Yba,   88,    ,88  \"8a,   ,aa  ,d8\"
  \"Y888  88   `Y8a  `\"8bbdP\"Y8   `\"Ybbd8\"'  888888888  """)
# http://patorjk.com/software/taag/#p=display&f=Univers&t=tkacz

print("Hai! I iz teh dirty Tkacz builder. I iz a sekret!")

#=======================================================================================================================
# Start here
#=======================================================================================================================


run(["./uiLogicCompiler.py", "xml", "src/tkacz/gui/uibase/_coreLogic.py"])

sys.stdout.write("Building icons.qrc: ") ##########

qrcFile = os.path.join(os.path.split(__file__)[0], "qrc/icons.qrc")
absRoot = os.path.abspath(os.path.join(os.path.split(__file__)[0], "qrc/icons/default"))
qrc = open(qrcFile, 'w')
qrc.write("<RCC>\n")
iconsRoot = "icons/default"
for dir in os.listdir(absRoot):
	if (not dir.startswith(".")) and os.path.isdir(os.path.join(absRoot, dir)):
		qrc.write("\t<qresource prefix=\"{0}\">\n".format(dir))
		for file in os.listdir(os.path.join(absRoot, dir)):
			if (not file.startswith(".")) and os.path.isfile(os.path.join(absRoot, dir, file)):
				alias = os.path.splitext(file)[0]
				qrc.write("\t\t<file alias=\"{alias}\">{file}</file>\n".format(alias=alias, dir=dir, file=os.path.join(iconsRoot, dir, file)))
		qrc.write("\t</qresource>\n".format(dir))
qrc.write("</RCC>")
qrc.close()
print("Done.")

run(["pyrcc4", "-py3", qrcFile, "-o", "src/tkacz/gui/uibase/icons_rc.py"])
	
run(["pyrcc4", "-py3", "qrc/common.qrc", "-o", "src/tkacz/gui/uibase/common_rc.py"])

buildUIs()

run(["pylupdate4", "tkacz.pro"])
run(["lrelease", "tkacz.pro"])

print("All done, seemingly successfully.")

if "--run-app" in sys.argv:
	print("Now I'll run Tkacz.")
	#@FIXME Will work only from within an IDE: Add ./src to Pythonpath
	import Tkacz