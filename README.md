Tkacz
=====

**Tkacz is unstable, unfinished software. There is nothing working actually, and the notes below refer to the project and no to the actual software**

The Tkacz project is described (in French) on my [personal website](thb.lt/projects/tkacz.html).

Random notes on building
------------------------

### Cmake invocation

On OSX with Python3.4 installed:

~~~bash
mkdir build
cd build
cmake .. -DPYTHON_INCLUDE_DIR=/Library/Frameworks/Python.framework/Versions/3.4/include/ -DPYTHON_LIBRARY=/Library/Frameworks/Python.framework/Versions/3.4/lib/libpython3.4m.dylib
~~~