//
//  UtilitiesSDL.hpp
//  Aurelius
//
//  Created by Haakon Svane on 09/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#pragma once
#include "SDL2/SDL.h"

SDL_Rect operator * (const SDL_Rect& rec, const int num);

SDL_Rect operator * (const SDL_Rect& r, const float num);



