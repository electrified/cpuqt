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
    for (int i = 0; i < data.size(); ++i) {
        memory->write(i + offset, data.at(i));
    }
}