//
//  Mob.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <utility>
#include "Vector2D.hpp"
#include "Entity.hpp"
#include "Identifications.hpp"


class Mob : public Entity {
public:
    Mob(const ID::SPRITES_ID id, const Uint8 cell_s, const bool volatile_coloring) : Entity(id, cell_s, volatile_coloring){};
    virtual ~Mob() = default;
    
    virtual void update(const Uint32 dt) = 0;
    
    void move(const ID::Move_dirs m);

protected:
    Vector2D<int8_t> move_vector;
    
private:
    Uint8 hp;
    
};



