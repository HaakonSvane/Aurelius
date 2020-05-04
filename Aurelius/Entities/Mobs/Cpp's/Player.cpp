//
//  Player.cpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "Player.hpp"
#include "Constants.hpp"
#include "Sprite.hpp"
#include "Animator.hpp"
#include <iostream>
#include "Identifications.hpp"
#include "MediumShadow.hpp"

Player::Player()
:
Player{0.f,0.f}
{
}

Player::Player(const int x, const int y)
:
Player{static_cast<float>(x), static_cast<float>(y)}
{
}

Player::Player(const float x, const float y)
    :
    Mob{ID::SPRITES_ID::PLAYER, 16, true},
    anim{15, 5, ID::Anim_Modes::ANIM_FOIL}
{
    pos.x = x;
    pos.y = y;
    const int r1 = Randomizer::random_int(1, 4);
    const int r2 = Randomizer::random_int(1, 4);
    const int r3 = Randomizer::random_int(1, 4);

    colors_.insert(0, COLORS::SKIN_OUTLINE);
    switch (r1)
    {
        case 1:
        {
            colors_.insert(1, COLORS::GREEN);
            colors_.insert(2, COLORS::lGREEN);;
            break;
        }
        case 2:
        {
            colors_.insert(1, COLORS::BLUE);
            colors_.insert(2, COLORS::lBLUE);
            break;
        }
        case 3:
        {
            colors_.insert(1, COLORS::RED);
            colors_.insert(2, COLORS::lRED);
            break;
        }
        case 4:
        {
            colors_.insert(1, COLORS::PURPLE);
            colors_.insert(2, COLORS::lPURPLE);
            break;
        }
        default:
        {
            colors_.insert(1, COLORS::DEFAULT);
            colors_.insert(2, COLORS::DEFAULT);
            break;
        }
    }
    switch(r2)
    {
        case 1: colors_.insert(3, COLORS::dBLUE);
            break;
        case 2: colors_.insert(3, COLORS::RED);
            break;
        case 3: colors_.insert(3, COLORS::dGREEN);
            break;
        case 4: colors_.insert(3, COLORS::dORANGE);
            break;
        default: colors_.insert(3, COLORS::DEFAULT);
            break;
    }
    switch(r3)
    {
        case 1:
        {
            colors_.insert(4, COLORS::sSKIN_1);
            colors_.insert(5, COLORS::SKIN_1);
            break;
        }
        case 2:
        {
            colors_.insert(4, COLORS::sSKIN_2);
            colors_.insert(5, COLORS::SKIN_2);
            break;
        }
        case 3:
        {
            colors_.insert(4, COLORS::sSKIN_3);
            colors_.insert(5, COLORS::SKIN_3);
            break;
        }
        case 4:
        {
            colors_.insert(4, COLORS::sSKIN_4);
            colors_.insert(5, COLORS::SKIN_4);
            break;
        }
        default:
        {
            colors_.insert(4, COLORS::DEFAULT);
            colors_.insert(5, COLORS::DEFAULT);
            break;
        }
    }
    colors_.insert(6, COLORS::WHITE);
    anim.set_state(0);
    attach_sprite(new MediumShadow(*this, {0, 8}));
    color_sprite();
    bp = builder_function();
}

Player::~Player()
{

};

void Player::update(const Uint32 dt)
{
    float fac = (move_vector.length() == 0.0)?1.0:(1.0/move_vector.length());
    pos.x += fac*(float)move_vector.x*(float)movespeed*(float)dt/1000.0;
    pos.y += fac*(float)move_vector.y*(float)movespeed*(float)dt/1000.0;
    for (auto& p : attached_sprites){
        p->update(dt);
    }
    
    anim.update();
    active_frame_index = anim.current_frame();
    
    if (move_vector.length() != 0){
        anim.resume();
    }
    
//    Right
    if(move_vector.x > 0 && move_vector.y == 0){
        flip = SDL_FLIP_NONE;
        anim.set_state(2);
    }
//    Left
    else if(move_vector.x < 0 && move_vector.y == 0){
        flip = SDL_FLIP_HORIZONTAL;
        anim.set_state(2);
    }
//    Down
    else if(move_vector.x == 0 && move_vector.y > 0){
        flip = SDL_FLIP_NONE;
        anim.set_state(0);
    }
//    Up
    else if(move_vector.x == 0 && move_vector.y < 0){
        flip = SDL_FLIP_NONE;
        anim.set_state(1);
    }
//    Diag Up-Right
    else if(move_vector.x > 0 && move_vector.y < 0){
        flip = SDL_FLIP_NONE;
        anim.set_state(3);
    }
//    Diag Up-Left
    else if(move_vector.x < 0 && move_vector.y < 0){
        flip = SDL_FLIP_HORIZONTAL;
        anim.set_state(3);
    }
//    Diag Down-Right
    else if(move_vector.x > 0 && move_vector.y > 0){
        flip = SDL_FLIP_NONE;
        anim.set_state(4);
    }
//    Diag Down-Left
    else if(move_vector.x < 0 && move_vector.y > 0){
        flip = SDL_FLIP_HORIZONTAL;
        anim.set_state(4);
    }
    else anim.pause();
    
    bp[0].flip = flip;
    bp[0].src_rec = &this_frames[active_frame_index];
}

