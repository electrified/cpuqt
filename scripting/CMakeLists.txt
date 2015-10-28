cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_BUILD_TYPE Debug)
project(scripting)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(Boost_DEBUG OFF)
# set(Boost_USE_STATIC_LIBS OFF)
# set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Lua REQUIRED)

include_directories(${LUA_INCLUDE_DIR})
# LINK_DIRECTORIES(${Lua_LIBRARY_DIRS})

set(scripting_SRC
    sampleluahost.cpp
)

add_executable(scripting ${scripting_SRC})

set_property(TARGET scripting PROPERTY CXX_STANDARD 11)
set_property(TARGET scripting PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(scripting ${LUA_LIBRARIES})
install(TARGETS scripting RUNTIME DESTINATION bin)