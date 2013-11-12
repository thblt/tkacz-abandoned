cmake_minimum_required (VERSION 2.8.11)
project (Tkacz)

set (Tkacz_VERSION_MAJOR 0)
set (Tkacz_VERSION_MINOR 1)
set (Tkacz_VERSION_RELEASE 0)
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
  "${PROJECT_SOURCE_DIR}/TZBuildConfig.h.in"
  "${PROJECT_BINARY_DIR}/TZBuildConfig.h"
  )

file(
        GLOB_RECURSE
        source_files
        ${PROJECT_SOURCE_DIR}/*
)

SET(MACOSX_BUNDLE_BUNDLE_NAME Tkacz)
ADD_EXECUTABLE(Tkacz MACOSX_BUNDLE ${source_files})

include_directories("${PROJECT_BINARY_DIR}")

####################
# Qt               #
####################

FIND_PACKAGE(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

foreach(_USE_FILE ${Qt5_USE_FILES})
    include(${_USE_FILE})
endforeach()

target_link_libraries(Tkacz Qt5::Gui Qt5::Widgets Qt5::Core )

####################
# Boost            #
####################

IF(APPLE)
    set(Boost_USE_STATIC_LIBS ON) 
ELSE()
    set(Boost_USE_STATIC_LIBS OFF) 
ENDIF()
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE(Boost COMPONENTS system filesystem REQUIRED )

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries(Tkacz ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

####################
# Xerces           #
####################

#FIND_PACKAGE(Xerces REQUIRED)
 
####################
# OSX bundle       #
####################

IF(APPLE)
    set(CMAKE_INSTALL_PREFIX . )
    # TODO Invoke macdeployqt
ENDIF(APPLE)

####################
# Install          #
####################

# Install the Tkacz application, on Apple, the bundle is at the root of the
# install tree, and on other platforms it'll go into the bin directory.
INSTALL(TARGETS Tkacz 
    BUNDLE DESTINATION . COMPONENT Runtime 
    RUNTIME DESTINATION bin COMPONENT Runtime
    )
