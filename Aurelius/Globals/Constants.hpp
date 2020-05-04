//
//  Constants.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace CONSTANTS {
    constexpr unsigned int SCREEN_WIDTH = 640*5/2;
    constexpr unsigned int SCREEN_HEIGHT = 480*4/2;
    constexpr int SCALING = 3;
    
    constexpr unsigned int BIT_DEPTH = 32;
    constexpr Uint8 BIT_DEPTH_ART = 8;
    
    constexpr unsigned int PLAYERS = 1;
    
    constexpr Uint16 SHEET_SIZE = 256;
    constexpr Uint8 CELL_DIM = 8;
    
    constexpr unsigned int TICK_RATE = 70;
    constexpr unsigned int SCREEN_FPS_CAP = 240;
    constexpr unsigned int MASTER_RATE = 600;
    
    auto constexpr STD_FORMAT = SDL_PIXELFORMAT_RGBA8888;
    const std::string msg = "(TESTING testing Haakon!)";
    
}
