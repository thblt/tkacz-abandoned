cache()

CONFIG += debug_and_release qt c++11  
QT += gui widgets core
ICON = platform/osx/app.icns

release:DESTDIR = build/release
debug:DESTDIR = build/debug

#OBJECTS_DIR = $$DESTDIR/intermediates
#MOC_DIR = $$DESTDIR/intermediates
#RCC_DIR = $$DESTDIR/intermediates
#UI_DIR = $$DESTDIR/intermediates

#debug: INCLUDEPATH+=/usr/local/include
#release: INCLUDEPATH+=/usr/local/include

include("Tkacz.pri")