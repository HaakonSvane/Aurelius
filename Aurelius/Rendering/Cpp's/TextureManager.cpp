//
//  TextureManager.cpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "TextureManager.hpp"
#include <string>
#include <iostream>
#include "Constants.hpp"


namespace TextureManager{
    namespace {
        Surface PERI_surf, MOBS_surf, BLOC_surf, SCEN_surf, EFFE_surf, MAP_surf, MAP_OVERLAY_surf;
        Spritesheet PERI_sheet, MOBS_sheet, BLOC_sheet, SCEN_sheet, EFFE_sheet;
        SDL_Renderer* rend = NULL;
    }

    const Surface* get_peripherals_surf() { return &PERI_surf; };
    const Surface* get_mobs_surf() { return &MOBS_surf; };
    const Surface* get_blocks_surf() { return &BLOC_surf; };
    const Surface* get_scenery_surf() {return &SCEN_surf;};
    const Surface* get_effects_surf() { return &EFFE_surf; };
    const Surface* get_map_surf() {return &MAP_surf; };
    const Surface* get_map_overlay_surf() {return &MAP_OVERLAY_surf; };

    const Spritesheet* get_peripherals_ssheet() { return &PERI_sheet; };
    const Spritesheet* get_mobs_ssheet() { return &MOBS_sheet; };
    const Spritesheet* get_blocks_ssheet() { return &BLOC_sheet; };
    const Spritesheet* get_scenery_ssheet() { return &SCEN_sheet; };
    const Spritesheet* get_effects_ssheet() { return &EFFE_sheet; };


    SDL_Renderer* get_renderer() { return rend; };
    

    void init(SDL_Renderer* ren, SDL_Window* win) {
        
        rend = ren;
        
        PERI_surf.load_surface_from_file("Assets/Peripherals_Sheet.png");
        PERI_surf.color_key();
        PERI_sheet.init(&PERI_surf);
        
        
        MOBS_surf.load_surface_from_file("Assets/Mobs_Sheet.png");
        MOBS_surf.color_key();
        MOBS_sheet.init(&MOBS_surf);
        
        
        BLOC_surf.load_surface_from_file("Assets/Blocks_Sheet.png");
        BLOC_surf.color_key();
        BLOC_sheet.init(&BLOC_surf);
        
        SCEN_surf.load_surface_from_file("Assets/Scenery_Sheet.png");
        SCEN_surf.color_key();
        SCEN_sheet.init(&SCEN_surf);
        
        EFFE_surf.load_surface_from_file("Assets/Effects_Sheet.png");
        EFFE_surf.color_key();
        EFFE_sheet.init(&EFFE_surf);
        
        MAP_surf.load_surface_from_file("Assets/Maps/Map_test/Map_Test.png");
        MAP_OVERLAY_surf.load_surface_from_file("Assets/Maps/Map_test/Map_Test_OVERLAY.png");
        
        
        
    }

    Surface* get_surf_from_id(const ID::SPRITES_ID id){
        switch (ID::SPRITE_TYPES.at(id)){
            case ID::TYPES::MOBS: return &MOBS_surf; break;
            case ID::TYPES::BLOCKS: return &BLOC_surf; break;
            case ID::TYPES::SCENERY: return &SCEN_surf; break;
            case ID::TYPES::PERIPHERALS: return &PERI_surf; break;
            case ID::TYPES::EFFECTS: return &EFFE_surf; break;
                
            default: throw std::invalid_argument("Could not fetch surface from ID: "+ID::ID_to_string(id)+". ");
        }
    }

    Spritesheet* get_sheet_from_id(const ID::SPRITES_ID id){
        switch (ID::SPRITE_TYPES.at(id)){
            case ID::TYPES::MOBS: return &MOBS_sheet; break;
            case ID::TYPES::BLOCKS: return &BLOC_sheet; break;
            case ID::TYPES::SCENERY: return &SCEN_sheet; break;
            case ID::TYPES::PERIPHERALS: return &PERI_sheet; break;
            case ID::TYPES::EFFECTS: return &EFFE_sheet; break;
                
            default: throw std::invalid_argument("Could not fetch sheet from ID: "+ ID::ID_to_string(id)+". ");
        }
    }

}




