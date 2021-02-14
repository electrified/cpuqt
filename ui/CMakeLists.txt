cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(
  Qt5
  COMPONENTS Widgets Svg
  REQUIRED)

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

find_package(Lua 5.3 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

find_package(Threads)

set(GuiLib_src
    main_window.cpp
    DisassemblyModel.cpp
    qtbadgerio.cpp
    qtbadgermemory.cpp
    cpm_io.cpp
    badgercomputer.cpp
    about_box.cpp
    scripting/script_host.cpp
    keypresseater.cpp
    settings.cpp
    utils.cpp)

set(GuiLib_hdr
    # utils.h
    main_window.h
    DisassemblyModel.h
    qtbadgerio.h
    qtbadgermemory.h
    cpm_io.h
    badgercomputer.h
    about_box.h
    # scripting/script_host.h
    qdebugstream.h
    keypresseater.h
    settings.h
    utils.h)

set(GuiLib_ui main_window.ui about_box.ui)

set(GuiBin_src main.cpp)

qt5_wrap_cpp(GuiLib_hdr_moc ${GuiLib_hdr})
qt5_wrap_ui(GuiLib_ui_moc ${GuiLib_ui})
qt5_add_resources(APP_RESOURCES resources/app.qrc)

include_directories(${PROJECT_SOURCE_DIR})

add_library(GuiLib STATIC ${GuiLib_src} ${GuiLib_hdr_moc} ${GuiLib_ui_moc})

target_link_libraries(GuiLib Qt5::Widgets Qt5::Svg ${LUA_LIBRARIES})

add_executable(cpuqt2 ${GuiBin_src} ${APP_RESOURCES})

target_link_libraries(cpuqt2 GuiLib Z80 ${Boost_LIBRARIES}
                      ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS cpuqt2 RUNTIME DESTINATION bin)
