Tkacz
=====

**Tkacz is unstable, unfinished software. There is nothing working actually, and the notes below refer to the project and no to the actual software**

The Tkacz project is described (in French) on my [personal website](http://thb.lt/projects/tkacz.html).

Random notes on building
------------------------

### Cmake invocation

On OSX with Python3.4 installed:

~~~bash
mkdir build
cd build
cmake .. -DPYTHON_INCLUDE_DIR=/usr/local/Cellar/python3/3.4.2_1/Frameworks/Python.framework/Versions/3.4/include/python3.4m -DPYTHON_LIBRARY=/usr/local/Cellar/python3/3.4.2_1/Frameworks/Python.framework/Versions/3.4/lib/libpython3.4m.dylib -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt5/5.4.0/lib/cmake
~~~
