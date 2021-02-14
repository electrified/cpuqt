cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
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

find_package(Threads)

set(tooltests_SRC
    mocks/test_computer.h
    mocks/test_computer.cpp
    mocks/test_io.h
    mocks/test_io.cpp
    test.cpp
    graphics_test.cpp
    # computer_utils_test.cpp
    main.cpp)

set(zexrunner_SRC
    zexrunner.cpp
    mocks/zexrunner_computer.h
    mocks/zexrunner_computer.cpp
    ../computer/cpm/serial_io.cpp
    ../computer/cpm/serial_io.h
    ../computer/cpm/console_serial_io.cpp
    ../computer/cpm/console_serial_io.h)

add_subdirectory(./modules/Catch2)

add_executable(tests ${tooltests_SRC})
add_executable(zexrunner ${zexrunner_SRC})

target_link_libraries(tests PRIVATE ${Boost_LIBRARIES} Z80
                                    ${CMAKE_THREAD_LIBS_INIT} Catch2::Catch2)
target_link_libraries(zexrunner ${Boost_LIBRARIES} Z80
                      ${CMAKE_THREAD_LIBS_INIT} ${Boost_SYSTEM_LIBRARY})
