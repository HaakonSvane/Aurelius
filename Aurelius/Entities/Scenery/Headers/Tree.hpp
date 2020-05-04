//
//  Tree.hpp
//  Aurelius
//
//  Created by Haakon Svane on 10/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#pragma once
#include "Scenery.hpp"
#include "BigShadow.hpp"

class Tree : public Scenery{
public:
    Tree(int x, int y, int forced_frame = -1, SDL_RendererFlip forced_flip = SDL_FLIP_NONE, float forced_rot = 0.0);
    void update(const Uint32 dt) override;
    virtual builder_pack builder_function() const override;
    
private:
    const int r = Randomizer::random_int(0, 3);
};
