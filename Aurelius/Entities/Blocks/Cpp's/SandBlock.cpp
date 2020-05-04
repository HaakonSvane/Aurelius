//
//  SandBlock.cpp
//  Aurelius
//
//  Created by Haakon Svane on 03/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#include "SandBlock.hpp"


SandBlock::SandBlock(int x, int y, int forced_frame, SDL_RendererFlip forced_flip, float forced_rot)
:
Block{ID::SPRITES_ID::SAND, 16, false, forced_frame, forced_flip, forced_rot}
{
    pos.x = static_cast<float>(x);
    pos.y = static_cast<float>(y);
    colors_.insert(2, COLORS::GRAY);
    colors_.insert(3, COLORS::lSAND);
    colors_.insert(5, COLORS::lGRAY);
    colors_.insert(6, COLORS::SAND);
    active_frame_index = Randomizer::random_int(0,2);
    
    color_sprite();
    bp = builder_function();
}

void SandBlock::update(const Uint32 t){return;};
