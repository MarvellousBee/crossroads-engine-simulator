#pragma once
#include "intersection.hpp"

namespace i_fun
{
    //check if sign grants priority
    bool prio(itrsn::Road road, std::vector<int> signs);

    bool sign_prio(itrsn::Road road);
    bool light_prio(itrsn::Road road);

    // check if a has priority over b
    //  0 - has no priority
    //  1 - has priority
    //  2 - equal priority
    int has_priority(itrsn::Road a, itrsn::Road b);
}
