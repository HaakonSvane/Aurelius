//
//  MobShadow.cpp
//  Aurelius
//
//  Created by Haakon Svane on 18/12/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "MediumShadow.hpp"

MediumShadow::MediumShadow(const Sprite& _owner, Vector2D<int> _offset)
:
SpriteShadow(ID::SPRITES_ID::MEDIUM_SHADOW, 16, _owner, _offset)
{}
