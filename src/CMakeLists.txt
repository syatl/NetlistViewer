# To display executed commands, use:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

 cmake_minimum_required(VERSION 2.8.0)
 project(SCHEMATIC)
 
 set (CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE)
 set (CMAKE_INSTALL_PREFIX       "../install" )

 find_package(LibXml2 REQUIRED)
 find_package(Qt4     REQUIRED)
 include(${QT_USE_FILE})

    include_directories( ${SCHEMATIC_SOURCE_DIR}
                         ${LIBXML2_INCLUDE_DIR}
                       )

                    set( includes     Indentation.h
                                      XmlUtil.h 
                                      Point.h
                                      Box.h
                                      Term.h
                                      Net.h
                                      Instance.h
                                      Node.h
                                      Line.h
                                      Shape.h
                                      Symbol.h
                                      Cell.h
                       )

                    set( mocIncludes  SaveCellDialog.h
                                      OpenCellDialog.h
                                      CellWidget.h
                                      CellViewer.h
                                      InstancesModel.h
                                      InstancesWidget.h
                                      CellsLib.h
                                      CellsModel.h

                       )

                    set( cpps         Indentation.cpp
                                      XmlUtil.cpp 
                                      Point.cpp
                                      Box.cpp
                                      Term.cpp
                                      Net.cpp
                                      Instance.cpp
                                      Node.cpp
                                      Line.cpp
                                      Shape.cpp
                                      TermShape.cpp
                                      ArcShape.cpp
                                      BoxShape.cpp
                                      LineShape.cpp
                                      EllipseShape.cpp
                                      Symbol.cpp
                                      Cell.cpp
                                      SaveCellDialog.cpp
                                      OpenCellDialog.cpp
                                      CellWidget.cpp
                                      CellViewer.cpp
                                      InstancesModel.cpp
                                      InstancesWidget.cpp
                                      CellsLib.cpp
                                      CellsModel.cpp
                                      Main.cpp
                       )

           qt4_wrap_cpp( mocCpps      ${mocIncludes} )

         add_executable( NetlistViewer ${cpps} ${mocCpps} )
  target_link_libraries( NetlistViewer ${QT_LIBRARIES} ${LIBXML2_LIBRARIES} )
                install( TARGETS       NetlistViewer                      DESTINATION bin )
                install( FILES        ${includes} ${mocIncludes}  DESTINATION include )
