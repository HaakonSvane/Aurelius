//
//  SpriteShadow.cpp
//  Aurelius
//
//  Created by Haakon Svane on 12/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#include "SpriteShadow.hpp"

SpriteShadow::SpriteShadow(const ID::SPRITES_ID _id, const Uint8 _cell_s, const Sprite& _owner, Vector2D<int> _offset)
:
Sprite(_id, _cell_s, false),
owner{_owner},
offset{_offset*CONSTANTS::SCALING}
{
    pos = owner.get_pos() + offset.to_float();
    colors_.insert(0, COLORS::BLACK);
    color_sprite();
    texture_mod.a = 100;
}

void SpriteShadow::update(const Uint32 dt){
    pos = owner.get_pos() + offset.to_float();
};
