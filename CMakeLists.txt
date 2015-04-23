cmake_minimum_required(VERSION 2.8.11)

project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS regex system filesystem) 

include_directories(${Boost_INCLUDE_DIRS}) 

set(cpuqt2_SRCS cpuqt2.cpp main.cpp MainWindow.h ${Boost_LIBRARIES})
# 
# file(GLOB tools_SRC
#     "tools/*.hpp"
#     "tools/*.cpp"
# )

set(tools_SRC tools/FinalNode.cpp tools/FinalNode.hpp tools/GetData.cpp tools/GetData.hpp tools/Switch.cpp tools/Switch.hpp tools/Instruction.cpp tools/Instruction.hpp tools/InstructionTableToCode.cpp tools/InstructionTableToCode.hpp tools/Case.cpp tools/Case.hpp)


file(GLOB Z80_SRC
    "Z80/*.hpp"
    "Z80/*.cpp"
)

add_executable(cpuqt2 ${cpuqt2_SRCS} ${Z80_SRC})

add_executable(tool ${tools_SRC} ${Z80_SRC})

set_property(TARGET cpuqt2 PROPERTY CXX_STANDARD 11)
set_property(TARGET cpuqt2 PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET tool PROPERTY CXX_STANDARD 11)
set_property(TARGET tool PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(tool ${Boost_LIBRARIES})


target_link_libraries(cpuqt2 Qt5::Widgets)

install(TARGETS cpuqt2 RUNTIME DESTINATION bin)
install(TARGETS tool RUNTIME DESTINATION bin)
