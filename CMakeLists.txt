cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")
include(ExternalProject)

get_cmake_property(variableNames VARIABLES)
foreach(variableName ${variableNames})
  message(STATUS "${variableName}=${${variableName}}")
endforeach()

set(CMAKE_BUILD_TYPE Debug)
project(
  testproject
  VERSION 0.1
  DESCRIPTION "Z80 based emulator"
  LANGUAGES CXX)

#set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS}")
#set(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage ${CMAKE_C_FLAGS}")

add_subdirectory(modules/spdlog)
include_directories(${CMAKE_SOURCE_DIR}/modules/spdlog/include/)

add_subdirectory(modules/sol2)
include_directories(${CMAKE_SOURCE_DIR}/modules/sol2/include/)

add_subdirectory(Z80)
# add_subdirectory(tools)
add_subdirectory(ui)
add_subdirectory(tests)
# add_subdirectory(sdlui)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# set(Boost_DEBUG OFF)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(
  Boost
  COMPONENTS regex system filesystem timer
  REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

if(WIN32)
  # disable autolinking in boost
  add_definitions(-DBOOST_ALL_NO_LIB)

  # force all boost libraries to dynamic link (we already disabled autolinking,
  # so I don't know why we need this, but we do!)
  add_definitions(-DBOOST_ALL_DYN_LINK)
endif()

if(MSVC)
  install(
    FILES ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_FILESYSTEM_LIBRARY_RELEASE}
          ${Boost_REGEX_LIBRARY_RELEASE}
    DESTINATION bin
    CONFIGURATIONS Release RelWithDebInfo)
  message(${Boost_SYSTEM_LIBRARY_DEBUG} ${Boost_FILESYSTEM_LIBRARY_DEBUG}
          ${Boost_REGEX_LIBRARY_DEBUG})
  install(
    FILES ${Boost_SYSTEM_LIBRARY_DEBUG} ${Boost_FILESYSTEM_LIBRARY_DEBUG}
          ${Boost_REGEX_LIBRARY_DEBUG}
    DESTINATION bin
    CONFIGURATIONS Debug)
endif()

if(WIN32)
  option(COPY_BOOST_BINARIES "Copy boost DLL files to local path" 1)
  # file(GLOB Boost_BINARIES ${Boost_LIBRARY_DIRS}/*.dll)
  if(COPY_BOOST_BINARIES)
    message(STATUS "Copying Boost DLL Files")
  endif()
  foreach(lib ${Boost_LIBRARIES})
    if(NOT ${lib} MATCHES "optimized" AND NOT ${lib} MATCHES "debug")
      set(BIN ${lib})
      string(REPLACE ".lib" ".dll" BIN ${BIN})
      string(REPLACE "libboost" "boost" BIN ${BIN})
      if(EXISTS ${BIN})
        set(Boost_BINARIES ${Boost_BINARIES} ${BIN})
        if(COPY_BOOST_BINARIES)
          message(STATUS "\t${BIN}")

          execute_process(
            COMMAND ${CMAKE_COMMAND} -E copy ${BIN} ${CMAKE_BINARY_DIR}/
            RESULT_VARIABLE COPY_RESULT
            ERROR_VARIABLE ERROR)
          if(NOT COPY_RESULT EQUAL 0)
            message(STATUS "Copy Boost - ${ERROR}")
          endif()
        endif()
      endif()
    endif()
  endforeach()
endif()
get_cmake_property(_variableNames VARIABLES)
