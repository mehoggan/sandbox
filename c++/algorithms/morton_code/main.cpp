#include "morton_encoding.h"

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Input: " << std::hex << 0x000000FF << std::endl;
    morton::encoding::spread_by_one_16(0x000000FF);
    std::cout << std::endl;
    std::cout << "Input: " << std::hex << 0x0000000000FF00FF << std::endl;
    morton::encoding::spread_by_one_32(0x0000000000FF00FFull);

    return 0;
}
