#include "Z80/Memory.h"

#include <iostream>
#include <fstream>
#include <vector>

std::vector<char> ReadAllBytes(char const* filename)
{
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

void loadIntoMemory(std::vector<char> data, Memory* memory, std::uint16_t offset) {
    for (std::uint16_t i = 0; i < data.size(); ++i) {
        memory->write(i + offset, data.at(i));
    }
}


void loadIntoMemory2(Memory* memory, std::uint16_t offset, char const* filename) {
std::ifstream testFile(filename,  std::ios::binary);
std::vector<char> fileContents((std::istreambuf_iterator<char>(testFile)),
                               std::istreambuf_iterator<char>());

    for (std::uint16_t i = 0; i < fileContents.size(); ++i) {
        memory->write(i + offset, fileContents.at(i));
    }
}