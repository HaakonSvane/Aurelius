//
//  WaterBlock.hpp
//  Aurelius
//
//  Created by Haakon Svane on 30/12/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <random>
#include "Block.hpp"
#include "Animator.hpp"

class WaterBlock : public Block{
public:
    WaterBlock(int x, int y, int forced_frame = -1, SDL_RendererFlip forced_flip = SDL_FLIP_NONE, float forced_rot = 0.0);
    void update(const Uint32 dt) override;

private:
    Animator anim;
};




