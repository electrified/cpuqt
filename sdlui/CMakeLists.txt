message(${PROJECT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules/sdl2-cmake-scripts")
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
# LINK_DIRECTORIES(${SDL2_LIBRARIES})

message(${SDL2_VERSION_STRING})
# message(${SDL2_LIBRARY})
add_executable(sdlui main.cpp)
target_link_libraries(sdlui ${SDL2_LIBRARIES})
# install(TARGETS sdlui RUNTIME DESTINATION bin)
