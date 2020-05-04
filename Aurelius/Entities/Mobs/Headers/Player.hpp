//
//  Player.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include "Mob.hpp"
#include "Randomizer.hpp"
#include "Vector2D.hpp"
#include "MediumShadow.hpp"
#include "Animator.hpp"


class Surface;
class Player : public Mob {
    
public:
    Player();
    Player(const float x, const float y);
    Player(const int x, const int y);
    ~Player();
    
    void update(const Uint32 dt) override;
    
private:
    int movespeed = 200;
    
    bool right = true;
    bool down = true;
    
    Animator anim;
    
    // TODO: This ?
    const std::vector<COLORS> skin_colors{};
    const std::vector<COLORS> cloth_colors{};
    const std::vector<COLORS> eye_colors{};
};
