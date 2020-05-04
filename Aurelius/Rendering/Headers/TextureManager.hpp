//
//  TextureManager.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <SDL2/SDL.h>
#include "Surface.hpp"
#include "Spritesheet.hpp"
#include "unordered_map"
#include "Identifications.hpp"


namespace TextureManager{

    void init(SDL_Renderer* ren, SDL_Window* win);

    const Surface* get_peripherals_surf();
    const Surface* get_mobs_surf();
    const Surface* get_blocks_surf();
    const Surface* get_effects_surf();
    const Surface* get_map_surf();
    const Surface* get_map_overlay_surf();

    const Spritesheet* get_peripherals_ssheet();
    const Spritesheet* get_mobs_ssheet();
    const Spritesheet* get_blocks_ssheet();
    const Spritesheet* get_effects_ssheet();


    SDL_Renderer* get_renderer();

    Surface* get_surf_from_id(const ID::SPRITES_ID id);
    Spritesheet* get_sheet_from_id(const ID::SPRITES_ID id);

}

