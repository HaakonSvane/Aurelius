//
//  Scenery.cpp
//  Aurelius
//
//  Created by Haakon Svane on 10/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#include "Scenery.hpp"

Scenery::Scenery(const ID::SPRITES_ID id, const Uint8 cell_s, const bool volatile_coloring, int forced_frame, SDL_RendererFlip forced_flip, float forced_rot):
Entity(id, cell_s, volatile_coloring)
{
    this->forced_frame = forced_frame;
    this->forced_flip = forced_flip;
    this->forced_rot = forced_rot;
}

builder_pack Scenery::builder_function() const {
    SDL_RendererFlip f;
    if(forced_frame >= 0){
        f = forced_flip;
    }else{
        switch (r){
            case 0: f = SDL_FLIP_NONE; break;
            case 1: f = SDL_FLIP_HORIZONTAL; break;
        }
    }

    return builder_pack{BuilderItem{Vector2D<float>{0, 0}, &this_frames[(forced_frame >= 0)?forced_frame:active_frame_index],
        f, forced_rot}};
}
