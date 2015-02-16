cmake_minimum_required (VERSION 2.8.11)
project (Tkacz)

set (Tkacz_VERSION_MAJOR 0)
set (Tkacz_VERSION_MINOR 1)
set (Tkacz_VERSION_PATCH 0)
set (Tkacz_VERSION_MATURITY "Alpha")
set (Tkacz_VERSION_PREVERSION 1)
set (Tkacz_VERSION_NAME "Avogadro")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (PROJECT_SOURCE_DIR src)

configure_file (
	"${PROJECT_SOURCE_DIR}/tzbuild.h.in"
	"${PROJECT_BINARY_DIR}/tzbuild.h"
  )

include_directories (   
	"${PROJECT_SOURCE_DIR}/core" 
	"${PROJECT_SOURCE_DIR}/gui"
	"${PROJECT_SOURCE_DIR}/gui/forms"
	"${PROJECT_SOURCE_DIR}/gui/perspectives"
	"${PROJECT_BINARY_DIR}"
)
 
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/;${CMAKE_MODULE_PATH}")
  
################
# Source files #
################

# Core Lib

file(
        GLOB_RECURSE
        LibTkacz_SOURCES
        ${PROJECT_SOURCE_DIR}/core/*.cpp
)

file(
        GLOB_RECURSE
        LibTkacz_INCLUDES
        ${PROJECT_SOURCE_DIR}/core/*.hpp
)

# CLI

file(
        GLOB_RECURSE
        CLI_SOURCES
        ${PROJECT_SOURCE_DIR}/cli/*.cpp
)

file(
        GLOB_RECURSE
        CLI_INCLUDES
        ${PROJECT_SOURCE_DIR}/cli/*.hpp
)

file(
        GLOB_RECURSE
        GUI_SOURCES
        ${PROJECT_SOURCE_DIR}/gui/*.cpp
)

file(
        GLOB_RECURSE
        GUI_INCLUDES
        ${PROJECT_SOURCE_DIR}/gui/*.hpp
)

file(
        GLOB_RECURSE
        GUI_FORMS
        uidata/ui/*.ui
)

file(
        GLOB_RECURSE
        GUI_RESOURCES
        *.qrc
)

file(
        GLOB_RECURSE
        GUI_HEADERS_MOC
        ${PROJECT_SOURCE_DIR}/gui/forms/*.hpp
)

####################
# Libraries        #
####################

# Boost
# -----
IF(APPLE)
	set(Boost_USE_STATIC_LIBS ON)
ELSE()
    set(Boost_USE_STATIC_LIBS OFF)
ENDIF()

set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost COMPONENTS system filesystem log python python3 program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

# LibGit2
# -------
find_package(LibGit2 REQUIRED)
include_directories(${LIBGIT2_INCLUDE_DIR})

# Python
# ------

set(PythonLibs_FIND_VERSION 3.0)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Qt
# --

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

####################
# Targets          #
####################

# Library
# -------

add_library(LibTkacz SHARED ${LibTkacz_SOURCES} ${LibTkacz_INCLUDES})

target_link_libraries(LibTkacz ${PYTHON_LIBRARIES})
target_link_libraries(LibTkacz ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_PYTHON_LIBRARY} ${Boost_PYTHON3_LIBRARY}) 
target_link_libraries(LibTkacz ${LIBGIT2_LIBRARIES})
target_link_libraries(LibTkacz ${EXPAT_LIBRARY} )

SET_TARGET_PROPERTIES(LibTkacz PROPERTIES OUTPUT_NAME "tkacz")

# CLI Executable
# --------------

set( CLI_SOURCES ${CLI_SOURCES} ${CLI_INCLUDES} )

ADD_EXECUTABLE(CLI ${CLI_SOURCES})

target_link_libraries( CLI ${Boost_FILESYSTEM_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} ) 

SET_TARGET_PROPERTIES(CLI PROPERTIES OUTPUT_NAME "tkacz")
target_link_libraries(CLI LibTkacz)

# GUI Executable
# --------------

QT5_WRAP_UI(GUI_FORMS_HEADERS ${GUI_FORMS})
QT5_WRAP_CPP(GUI_HEADERS_MOC ${GUI_HEADERS_MOC})
QT5_ADD_RESOURCES(GUI_RESOURCES_RCC ${GUI_RESOURCES})

SET(GUI_SOURCES ${GUI_SOURCES} ${GUI_FORMS_HEADERS} ${GUI_RESOURCES_RCC} ${GUI_HEADERS_MOC})

IF(APPLE)
    set(CMAKE_INSTALL_PREFIX "." )
    SET(GUI_SOURCES ${GUI_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/icons/Tkacz.icns)
    SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/icons/Tkacz.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    SET(MACOSX_BUNDLE_ICON_FILE Tkacz.icns)
    
    # copy schemas in bundle
    # @fixme potentially buggy…
    # file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/schema/ DESTINATION Tkacz.app/Contents/Resources/schema)
    
    # Link to CoreFoundation
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework CoreFoundation")

ADD_EXECUTABLE(GUI MACOSX_BUNDLE ${GUI_SOURCES}) # This must be invoked last, or else icon/bundle name won't be set correctly
ELSE(APPLE)
	ADD_EXECUTABLE(GUI ${GUI_SOURCES})
ENDIF(APPLE)

target_link_libraries( GUI ${Boost_FILESYSTEM_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} ) 

SET_TARGET_PROPERTIES(GUI PROPERTIES OUTPUT_NAME "Tkacz")
target_link_libraries(GUI LibTkacz)
TARGET_LINK_LIBRARIES(GUI ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} )

########
# Misc #
########

# Linker
# ------

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -dead_strip -order-file")
endif()