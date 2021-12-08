# Install script for directory: /home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "../install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/build/tme810")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Indentation.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/XmlUtil.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Point.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Box.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Term.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Net.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Instance.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Node.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Line.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Shape.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Symbol.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/Cell.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/SaveCellDialog.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/OpenCellDialog.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/CellWidget.h"
    "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/src/CellViewer.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/samy/Documents/fac/master/S1/mobj/NetlistViewer/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
