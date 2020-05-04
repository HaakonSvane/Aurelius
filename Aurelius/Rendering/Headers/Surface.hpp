//
//  Surface.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <SDL2/SDL.h>
#include "Constants.hpp"
#include "Identifications.hpp"

class ColorPalette;
class Surface{
public:
    Surface();
    ~Surface();
    bool load_surface_from_file(const char* file_name);
    bool init_from_surface(SDL_Surface* surface);
    
    bool color_key();
    bool color_surface(const ColorPalette& cp);
    
    int get_width() const { return width_; }
    int get_height() const { return height_; }
    SDL_Surface* get_surface() const { return surf_; }
    void set_is_colored(const bool value) { is_col = value; }
    bool get_is_colored() const { return is_col ;}
    
private:
    
    int width_;
    int height_;
    SDL_Surface* surf_;
    bool is_col;
};
