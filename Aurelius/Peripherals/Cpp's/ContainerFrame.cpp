//
//  ContainerFrame.cpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "ContainerFrame.hpp"
ContainerFrame::ContainerFrame(const int x, const int y, const int width, const int height)
    :
    ContainerFrame::ContainerFrame(static_cast<float>(x), static_cast<float>(y), width, height)
{}
ContainerFrame::ContainerFrame(const float x, const float y, int width, int height)
    :
    Peripheral(ID::SPRITES_ID::CONTAINER_FRAME, 16, false),
    width_{width},
    height_{height}
{
    pos.x = x;
    pos.y = y;
    colors_.insert(0, COLORS::dGREEN);
    colors_.insert(1, COLORS::dBLUE);
    colors_.insert(3, COLORS::lBLUE);
    colors_.insert(4, COLORS::lBLUE);
    
    color_sprite();
    bp = builder_function();
}


builder_pack ContainerFrame::builder_function() const {
    builder_pack bp{};
    const int d = CONSTANTS::CELL_DIM;
    const int s = CONSTANTS::SCALING;
    const int y = height_ / d;
    const int x = width_ / d;
    for(int j = 0; j < y+1; ++j)
    {
        for (int i = 0; i < x+1; ++i)
        {
            if(i == 0 && j == 0){
                bp.push_back(BuilderItem{Vector2D<float>{0, 0}, &this_frames[0], SDL_FLIP_NONE, 0.0});
            }
            else if(i == x && j == 0){
                bp.push_back(BuilderItem{Vector2D<float>{static_cast<float>(x*d*s), 0}, &this_frames[0], SDL_FLIP_HORIZONTAL, 0.0});
            }
            else if(i == 0 && j == y){
                bp.push_back(BuilderItem{Vector2D<float>{0, static_cast<float>(y*d*s)}, &this_frames[0], SDL_FLIP_VERTICAL, 0.0});
            }
            else if (i == x && j == y){
                bp.push_back(BuilderItem{Vector2D<float>{static_cast<float>(x*d*s), static_cast<float>(y*d*s)}, &this_frames[0], static_cast<SDL_RendererFlip>(SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL), 0.0});
            }
            else if (j == 0){
                bp.push_back(BuilderItem{Vector2D<float>{static_cast<float>(i*d*s), 0}, &this_frames[1], SDL_FLIP_NONE, 0.0});
            }
            else if (j == y){
                bp.push_back(BuilderItem{Vector2D<float>{static_cast<float>(i*d*s), static_cast<float>(y*d*s)}, &this_frames[1], SDL_FLIP_VERTICAL, 0.0});
            }
        }
    }
    return bp;
}

