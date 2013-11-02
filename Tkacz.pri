######################################################################
# Automatically generated by qmake (3.0) sam. nov. 2 05:20:13 2013
######################################################################

TEMPLATE = app
TARGET = Tkacz
INCLUDEPATH += . \
               core \
               core/data \
               core/schema 

# Input
HEADERS += core/tkacz.h \
           core/data/primitives.h \
           core/data/taxonomies.h \
           core/data/types.h \
           core/io/DataBridge.h \
           core/schema/loader.h 
           
FORMS += resources/ui/dlgAbout.ui \
         resources/ui/dlgCollectionEditor.ui \
         resources/ui/dlgCrashReporter.ui \
         resources/ui/dlgFirstStart.ui \
         resources/ui/dlgPreferences.ui \
         resources/ui/mainWindow.ui \
         resources/ui/mwListOfEntryPoints.ui \
         resources/ui/mwLocationBar.ui \
         resources/ui/mwMainView.ui \
         resources/ui/mwPageEditor.ui \
         resources/ui/mwPagePropertiesEditor.ui \
         resources/ui/mwPagesList.ui \
         resources/ui/mwPageView.ui \
         resources/ui/mwRepositorySettingsView.ui \
         resources/ui/mwToolBarWidget.ui \
         resources/ui/propertyEditWidget.ui
SOURCES += core/tkacz.cpp \
           gui/main.cpp \
           core/data/primitives.cpp \
           core/data/taxonomies.cpp \
           core/data/types.cpp \
           core/schema/loader.cpp 
RESOURCES += resources/qrc/common.qrc resources/qrc/icons.qrc