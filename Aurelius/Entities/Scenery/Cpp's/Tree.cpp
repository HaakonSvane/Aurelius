//
//  Tree.cpp
//  Aurelius
//
//  Created by Haakon Svane on 10/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#include "Tree.hpp"

Tree::Tree(int x, int y, int forced_frame, SDL_RendererFlip forced_flip, float forced_rot)
:
Scenery{ID::SPRITES_ID::TREE, 32, false, forced_frame, forced_flip, forced_rot}
{
    pos.x =  static_cast<float>(x-8*CONSTANTS::SCALING);
    pos.y = static_cast<float>(y-16*CONSTANTS::SCALING);
    colors_.insert(0, COLORS::dWOOD);
    colors_.insert(1, COLORS::WOOD);
    colors_.insert(2, COLORS::lWOOD);
    colors_.insert(3, COLORS::dGRASS);
    colors_.insert(4, COLORS::GRASS);
    colors_.insert(5, COLORS::lGRASS);
    colors_.insert(6, COLORS::llGRASS);

    color_sprite();
    attach_sprite(new BigShadow{*this, {0, 9}});
    bp = builder_function();
}

void Tree::update(const Uint32 t){return;};

builder_pack Tree::builder_function() const{
    builder_pack bp{};

    SDL_RendererFlip f = (r == 0 || r == 2)? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    
    for (int i = 0; i < 2; i++){
        bp.push_back(BuilderItem{Vector2D<float>{0, static_cast<float>(- i*32*CONSTANTS::SCALING)}, &this_frames[(r/2)*2+i], f, 0.0});
    }
    return bp;
}


