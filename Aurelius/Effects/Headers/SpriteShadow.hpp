//
//  SpriteShadow.hpp
//  Aurelius
//
//  Created by Haakon Svane on 12/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#pragma once
#include "Sprite.hpp"

class SpriteShadow : public Sprite{
public:
    SpriteShadow(const ID::SPRITES_ID id, const Uint8 cell_s, const Sprite& owner, Vector2D<int> offset);
    virtual ~SpriteShadow() = default;
    virtual void update(const Uint32 dt) override;
    
private:
    const Sprite& owner;
    Vector2D<int> offset;
};
