//
//  GrassBlock.cpp
//  Aurelius
//
//  Created by Haakon Svane on 17/12/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "GrassBlock.hpp"
#include "Randomizer.hpp"


GrassBlock::GrassBlock(int x, int y, int forced_frame, SDL_RendererFlip forced_flip, float forced_rot)
:
Block{ID::SPRITES_ID::GRASS, 16, false, forced_frame, forced_flip, forced_rot}
{
    pos.x = static_cast<float>(x);
    pos.y = static_cast<float>(y);
    colors_.insert(0, COLORS::GRASS);
    colors_.insert(1, COLORS::lGRASS);
    colors_.insert(2, COLORS::dGRASS);
    colors_.insert(3, COLORS::GRASS);
    colors_.insert(4, COLORS::lGRASS);
    colors_.insert(5, COLORS::GRASS);
    active_frame_index = Randomizer::random_int(0,2);
    
    color_sprite();
    bp = builder_function();
    
}

void GrassBlock::update(const Uint32 t){return;};
