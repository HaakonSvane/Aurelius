//
//  BigShadow.hpp
//  Aurelius
//
//  Created by Haakon Svane on 11/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#pragma once
#include "SpriteShadow.hpp"

class BigShadow : public SpriteShadow{
public:
    BigShadow(const Sprite& owner, Vector2D<int> offset = {0, 0});
    
private:

};

