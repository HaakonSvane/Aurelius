//
//  Peripheral.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include "Sprite.hpp"

class Peripheral: public Sprite
{
public:
    
    Peripheral(const ID::SPRITES_ID id, const Uint8 cell_s, const bool volatile_coloring);
    virtual ~Peripheral() = default;
    
    virtual void update(const Uint32 dt) = 0;
    
protected:

};
