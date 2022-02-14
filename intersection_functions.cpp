#include "intersection_functions.hpp"

namespace i_fun
{
    //check if sign grants priority
    bool  prio(itrsn::Road road, std::vector<int> signs){
        return (
            std::find(
                    signs.begin()
                    , signs.end()
                    , road.sign
                    ) 
            != 
            signs.end()
            );
    }
    //split into more functions to increase(decrease?) readibility
    bool  sign_prio(itrsn::Road road){
        return prio(road, itrsn::sign::high_priority_signs);
    }
    bool light_prio(itrsn::Road road){
        return prio(road, itrsn::sign::high_priority_lights);
    }

    //check if a has priority over b
    // 0 - has no priority
    // 1 - has priority
    // 2 - equal priority
    int has_priority(itrsn::Road a, itrsn::Road b)
        {
            //check if there are any lights
            if (light_prio(a) > light_prio(b))
            {
                return 1;
            }
            else if (light_prio(a) < light_prio(b))
            {
                return 0;
            }
            //check if there are any signs
            if ( a.sign == 0 && b.sign == 0 )
            {
                //check if b is on the right of a
                if ( a.id == b.id-1 || (a.id==3 && b.id==0) )
                    return 0;
                //check if a is on the same course as b
                else if ( (a.id==0 && b.id==2) || (a.id==1 && b.id==3) )
                    return 2;
                else
                    return 1;
            }
            //Check if any sign priority rules apply
            else if (sign_prio(a) > sign_prio(b))
            {
                return 1;
            }
            else if (sign_prio(a) < sign_prio(b))
            {
                return 0;
            }
            else
            {
                return 2;
            }
        }
}