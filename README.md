Tkacz
=====

**Tkacz is unstable, unfinished software. There is nothing working actually, and the notes below refer to the project and no to the actual software**

Tkacz provides an environement for structured note-taking and organization of factual data.

Building
--------

Tkacz depends on:

 * Boost (tested with 1.54) 
 * CMake (tested with 2.8.12.1)
 * Qt 5.2 (tested with 5.2.0)
 * XercesC (tested with 3.1.1)

For an out-of-source build, first create a build directory in the root of the source package:

    mkdir build 
    cd build

Generate intermediate files:

    ../builders/tzuic.py ../xml ../src/gui/Base_MainWindow.hpp
    ../builders/dir2qrc.py -multi . ../qrc   
    
Then invoke

    cmake ..  
    
If cmake can't find some library, export the needed environement variables before trying again. Refer to cmake output for the name of these variables.

Then run 

    make  
    
To create a MacOS X bundle, just execute 

    macdeployqt Tkacz.app  
    
then manually move the full bundle to `/Applications/`. for other platforms, just:

    sudo make install  
    
Report bugs to [https://github.com/thblt/tkacz/issues](<https://github.com/thblt/tkacz/issues>).

Code organization
-----------------

All C++ source code is in `src/`, and furthermore divided in `core/` and `gui/`, and defines the two namespaces `tkacz` and `tkacz::gui`. The general rule of division is :

-   `Core` provides a general interface for the Tkacz data framework. It provides classes for reading, writing, searching, editing and modifying data.

-   `Gui` handles representation of `core` operations. `Gui` shouldn’t provide data-level operations, but be a simple accessor for `core` functions. It fundamentally depends on `core`.

-   `Core` is totally autonomous and depends on neither `gui` code nor the Qt framework or any other UI framework, and doesn’t know about the `tkacz::gui` namespace.

-   `Core` doesn’t provide any other interface than its C++ headers. It is designed as a static library, and may be modified to become a dynamic library if needed. Other interfaces (such as a web service interface, etc.) must be implemented separately, alongside with `gui` and `core`, on their own namespace (ie, `tkacz::rest`).
