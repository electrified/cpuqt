cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

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

INCLUDE(CodeCoverage)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

SETUP_TARGET_FOR_COVERAGE(
    my_coverage_target  # Name for custom target.
    ./tests/tooltests         # Name of the test driver executable that runs the tests.
              # NOTE! This should always have a ZERO as exit code
              # otherwise the coverage generation will not complete.
    coverage            # Name of output directory.
)

# SPDLOG setup
FILE(GLOB SPDLOG_INCLUDES
  "modules/spdlog/include/spdlog/*.h"
  "modules/spdlog/include/spdlog/details/*.h"
  "modules/spdlog/include/spdlog/sinks/*.h"
  )
LIST(REMOVE_ITEM SPDLOG_INCLUDES "modules/spdlog/include/spdlog/tweakme.h" )
SOURCE_GROUP(SPDLog FILES ${SPDLOG_INCLUDES})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/modules/spdlog/include/)

# Selene (LUA bindings) setup
FILE(GLOB SELENE_INCLUDES
  "modules/selene/include/*.h"
  "modules/selene/include/selene/*.h"
  )
SOURCE_GROUP(SELENE FILES ${SELENE_INCLUDES})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/modules/Selene/include/)


add_subdirectory(Z80)
# add_subdirectory(tools)
add_subdirectory(ui)
add_subdirectory(tests)
#add_subdirectory(sdlui)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(Boost_DEBUG OFF)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS regex system filesystem timer REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

if (WIN32)
 # disable autolinking in boost
  add_definitions( -DBOOST_ALL_NO_LIB )

  # force all boost libraries to dynamic link (we already disabled
  # autolinking, so I don't know why we need this, but we do!)
  add_definitions( -DBOOST_ALL_DYN_LINK )
endif()

if (MSVC)
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
