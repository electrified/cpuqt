set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(
  Boost
  COMPONENTS regex system filesystem timer
  REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_library(
  Z80 STATIC
  Condition.hpp
  Condition.cpp
  disassembler.cpp
  disassembler.h
  Memory.h
  MemoryAddress.cpp
  MemoryAddress.h
  processor.cpp
  processor.h
  Register.hpp
  Register.cpp
  RegisterPair.hpp
  RegisterPair.cpp
  IO.h
  decoder.cpp
  decoder.h
  alu.h
  BadgerMemory.cpp
  BadgerMemory.h
  registers.h
  registers.cpp
  DisassemblyResult.cpp
  DisassemblyResult.h
  disassembler.cpp
  disassembler.h
  ../computer/utils.cpp
  ../computer/utils.h
  ../computer/spectrum/graphics.h
  ../computer/spectrum/spectrumio.cpp
  ../computer/spectrum/spectrumio.h ../computer/logger.cpp ../computer/logger.h)
