//
//  MediumShadow.hpp
//  Aurelius
//
//  Created by Haakon Svane on 18/12/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include "SpriteShadow.hpp"

class MediumShadow : public SpriteShadow{
public:
    MediumShadow(const Sprite& owner, Vector2D<int> offset = {0, 0} );
    
private:

};
