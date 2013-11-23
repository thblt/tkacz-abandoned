cmake_minimum_required (VERSION 2.8.11)
project (Tkacz)

set (Tkacz_VERSION_MAJOR 0)
set (Tkacz_VERSION_MINOR 1)
set (Tkacz_VERSION_PATCH 0)
set (Tkacz_VERSION_MATURITY "Alpha")
set (Tkacz_VERSION_PREVERSION 1)
set (Tkacz_VERSION_NAME "Avogadro")

set ( PROJECT_SOURCE_DIR src ) 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O0 -g -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O4 -DNDEBUG -Wall -std=c++11")

include_directories (  
"${PROJECT_SOURCE_DIR}" 
"${PROJECT_SOURCE_DIR}/core" 
"${PROJECT_SOURCE_DIR}/core/entities" 
"${PROJECT_SOURCE_DIR}/core/io" 
"${PROJECT_SOURCE_DIR}/core/repositories" 
"${PROJECT_SOURCE_DIR}/core/schemas"
"${PROJECT_SOURCE_DIR}/core/schemas/loader"
"${PROJECT_SOURCE_DIR}/gui" 
"${PROJECT_SOURCE_DIR}/gui/forms"
)
 
configure_file (
  "${PROJECT_SOURCE_DIR}/tzbuild.h.in"
  "${PROJECT_BINARY_DIR}/tzbuild.h"
  )

file(
        GLOB_RECURSE
        Tkacz_SOURCES
        ${PROJECT_SOURCE_DIR}/gui/*.cpp
)

file(
        GLOB_RECURSE
        Tkacz_CORE_SOURCES
        ${PROJECT_SOURCE_DIR}/core/*.cpp
)

file(
        GLOB_RECURSE
        Tkacz_CORE_INCLUDES
        ${PROJECT_SOURCE_DIR}/core/*.hpp
)

message("***SCHEMA ${CMAKE_CURRENT_SOURCE_DIR} :::::: ${Tkacz_SCHEMA}")

IF(APPLE)
    # set(CMAKE_INSTALL_PREFIX "/Applications" )
    set(CMAKE_INSTALL_PREFIX "." )
    # set how it shows up in the Info.plist file
    SET(MACOSX_BUNDLE_ICON_FILE Tkacz.ADD_CUSTOM_COMMAND) 
    # set where in the bundle to put the icns file
    SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/Tkacz.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    # include the icns file in the target
    SET(Tkacz_SOURCES ${Tkacz_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/Tkacz.icns)
    
    # copy schemas in bundle
    # @fixme potentially buggy…
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/schema/ DESTINATION Tkacz.app/Contents/Resources/schema)
    
    # Link to CoreFoundation
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework CoreFoundation")
ENDIF(APPLE)    

SET(MACOSX_BUNDLE_BUNDLE_NAME Tkacz)

include_directories("${PROJECT_BINARY_DIR}")

###### Modules ######

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/;${CMAKE_MODULE_PATH}")

####################
# Qt               #
####################

file(
        GLOB_RECURSE
        Tkacz_FORMS
        *.ui
)

file(
        GLOB_RECURSE
        Tkacz_RESOURCES
        *.qrc
)

file(
        GLOB_RECURSE
        Tkacz_HEADERS_MOC
        ${PROJECT_SOURCE_DIR}/gui/forms/*.hpp
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

QT5_WRAP_UI(Tkacz_FORMS_HEADERS ${Tkacz_FORMS})
QT5_WRAP_CPP(Tkacz_MOC_HEADERS ${Tkacz_HEADERS_MOC})
QT5_ADD_RESOURCES(Tkacz_RESOURCES_RCC ${Tkacz_RESOURCES})

foreach(_USE_FILE ${Qt5_USE_FILES})
    include(${_USE_FILE})
endforeach()

SET(Tkacz_SOURCES ${Tkacz_SOURCES} ${Tkacz_FORMS_HEADERS} ${Tkacz_RESOURCES_RCC}  ${Tkacz_MOC_HEADERS})

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

find_package(Boost COMPONENTS system filesystem log REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

####################
# Expat            #
####################

#find_package(XercesC REQUIRED)
find_package(EXPAT REQUIRED)

####################
# MongoDB          #
####################

find_package(MongoDB REQUIRED)

include_directories(${MongoDB_INCLUDE_DIR})
 
####################
# Linker           #
####################

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -dead_strip -order-file -macosx_version_min=10.9")
endif()

####################
# Executable       #
####################

add_library(Tkacz ${Tkacz_CORE_SOURCES} ${Tkacz_CORE_INCLUDES})
ADD_EXECUTABLE(TkaczExe MACOSX_BUNDLE ${Tkacz_SOURCES})

SET_TARGET_PROPERTIES(TkaczExe PROPERTIES OUTPUT_NAME "Tkacz")

target_link_libraries(TkaczExe Tkacz)
target_link_libraries(TkaczExe Qt5::Gui Qt5::Widgets Qt5::Core )
target_link_libraries(TkaczExe ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(TkaczExe ${EXPAT_LIBRARY} )
target_link_libraries(Tkacz ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(Tkacz ${MongoDB_LIBRARIES})

####################
# Install          #
####################

INSTALL(TARGETS TkaczExe 
    BUNDLE DESTINATION . COMPONENT Runtime 
    RUNTIME DESTINATION bin COMPONENT Runtime
    )
    
INSTALL(TARGETS Tkacz
    ARCHIVE DESTINATION lib COMPONENT Runtime
    )