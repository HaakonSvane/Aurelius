//
//  Mob.cpp
//  Aurelius
//
//  Created by Haakon Svane on 26/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "Mob.hpp"


void Mob::move(const ID::Move_dirs m){
    switch(m){
        case(ID::MOVE_UP): move_vector.y = (move_vector.y<=-1)? -1 : move_vector.y-1;
            break;
        case(ID::MOVE_LEFT): move_vector.x = (move_vector.x<=-1)? -1 : move_vector.x-1;
            break;
        case(ID::MOVE_DOWN): move_vector.y = (move_vector.y>=1)? 1 : move_vector.y+1;
            break;
        case(ID::MOVE_RIGHT): move_vector.x = (move_vector.x>=1)? 1 : move_vector.x+1;
            break;
        case(ID::MOVE_NONE):{
            move_vector.x = 0;
            move_vector.y = 0;
            break;
        }
    }
}
