cmake_minimum_required(VERSION 3.0.2)

project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets REQUIRED)
#set(Boost_DEBUG OFF)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS regex system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#message(${Boost_LIBRARIES})


set (GuiLib_src ${PROJECT_SOURCE_DIR}/main_window.cpp)
set (GuiLib_hdr ${PROJECT_SOURCE_DIR}/main_window.h)
set (GuiLib_ui  ${PROJECT_SOURCE_DIR}/main_window.ui)
set (GuiBin_src ${PROJECT_SOURCE_DIR}/main.cpp)

qt5_wrap_cpp(GuiLib_hdr_moc ${GuiLib_hdr})
qt5_wrap_ui (GuiLib_ui_moc  ${GuiLib_ui})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

# add_library(main_window main_window.cpp)
add_library (GuiLib SHARED 
    ${GuiLib_src}
    ${GuiLib_hdr_moc}
    ${GuiLib_ui_moc}
)

qt5_use_modules(GuiLib Widgets)

# set(cpuqt2_SRCS cpuqt2.cpp main.cpp )

set(tools_SRC tools/FinalNode.cpp tools/FinalNode.hpp tools/GetData.cpp tools/GetData.hpp tools/Switch.cpp tools/Switch.hpp tools/Instruction.cpp tools/Instruction.hpp tools/InstructionTableToCode.cpp tools/InstructionTableToCode.hpp tools/Case.cpp tools/Case.hpp)

set(Z80_SRC
    Z80/EmulationProcessor.cpp Z80/EmulationProcessor.h Z80/Condition.cpp Z80/Condition.hpp Z80/DisassemblerProcessor.cpp Z80/DisassemblerProcessor.h
    Z80/Memory.cpp Z80/Memory.h
    Z80/MemoryAddress.cpp Z80/MemoryAddress.h Z80/Processor.cpp Z80/Processor.h Z80/Register.cpp Z80/Register.hpp Z80/RegisterPair.cpp Z80/RegisterPair.hpp
    Z80/IO.cpp Z80/IO.h Z80/TestIO.h Z80/TestIO.cpp
    Z80/BaseProcessor.cpp Z80/BaseProcessor.h
    Z80/baseprocessordecoder.cpp Z80/baseprocessordecoder.h
    Z80/badgerio.cpp Z80/badgerio.h  Z80/BadgerMemory.cpp Z80/BadgerMemory.h
    Logger.cpp Logger.h
    #Z80/InstructionDecoder.cpp Z80/InstructionDecoder.h Z80/InstructionDecoderGenerated.cpp Z80/InstructionDecoderGenerated.h
)

set(tooltests_SRC tools/Test.cpp)

add_executable(cpuqt2 ${GuiBin_src} ${Z80_SRC})

add_executable(tool ${tools_SRC} ${Z80_SRC})

add_executable(tooltests ${Z80_SRC} ${tooltests_SRC})

set_property(TARGET cpuqt2 PROPERTY CXX_STANDARD 11)
set_property(TARGET cpuqt2 PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET tool PROPERTY CXX_STANDARD 11)
set_property(TARGET tool PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET tooltests PROPERTY CXX_STANDARD 11)
set_property(TARGET tooltests PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(tool ${Boost_LIBRARIES})
target_link_libraries(cpuqt2 GuiLib)
target_link_libraries(tooltests ${Boost_LIBRARIES})

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
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_INSTALL_BINS}/icudt53.dll" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_INSTALL_BINS}/icuin53.dll" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_INSTALL_BINS}/icuuc53.dll" "${CMAKE_BINARY_DIR}"
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
install(TARGETS tool RUNTIME DESTINATION bin)
install(TARGETS tooltests RUNTIME DESTINATION bin)

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
