cache()

CONFIG += qt c++11
QT += core widgets
ICON = platform/osx/app.icns

release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/qrc
UI_DIR = $$DESTDIR/ui

include("Tkacz.pri")

debug: INCLUDEPATH=/usr/local/include