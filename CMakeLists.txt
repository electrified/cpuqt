cmake_minimum_required(VERSION 3.0.2)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

set(CMAKE_BUILD_TYPE Debug)
project(testproject)

use_cxx11()

add_subdirectory(tools)
#add_subdirectory(source_dir [binary_dir][EXCLUDE_FROM_ALL])


if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets Svg REQUIRED)

# find_package(Qt5Svg REQUIRED)

#set(Boost_DEBUG OFF)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS regex system filesystem timer REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

find_package(Lua 5.3 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

message("${LUA_LIBRARIES}")
message("${LUA_INCLUDE_DIR}")
message("${LUA_VERSION_STRING}")
set (GuiLib_src 
${PROJECT_SOURCE_DIR}/ui/main_window.cpp 
${PROJECT_SOURCE_DIR}/ui/DisassemblyModel.cpp 
${PROJECT_SOURCE_DIR}/ui/qtbadgerio.cpp
${PROJECT_SOURCE_DIR}/ui/qtbadgermemory.cpp
${PROJECT_SOURCE_DIR}/ui/cpm_io.cpp
${PROJECT_SOURCE_DIR}/ui/badgercomputer.cpp 
${PROJECT_SOURCE_DIR}/ui/about_box.cpp
${PROJECT_SOURCE_DIR}/ui/scripting/script_host.cpp
)

set (GuiLib_hdr 
${PROJECT_SOURCE_DIR}/ui/utils.h
${PROJECT_SOURCE_DIR}/ui/main_window.h 
${PROJECT_SOURCE_DIR}/ui/DisassemblyModel.h
${PROJECT_SOURCE_DIR}/ui/qtbadgerio.h
${PROJECT_SOURCE_DIR}/ui/qtbadgermemory.h
${PROJECT_SOURCE_DIR}/ui/cpm_io.h
${PROJECT_SOURCE_DIR}/ui/badgercomputer.h 
${PROJECT_SOURCE_DIR}/ui/about_box.h
${PROJECT_SOURCE_DIR}/ui/scripting/script_host.h
)

set (GuiLib_ui
${PROJECT_SOURCE_DIR}/ui/main_window.ui
${PROJECT_SOURCE_DIR}/ui/about_box.ui
)

set (GuiBin_src ${PROJECT_SOURCE_DIR}/main.cpp)

qt5_wrap_cpp(GuiLib_hdr_moc ${GuiLib_hdr})
qt5_wrap_ui (GuiLib_ui_moc  ${GuiLib_ui})

qt5_add_resources(APP_RESOURCES ui/resources/app.qrc)

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

add_library (GuiLib STATIC
    ${GuiLib_src}
    ${GuiLib_hdr_moc}
    ${GuiLib_ui_moc}
)

target_link_libraries(GuiLib Qt5::Widgets Qt5::Svg)

set(Z80_SRC
    Z80/Condition.hpp Z80/Condition.cpp
    Z80/disassembler.cpp Z80/disassembler.h
    Z80/Memory.h
    Z80/MemoryAddress.cpp Z80/MemoryAddress.h
    Z80/processor.cpp Z80/processor.h
    Z80/Register.hpp Z80/Register.cpp
    Z80/RegisterPair.hpp Z80/RegisterPair.cpp
    Z80/IO.h Z80/TestIO.h Z80/TestIO.cpp
    Z80/decoder.cpp Z80/decoder.h
    Z80/alu.h
    Z80/emu_alu.cpp Z80/emu_alu.h
    Z80/BadgerMemory.cpp Z80/BadgerMemory.h
    Z80/registers.h Z80/registers.cpp
    Logger.cpp Logger.h
    Z80/DisassemblyResult.cpp Z80/DisassemblyResult.h
    Z80/disassembler.cpp Z80/disassembler.h
    computer/badgerio.cpp computer/badgerio.h
    computer/utils.cpp computer/utils.h
    computer/spectrum/graphics.h
    computer/spectrum/spectrumio.cpp computer/spectrum/spectrumio.h
)

add_library(Z80 STATIC
    ${Z80_SRC}
)

set (tooltests_SRC
tests/test_computer.h tests/test_computer.cpp
computer/consolebadgerio.cpp computer/consolebadgerio.h
tests/test.cpp
tests/graphics_test.cpp
tests/catch.cpp
)

set (zexrunner_SRC
computer/consolebadgerio.cpp computer/consolebadgerio.h
tests/zexrunner.cpp tests/zexrunner.h
tests/test_computer.h tests/test_computer.cpp
)

add_executable(cpuqt2 ${GuiBin_src} ${APP_RESOURCES})

add_executable(tooltests ${tooltests_SRC})

add_executable(zexrunner ${zexrunner_SRC})


target_link_libraries(cpuqt2 GuiLib Z80 ${Boost_LIBRARIES} ${LUA_LIBRARIES})
target_link_libraries(tooltests ${Boost_LIBRARIES} Z80)
target_link_libraries(zexrunner ${Boost_LIBRARIES} Z80 ${Boost_SYSTEM_LIBRARY})

if (WIN32)
 # disable autolinking in boost
  add_definitions( -DBOOST_ALL_NO_LIB )

  # force all boost libraries to dynamic link (we already disabled
  # autolinking, so I don't know why we need this, but we do!)
  add_definitions( -DBOOST_ALL_DYN_LINK )
endif()

if (MSVC)
  # copy the debug and release dlls for Qt5Widgets, Qt5Core, and Qt5Gui
  get_property(qt5_qmake_executable TARGET ${Qt5Core_QMAKE_EXECUTABLE} PROPERTY IMPORT_LOCATION)
  execute_process(COMMAND ${qt5_qmake_executable} -query QT_INSTALL_PLUGINS OUTPUT_VARIABLE QT_INSTALL_PLUGINS OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND ${qt5_qmake_executable} -query QT_INSTALL_BINS OUTPUT_VARIABLE QT_INSTALL_BINS OUTPUT_STRIP_TRAILING_WHITESPACE)

  add_custom_target(copy_deps_qt5 ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_INSTALL_BINS}/Qt5Widgetsd.dll" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_INSTALL_BINS}/Qt5Cored.dll" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_INSTALL_BINS}/Qt5Guid.dll" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_INSTALL_BINS}/Qt5Svg.dll" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_INSTALL_BINS}/icudt54.dll" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_INSTALL_BINS}/icuin54.dll" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_INSTALL_BINS}/icuuc54.dll" "${CMAKE_BINARY_DIR}"
    COMMENT "Copying Qt5 dependencies to ${COPY_DEST}"
    VERBATIM)

   install(FILES ${Boost_SYSTEM_LIBRARY_RELEASE}
      ${Boost_FILESYSTEM_LIBRARY_RELEASE}
      ${Boost_REGEX_LIBRARY_RELEASE}
      DESTINATION bin
      CONFIGURATIONS Release RelWithDebInfo
   )
