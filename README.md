## Z80 Emulator - This is unmaintained and was last worked on significantly in 2016 

Currently just trying to implement all documented instructions, undocumented ones will follow later.

### Features:
* Written from scratch in C++
* Suite of tests using Catch
* Comes with a Qt based UI
* Disassembler
* Builds on Linux/OSX/Windows

### How To Build
* git clone
* git submodule init
* git submodule update --recursive
* Ensure CMake is installed
* Ensure relevant dev libraries are installed: Boost, Qt5, SDL2, Lua etc

### Dependencies
* gcovr

Update modules to latest versions
git submodule update --init --recursive --remote

run `./ui/cpuqt2`

Run tests with code coverage
* Ensure gcov and lcov are installed
* cmake -DCMAKE_BUILD_TYPE=Debug 
* make 
* make my_coverage_target 

Code incorporated from elsewhere
* Modified zexdoc from https://github.com/anotherlin/z80emu

Coding standards
* Formatting? `find computer -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;`

### TODO:
- Make more c++ey i.e. use std::string instead of char*, references instead of pointers etc.
- Document available console commands
- Do UI scaling
- Fix snapshot loading!
- Improve code style/ naming, https://google.github.io/styleguide/cppguide.html#Naming
- Show list of breakpoints in UI
- Implement callback mechanism for extending, so don't have to inherit to do stuff like cpm_io
- throttle speed
- colour output
- keyboard input focus


- Use some kind of static anaysis tool, e.g cppcheck (cppcheck . --force 2> err.txt)
- Rerun valgrind (valgrind --leak-check=yes --track-origins=yes -v build/tooltests ADCA_HL_Test)

perf record build/zexrunner

Version number in about box
http://stackoverflow.com/questions/1704907/how-can-i-get-my-c-code-to-automatically-print-out-its-git-version-hash
http://xit0.org/2013/04/cmake-use-git-branch-and-commit-details-in-project/

```
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
export CCC_CC=clang
export CCC_CXX=clang++
scan-build cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang ..
scan-build make

cppcheck --enable=all -ibuild -iclang-build -itests/test.cpp . 2> cppcheck.txt
```

TODO: Ensure all methods use parity function where they should and write a test for it.

###Console commands
- Add breakpoint
- Remove breakpoint
- List breakpoints
- Peek value
- Poke value
- Set register
- Quit
- Load ROM
- Single step
