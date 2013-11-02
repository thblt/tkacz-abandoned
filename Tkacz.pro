cache()

CONFIG += qt c++11  
QT += gui widgets core
ICON = platform/osx/app.icns

release:DESTDIR = build/release
debug:DESTDIR = build/debug

#OBJECTS_DIR = $$DESTDIR/obj
#MOC_DIR = $$DESTDIR/moc
#RCC_DIR = $$DESTDIR/rcc
#UI_DIR = $$DESTDIR/ui

#debug: INCLUDEPATH+=/usr/local/include
#release: INCLUDEPATH+=/usr/local/include

include("Tkacz.pri")