//
//  BigShadow.cpp
//  Aurelius
//
//  Created by Haakon Svane on 11/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#include "BigShadow.hpp"

BigShadow::BigShadow(const Sprite& _owner, Vector2D<int> _offset)
:
SpriteShadow(ID::SPRITES_ID::BIG_SHADOW, 32, _owner, _offset)
{}
