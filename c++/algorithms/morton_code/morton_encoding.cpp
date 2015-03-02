#include "morton_encoding.h"

namespace morton
{
    namespace encoding
    {
        std::ostream &print_binary_32(std::ostream &out, unsigned int x)
        {
            unsigned int num_bit_in_int = sizeof(unsigned int) * 8;
            unsigned int max_shift = num_bit_in_int - 1;

            for (unsigned int i = 0; i < num_bit_in_int; ++i)
            {
                unsigned int mask = 1 << (max_shift - i);

                if (x & mask) {
                    out << "1";
                } else {
                    out << "0";
                }

                if (i % 4 == 3) {
                    out << " ";
                }
            }

            return out;
        }

        unsigned int spread_by_one_16(unsigned int x)
        {
            x &= 0x0000ffff;
            print_binary_32(std::cout << "0) ", x) << std::endl;

            x = (x | (x <<  8)) & 0x00ff00ff;
            print_binary_32(std::cout << "1) ", x) << std::endl;

            x = (x | (x <<  4)) & 0x0f0f0f0f;
            print_binary_32(std::cout << "2) ", x) << std::endl;

            x = (x | (x <<  2)) & 0x33333333;
            print_binary_32(std::cout << "3) ", x) << std::endl;

            x = (x | (x <<  1)) & 0x55555555;
            print_binary_32(std::cout << "4) ", x) << std::endl;

            return x;
        }

        std::ostream &print_binary_64(std::ostream &out, unsigned long long int x)
        {
            unsigned long long int num_bit_in_long_long_int = sizeof(unsigned long long int) * 8;
            unsigned long long int max_shift = num_bit_in_long_long_int - 1;

            for (unsigned long long int i = 0; i < num_bit_in_long_long_int; ++i)
            {
                unsigned long long int shift = max_shift - i;
                unsigned long long int mask = 1ull << shift;

                if (x & mask) {
                    out << "1";
                } else {
                    out << "0";
                }

                if (i % 4 == 3) {
                    out << " ";
                }
            }

            return out;
        }

        unsigned long long int spread_by_one_32(unsigned long long int x)
        {
            x &= 0x00000000ffffffff;
            print_binary_64(std::cout << "0) ", x) << std::endl;

            x = (x | (x <<  16)) & 0x0000ffff0000ffffull;
            print_binary_64(std::cout << "1) ", x) << std::endl;

            x = (x | (x <<  8)) & 0x00ff00ff00ff00ffull;
            print_binary_64(std::cout << "2) ", x) << std::endl;

            x = (x | (x <<  4)) & 0x0f0f0f0f0f0f0f0full;
            print_binary_64(std::cout << "3) ", x) << std::endl;

            x = (x | (x <<  2)) & 0x3333333333333333ull;
            print_binary_64(std::cout << "4) ", x) << std::endl;

            x = (x | (x <<  1)) & 0x5555555555555555ull;
            print_binary_64(std::cout << "5) ", x) << std::endl;

            return x;
        }
    }
}
