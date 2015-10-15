Z80 Emulator!

Currently just trying to implement all documented instructions, undocumented ones will follow later.

Features:
* Written from scratch in C++
* Suite of tests using Catch
* Comes with a Qt based UI
* Disassembler
* Builds on Linux/OSX/Windows

To
Modified zexdoc from https://github.com/anotherlin/z80emu

TODO:
Implement callack mechanism for extending, so don't have to inherit to do stuff like cpm_io


Use some kind of static anaysis tool, e.g cppcheck (cppcheck . --force 2> err.txt)
Rerun valgrind (valgrind --leak-check=yes --track-origins=yes -v build/tooltests ADCA_HL_Test)

perf record build/zexrunner

Version number in about box
http://stackoverflow.com/questions/1704907/how-can-i-get-my-c-code-to-automatically-print-out-its-git-version-hash
http://xit0.org/2013/04/cmake-use-git-branch-and-commit-details-in-project/

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
export CCC_CC=clang
export CCC_CXX=clang++
scan-build cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang ..
scan-build make


cppcheck --enable=all -ibuild -iclang-build -itests/test.cpp . 2> cppcheck.txt

TODO: Goes wrong at 11E0 of Spectrum ROM - Doesn't jump relative backwards correctly
TODO: Ensure all methods use parity function where they should and write a test for it.