message (${Boost_SYSTEM_LIBRARY_DEBUG}
      ${Boost_FILESYSTEM_LIBRARY_DEBUG}
      ${Boost_REGEX_LIBRARY_DEBUG})
   install(FILES ${Boost_SYSTEM_LIBRARY_DEBUG}
      ${Boost_FILESYSTEM_LIBRARY_DEBUG}
      ${Boost_REGEX_LIBRARY_DEBUG}
      DESTINATION bin
      CONFIGURATIONS Debug
   )
endif()

file(COPY z80sean.txt DESTINATION .)

install(TARGETS cpuqt2 RUNTIME DESTINATION bin)
install(TARGETS tooltests RUNTIME DESTINATION bin)
#install(TARGETS Z80 RUNTIME DESTINATION bin)

foreach(plugin ${Qt5Gui_PLUGINS})
  get_target_property(_loc ${plugin} LOCATION)
  message("Core Plugin ${plugin} is at location ${_loc}")
endforeach()

foreach(plugin ${Qt5Svg_PLUGINS})
  get_target_property(_loc ${plugin} LOCATION)
  message("Core Plugin ${plugin} is at location ${_loc}")
endforeach()

if(WIN32)
        option(COPY_BOOST_BINARIES "Copy boost DLL files to local path" 1)
        #file(GLOB Boost_BINARIES ${Boost_LIBRARY_DIRS}/*.dll)
        if(COPY_BOOST_BINARIES)
                message(STATUS "Copying Boost DLL Files")
        endif()
        foreach(LIB ${Boost_LIBRARIES})
                if(NOT ${LIB} MATCHES "optimized" AND NOT ${LIB} MATCHES "debug")
                        set(BIN ${LIB})
                        string(REPLACE ".lib" ".dll" BIN ${BIN})
                        string(REPLACE "libboost" "boost" BIN ${BIN})
                        if(EXISTS ${BIN})
                                set(Boost_BINARIES ${Boost_BINARIES} ${BIN})
                                if(COPY_BOOST_BINARIES)
                                        message(STATUS "\t${BIN}")

                                        execute_process(COMMAND ${CMAKE_COMMAND} -E copy
                                                                                ${BIN} ${CMAKE_BINARY_DIR}/
                                                                                RESULT_VARIABLE COPY_RESULT
                                                                                ERROR_VARIABLE ERROR)
                                        if(NOT COPY_RESULT EQUAL 0)
                                                                MESSAGE(STATUS "Copy Boost - ${ERROR}")
                                        endif()
                                endif()
                        endif()
                endif()
        endforeach()
endif()
get_cmake_property(_variableNames VARIABLES)

#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
