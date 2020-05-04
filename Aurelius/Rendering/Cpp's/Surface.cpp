//
//  Surface.cpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include <cstdio>
#include <string>
#include "SDL2_image/SDL_image.h"
#include <stdexcept>
#include "Surface.hpp"
#include "ColorManager.hpp"


Surface::Surface()
:
height_{0},
width_{0},
surf_{nullptr},
is_col{false}
{
}

Surface::~Surface()
{
    SDL_FreeSurface(surf_);
    surf_ = nullptr;
}

bool Surface::load_surface_from_file(const char * file_name)
{
    bool success = false;
    SDL_Surface* temp = IMG_Load(file_name);
    if (!temp){
        throw std::runtime_error("Image could not be loaded. Did you specify a bad path?\n");
    }
    surf_ = SDL_ConvertSurfaceFormat(temp, CONSTANTS::STD_FORMAT, 0);
    if (!surf_){
        throw std::runtime_error(std::string{"Could not convert surface. Error:\n"} + std::string{IMG_GetError()});
    }
    SDL_FreeSurface(temp);
    SDL_SetSurfaceBlendMode(surf_, SDL_BLENDMODE_BLEND);
    
    if (surf_ == nullptr) {
        
        std::fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", file_name, IMG_GetError());
        success = false;
    }
    width_ = surf_->w;
    height_ = surf_->h;
    
    if (SDL_SetSurfaceRLE(surf_, 1) < 0){
        std::fprintf(stderr, "Could set the surface to use RLE. Error: %s", SDL_GetError());
        success = false;
    }
    
    return success;
}


bool Surface::init_from_surface(SDL_Surface * surface)
{
    bool success = true;
    if (surf_ != nullptr) {
        throw std::invalid_argument("SDL_Surface object is already instantiated for this instance.. you fuck.");
    }
    else {
        SDL_Surface* temp = surface;
        surf_ = SDL_ConvertSurfaceFormat(temp, CONSTANTS::STD_FORMAT, 0);
        if (!surf_) std::fprintf(stderr, "Could not convert given surface format. Error: %s", SDL_GetError());
        
        SDL_FreeSurface(temp);
        
        if (SDL_SetSurfaceBlendMode(surf_, SDL_BLENDMODE_BLEND) < 0){
            std::fprintf(stderr, "Could set the surface blend mode. Error: %s", SDL_GetError());
            success = false;
        }
        
        width_ = surface -> w;
        height_ = surface -> h;
        if (SDL_SetSurfaceRLE(surf_, 1) < 0){
            std::fprintf(stderr, "Could set the surface to use RLE. Error: %s", SDL_GetError());
            success = false;
        }
        
    }
    return success;
}

bool Surface::color_key()
{
    bool success = true;
    const Uint32 color_white = SDL_MapRGB(surf_->format, KeyColors[7], KeyColors[7], KeyColors[7]);
    if (SDL_LockSurface(surf_) < 0){
        std::fprintf(stderr, "Could not lock surface for coloring. Error: %s", SDL_GetError());
        success = false;
    }
    if (SDL_SetColorKey(surf_, SDL_RLEACCEL, color_white) < 0){
        std::fprintf(stderr, "Could not color-key the surface. Error: %s", SDL_GetError());
        success = false; 
    }
    SDL_UnlockSurface(surf_);
    
    return success;
}

bool Surface::color_surface(const ColorPalette& cp){
    bool success = true;
    if (SDL_LockSurface(surf_) < 0){
        std::fprintf(stderr, "Could not lock surface for coloring. Error: %s", SDL_GetError());
        success = false;
    }
    else
    {
        Uint32* pixels = static_cast<Uint32*>(surf_->pixels);
        const int pixel_count = (surf_->pitch / 4) * surf_->h;
        SDL_PixelFormat* format = surf_->format;
        
        for (int i = 0; i < pixel_count; ++i)
        {
            if (pixels[i]%(0xFF+1) != 0)
            {
                for (int n = 0; n < CONSTANTS::BIT_DEPTH_ART; ++n)
                {
                    if (pixels[i] == SDL_MapRGB(format, KeyColors[n], KeyColors[n], KeyColors[n])) // Mulig slowdown med MapRGB hver gang her?
                    {
                        pixels[i] = cp.get_color(n);
                        break;
                    }
                }
            }
        }
        SDL_UnlockSurface(surf_);
    }
    return success;
}
