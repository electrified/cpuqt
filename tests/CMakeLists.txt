# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(Boost_DEBUG OFF)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS regex system filesystem timer REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

find_package (Threads)

set (tooltests_SRC
mocks/test_computer.h mocks/test_computer.cpp
../computer/consolebadgerio.cpp ../computer/consolebadgerio.h
test.cpp
graphics_test.cpp
computer_utils_test.cpp
catch.cpp
)

set (zexrunner_SRC
../computer/consolebadgerio.cpp ../computer/consolebadgerio.h
zexrunner.cpp zexrunner.h
mocks/test_computer.h mocks/test_computer.cpp
)

add_executable(tooltests ${tooltests_SRC})

add_executable(zexrunner ${zexrunner_SRC})

target_link_libraries(tooltests ${Boost_LIBRARIES} Z80 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(zexrunner ${Boost_LIBRARIES} Z80 ${Boost_SYSTEM_LIBRARY})
