# Tkacz

**Tkacz is unstable, unfinished software. There is nothing working actually, and the notes below refer to the project and no to the actual software**

Tkacz provides an environement for structured note-taking.

## Building

Building Tkacz requires:

- Boost (tested with 1.54)
- CMake (tested with 2.8.12.1)
- Qt (tested with 5.2 beta 1)
- XercesC (tested with 3.1.1)

For an out-of-source build, first create a build directory in the root of the source package:

    mkdir build
    cd build

Generate intermediate files:

    ../builders/tzuic.py ../xml ../src/gui/Base_MainWindow.hpp 
    ../builders/dir2qrc.py -multi . ../resources/qrc 
    
Then invoke

    cmake ..
    
If cmake can't find some library, export the needed environement variables before trying again. Refer to cmake output for the name of these variables.

Then run 

    make
    
To create a MacOS X bundle, just execute 

    macdeployqt Tkacz.app
    
then manually move the full bundle to `/Applications/`. for other platforms, just:

    sudo make install
    
Report bugs to [https://github.com/thblt/tkacz/issues](https://github.com/thblt/tkacz/issues).