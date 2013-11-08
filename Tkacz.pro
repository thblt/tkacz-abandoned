cache()

CONFIG += qt c++11  
QT +=  widgets 
ICON = platform/osx/app.icns

DESTDIR = build

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/rcc
UI_DIR = $$DESTDIR/ui

#debug: INCLUDEPATH+=/usr/local/include
#release: INCLUDEPATH+=/usr/local/include

include("Tkacz.pri")