#include <set>
#include <vector>
#include <iterator>
#include <iostream>
#include <bitset>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include <stdint.h>
#include <string.h>

#include <boost/timer/timer.hpp>

const char Bit2Posn[] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0 };

const uint32_t Posn2Bit[] = {
    1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800,
    0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000, 0x40000, 0x80000,
    0x100000, 0x200000, 0x400000, 0x800000,
    0x1000000, 0x2000000, 0x4000000, 0x8000000,
    0x10000000, 0x20000000, 0x40000000, 0x80000000 };

uint32_t Posn2Mask[] = {
        0xFFFFFFFE, 0xFFFFFFFD, 0xFFFFFFFB, 0xFFFFFFF7,
        0xFFFFFFEF, 0xFFFFFFDF, 0xFFFFFFBF, 0xFFFFFF7F,
        0xFFFFFEFF, 0xFFFFFDFF, 0xFFFFFBFF, 0xFFFFF7FF,
        0xFFFFEFFF, 0xFFFFDFFF, 0xFFFFBFFF, 0xFFFF7FFF,
        0xFFFEFFFF, 0xFFFDFFFF, 0xFFFBFFFF, 0xFFF7FFFF,
        0xFFEFFFFF, 0xFFDFFFFF, 0xFFBFFFFF, 0xFF7FFFFF,
        0xFEFFFFFF, 0xFDFFFFFF, 0xFBFFFFFF, 0xF7FFFFFF,
        0xEFFFFFFF, 0xDFFFFFFF, 0xBFFFFFFF, 0x7FFFFFFF 
};

int32_t staticP32Index(int bits_) {
    int ret = -1;
    unsigned int tmpBits = 0;
    unsigned int i = 0;

    for (i = 0; i < 4; ++i) {
        tmpBits = ((bits_ >> (i * 8)) & 0xFF);
        if (!tmpBits) {
            continue;
        }
        ret = Bit2Posn[tmpBits];
        if (ret != -1) {
            break;
        }
    }
    return ((i == 4) ? 0 : (ret + i * 8));
}

std::set<uint32_t> power_set_in_bit_field_format(uint32_t bit_field) {
    int32_t tones[6];
    std::set<uint32_t> ret;
    memset(tones, -1, 6 * sizeof(int32_t));
    uint32_t index = 0;
    while (bit_field) {
        uint16_t tone = staticP32Index(bit_field);
        bit_field &= Posn2Mask[tone];
        tones[index++] = tone;
    }

    uint32_t number_of_sets_in_power_set = std::pow(2, index);
    for (uint32_t i = 0; i < number_of_sets_in_power_set; ++i) {
        uint32_t tone_bit_field = 0;
        uint32_t mask = i;
        while (mask) {
            index = staticP32Index(mask);
            mask &= Posn2Mask[index];
            if (tones[index] != -1) {
                tone_bit_field |= Posn2Bit[tones[index]]; 
            }
        }
        ret.insert(tone_bit_field);
    }
    return ret; 
}

int main(int /*argc*/, char * /*argv*/[]) {
    srand(time(NULL));
    for (uint32_t i = 0; i < 10; ++i) {
        uint32_t bit_field = 0;
        uint32_t number_of_tones = std::rand() % 6;
        for (uint32_t j = 0; j < number_of_tones; ++j) {
            bit_field |= Posn2Bit[std::rand() % 20];            
        }
        std::cout << "=================================================" <<
            std::endl;
        std::cout << "Test " << (i + 1) << std::endl;
        std::set<uint32_t> power_set_of_tones;
        {
            std::cout << "Timing" << std::endl;
            boost::timer::auto_cpu_timer t;
            power_set_of_tones = power_set_in_bit_field_format(bit_field);
        }
        std::cout << "Number of tones: " << number_of_tones << std::endl;
        std::cout << "Number of combinations " << power_set_of_tones.size()
            << std::endl;
        std::bitset<20> tones(bit_field);
        std::cout << "Original bits " << tones << std::dec <<
            "(" << bit_field << ")" << std::endl;
        
        for (std::set<uint32_t>::iterator set_it = power_set_of_tones.begin();
            set_it != power_set_of_tones.end();
            ++set_it) {
        
            std::bitset<20> bits(*set_it);
            std::cout << "\tOriginal bits " << bits << 
                std::dec << "(" << (*set_it) << ")" << std::endl;
        }
        std::cout << "=================================================" <<
            std::endl;
    }
    return 0;
}




















