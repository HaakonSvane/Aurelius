//
//  Entity.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include "Sprite.hpp"

class Entity : public Sprite {
    
public:
    Entity(const ID::SPRITES_ID id, const Uint8 cell_s, const bool volatile_coloring) : Sprite{id, cell_s, volatile_coloring} {}
    virtual ~Entity() = default;
    
    virtual void update(const Uint32 dt) = 0;
    

};


