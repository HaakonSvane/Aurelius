//
//  Block.hpp
//  Aurelius
//
//  Created by Haakon Svane on 03/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#pragma once
#include "Entity.hpp"
#include "Randomizer.hpp"


class Block : public Entity{
public:
    Block(const ID::SPRITES_ID id, const Uint8 cell_s, const bool volatile_coloring, int forced_frame, SDL_RendererFlip forced_flip, float forced_rot);
    virtual ~Block() = default;
    
    virtual void update(const Uint32 dt) override = 0;
    virtual builder_pack builder_function() const override;
    
private:
    int forced_frame;
    SDL_RendererFlip forced_flip;
    float forced_rot;
    const int r = Randomizer::random_int(0, 3);
};
