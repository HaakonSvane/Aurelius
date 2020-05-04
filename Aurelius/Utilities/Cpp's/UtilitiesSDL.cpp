//
//  UtilitiesSDL.cpp
//  Aurelius
//
//  Created by Haakon Svane on 09/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#include "UtilitiesSDL.hpp"


SDL_Rect operator * (const SDL_Rect& rec, const int num){
    SDL_Rect r = rec;
    r.x -= (r.w*(num-1)/2);
    r.y -= (r.h*(num-1)/2);
    r.h = r.h*num;
    r.w = r.w*num;

    return r;
}

SDL_Rect operator * (const SDL_Rect& rec, const float num){
    SDL_Rect r = rec;
    const float a = r.w * (num - 1) / 2.f;
    const float b = r.h * (num - 1) / 2.f;
    r.x -= static_cast<int>(a);
    r.y -= static_cast<int>(b);
    r.h = static_cast<int>( r.h * num );
    r.w = static_cast<int>( r.w * num );

    return r;
}

