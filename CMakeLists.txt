cmake_minimum_required (VERSION 2.8.11)
project (Tkacz)

set (Tkacz_VERSION_MAJOR 0)
set (Tkacz_VERSION_MINOR 1)
set (Tkacz_VERSION_PATCH 0)
set (Tkacz_VERSION_MATURITY "Alpha")
set (Tkacz_VERSION_NAME "Avogadro")

set ( PROJECT_SOURCE_DIR src ) 

set(CMAKE_CXX_FLAGS                "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

include_directories ( "${PROJECT_SOURCE_DIR}/gui" ,
"${PROJECT_SOURCE_DIR}/gui/_intermediates" ,
"${PROJECT_SOURCE_DIR}/core" ,
"${PROJECT_SOURCE_DIR}/core/entities" ,
"${PROJECT_SOURCE_DIR}/core/io" ,
"${PROJECT_SOURCE_DIR}/core/schemas"
)
 
configure_file (
  "${PROJECT_SOURCE_DIR}/TZGlobals.h.in"
  "${PROJECT_BINARY_DIR}/TZGlobals.h"
  )

file(
        GLOB_RECURSE
        source_files
        ${PROJECT_SOURCE_DIR}/*
)

IF(APPLE)
    set(CMAKE_INSTALL_PREFIX . )
    # set how it shows up in the Info.plist file
    SET(MACOSX_BUNDLE_ICON_FILE app.icns) 
    # set where in the bundle to put the icns file
    SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/platform/osx/app.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    # include the icns file in the target
    SET(source_files ${source_files} ${CMAKE_CURRENT_SOURCE_DIR}/platform/osx/app.icns)
ENDIF(APPLE)    

SET(MACOSX_BUNDLE_BUNDLE_NAME Tkacz)
ADD_EXECUTABLE(Tkacz MACOSX_BUNDLE ${source_files})

include_directories("${PROJECT_BINARY_DIR}")

###### Modules ######

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/;${CMAKE_MODULE_PATH}")

####################
# Qt               #
####################

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

foreach(_USE_FILE ${Qt5_USE_FILES})
    include(${_USE_FILE})
endforeach()

target_link_libraries(Tkacz Qt5::Gui Qt5::Widgets Qt5::Core )

####################
# Boost            #
####################
# No need to ask for format (include only lib)

IF(APPLE)
    set(Boost_USE_STATIC_LIBS ON) 
ELSE()
    set(Boost_USE_STATIC_LIBS OFF) 
ENDIF()
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries(Tkacz ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

####################
# Xerces           #
####################

find_package(XercesC REQUIRED)

####################
# MongoDB          #
####################

find_package(MongoDB REQUIRED)

include_directories(${MongoDB_INCLUDE_DIR})
target_link_libraries(Tkacz ${MongoDB_LIBRARIES})
 
####################
# Install          #
####################

INSTALL(TARGETS Tkacz 
    BUNDLE DESTINATION . COMPONENT Runtime 
    RUNTIME DESTINATION bin COMPONENT Runtime
    )
