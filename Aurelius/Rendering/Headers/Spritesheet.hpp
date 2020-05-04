//
//  Spritesheet.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <SDL2/SDL.h>
#include "Vector2D.hpp"
#include "Constants.hpp"

class Surface;
class Spritesheet {
public:
    Spritesheet();
    void init(Surface* s);
    Surface* create_strip(Vector2D<int> start_stop, Uint8 dim=CONSTANTS::CELL_DIM) const;
    SDL_Rect* create_frames(Vector2D<int> start_stop, Uint8 dim=CONSTANTS::CELL_DIM) const;
private:
    int width_;
    int height_;
    Surface* surf_;
};
