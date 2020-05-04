//
//  GrassBlock.hpp
//  Aurelius
//
//  Created by Haakon Svane on 17/12/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include "Block.hpp"


class GrassBlock : public Block{
public:
    GrassBlock(int x, int y, int forced_frame = -1, SDL_RendererFlip forced_flip = SDL_FLIP_NONE, float forced_rot = 0.0);
    void update(const Uint32 dt) override;

private:
    
};


