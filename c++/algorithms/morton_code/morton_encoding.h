#include <iostream>

namespace morton
{
    namespace encoding
    {

        std::ostream &print_binary_32(std::ostream &out, unsigned int x);

        unsigned int spread_by_one_16(unsigned int x);

        std::ostream &print_binary_64(std::ostream &out, unsigned long long int x);

        unsigned long long int spread_by_one_32(unsigned long long int x);
    }
}

