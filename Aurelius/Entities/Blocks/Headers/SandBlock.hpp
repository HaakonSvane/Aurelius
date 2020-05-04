//
//  SandBlock.hpp
//  Aurelius
//
//  Created by Haakon Svane on 03/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#pragma once
#include "Block.hpp"
#include "Randomizer.hpp"

class SandBlock : public Block{
public:
    SandBlock(int x, int y, int forced_frame = -1, SDL_RendererFlip forced_flip = SDL_FLIP_NONE, float forced_rot = 0.0);
    void update(const Uint32 dt) override;

private:

};

