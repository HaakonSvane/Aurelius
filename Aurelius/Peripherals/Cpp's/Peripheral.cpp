//
//  Peripheral.cpp
//  Aurelius
//
//  Created by Haakon Svane on 27/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "Peripheral.hpp"

Peripheral::Peripheral(const ID::SPRITES_ID _id, const Uint8 _cell_s, const bool _volatile_coloring) :
    Sprite{ _id, _cell_s, _volatile_coloring}
{}
