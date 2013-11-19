#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, os;

# begin and end markers for license blocks. Used when updating.
marks = ("tzlb", "/tzlb")

# Comment templates py language types. Tuple : first line, intermediate lines, last line. 
templates = dict();
templates["c"] = ("/*", " *", " */")
templates["py"] = (None, "#", None)
templates["xml"] = ("<!--", "", "-->")

# Mapping file extensions to templates.
extensions = {
              "c": "c", 
              "h":"c",
              "in":"c", # Lots of prayers over this one.  
              "cpp":"c",
              "cxx":"c",
              "hpp":"c",
              "py":"py",
              "htm":"xml",
              "html":"xml",
              "xhtml":"xml",
              "xml":"xml",
              "ui":"xml",
              }

def usage(cmdName):
    print("Usage:\n\t{0} license file […file]\n".format(cmdName))
    print("Options:")
    print("\tlicense\tThe license text to insert.")
    print("\tfile\tThe files to process. If the given file is a directory,\n\t\tit will be search recursively.")

def do(f):
    if os.path.isdir(f):
        for g in [os.path.join(f, x) for x in os.listdir(f)]:
            do(g)
    else:
        ext = os.path.splitext(f)[1][1:]
        if ext in extensions.keys():
            template = templates[extensions[ext]]
            print("Processing\t{0} ({1} file).".format(f, extensions[ext]))
        else: 
            print("Skipping\t{0} (bad extension '{1}').".format(f, ext))
            

if __name__ == "__main__":
    if len(sys.argv) < 3:
        usage(sys.argv[0])
        exit(-1)
        
    license = ""
    with open(sys.argv[1], 'r') as licFile:
        line = licFile.readline()
        while (line):
            license+=line
            line = licFile.readline()
        
    for f in sys.argv[2:]:
        do(f)