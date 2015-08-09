Modified zexdoc from https://github.com/anotherlin/z80emu

TODO:
Implement callack mechanism for extending, so don't have to inherit to do stuff like cpm_io
Use some kind of static anaysis tool, e.g cppcheck (cppcheck . --force 2> err.txt)
Rerun valgrind (valgrind --leak-check=yes --track-origins=yes -v build/tooltests ADCA_HL_Test)

Version number in about box
http://stackoverflow.com/questions/1704907/how-can-i-get-my-c-code-to-automatically-print-out-its-git-version-hash
http://xit0.org/2013/04/cmake-use-git-branch-and-commit-details-in-project/
