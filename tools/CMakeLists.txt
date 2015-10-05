cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_BUILD_TYPE Debug)
project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(Boost_DEBUG OFF)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS regex system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

set(tools_SRC
FinalNode.cpp FinalNode.hpp
GetData.cpp GetData.hpp
Switch.cpp Switch.hpp
Instruction.cpp Instruction.hpp
InstructionTableToCode.cpp InstructionTableToCode.hpp
Case.cpp Case.hpp
)


add_executable(tool ${tools_SRC})

set_property(TARGET tool PROPERTY CXX_STANDARD 11)
set_property(TARGET tool PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(tool ${Boost_LIBRARIES})
install(TARGETS tool RUNTIME DESTINATION bin)