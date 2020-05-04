//
//  WaterBlock.cpp
//  Aurelius
//
//  Created by Haakon Svane on 30/12/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "WaterBlock.hpp"


WaterBlock::WaterBlock(int x, int y, int forced_frame, SDL_RendererFlip forced_flip, float forced_rot)
:
Block{ID::SPRITES_ID::WATER, 16, false, forced_frame, forced_flip, forced_rot},
anim{3, 1, ID::Anim_Modes::ANIM_UP, static_cast<Uint8>(Randomizer::random_int(0,2))}
{

    pos.x = static_cast<float>(x);
    pos.y = static_cast<float>(y);
    colors_.insert(2, COLORS::lWATER);
    colors_.insert(3, COLORS::WATER);
    color_sprite();
    anim.set_tpf(270);
    bp = builder_function();
    
}

void WaterBlock::update(const Uint32 t){
    anim.update();
    active_frame_index = anim.current_frame();
    bp[0].src_rec = &this_frames[active_frame_index];
};
