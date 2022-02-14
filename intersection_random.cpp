#include <cctype>
#include <random>
#include "intersection_random.hpp"


int i_random::r_num(int num, bool biased)
{
    //setup
    std::random_device os_seed;
    const uint_least32_t seed = os_seed();

    std::mt19937 generator( seed );
    std::uniform_int_distribution<uint_least32_t> distribute( 0,1 );
    if (biased)
    {
        std::uniform_int_distribution<uint_least32_t> distribute( 0,1 );
        if (distribute( generator ))
        return 0;
    }
    //else, return a random number
    std::uniform_int_distribution<uint_least32_t> distribute2( 0,num );
    return static_cast<int>(distribute2(generator));
}

