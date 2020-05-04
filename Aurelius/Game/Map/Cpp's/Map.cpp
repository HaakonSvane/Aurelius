//
//  Map.cpp
//  Aurelius
//
//  Created by Haakon Svane on 25/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "Map.hpp"
#include <iostream>

Map::~Map(){
    for (auto s : blocks){
        delete s;
        s = nullptr;
    }
    delete[] tiles;
    delete[] world_objs;
    blocks.clear();
}

Map::Map(const Surface* map_surface, const Surface* overlay_surface):
tiles{new ID::SPRITES_ID[map_surface->get_height()*map_surface->get_width()]},
world_objs{new ID::SPRITES_ID[overlay_surface->get_height()*overlay_surface->get_width()]}
{
    if (map_surface->get_height() != overlay_surface->get_height() || map_surface->get_width() != overlay_surface->get_width()) throw std::invalid_argument("ERROR: Map surfaces does not match in dimentions\n");
    SDL_Surface* map_surf = map_surface->get_surface();
    SDL_Surface* overlay_surf = overlay_surface->get_surface();
    if (SDL_LockSurface(map_surf) < 0 || SDL_LockSurface(overlay_surf) < 0){
       std::fprintf(stderr, "Could not lock map surface(s) for scanning. Error: %s \n", SDL_GetError());
    }
    else
    {
        // Scans the map suface and inserts a SPRITES_ID into each tile
        Uint32* pixels_map = static_cast<Uint32*>(map_surf->pixels);
        dim.x = (map_surf->pitch / 4);
        dim.y = map_surf->h;
        for (int i = 0; i < dim.x*dim.y; ++i)
       {
           auto n = color_mapping.find(ColorFunctions::Uint32_to_Color(pixels_map[i]));
           int x = i%dim.x;
           int y = i/dim.y;
           if (n != color_mapping.end()){
               tiles[y*dim.y+x]=n->second;
           } else{
               tiles[y*dim.y +x] = ID::SPRITES_ID::NONE;
           }
       }
        
        Uint32* pixels_overlay = static_cast<Uint32*>(overlay_surf->pixels);
        dim.x = (overlay_surf->pitch / 4);
        dim.y = overlay_surf->h;
        for (int i = 0; i < dim.x*dim.y; ++i)
        {
            auto n = color_mapping.find(ColorFunctions::Uint32_to_Color(pixels_overlay[i]));
            int x = i%dim.x;
            int y = i/dim.y;
            if (n != color_mapping.end()){
                world_objs[y*dim.y + x]=n->second;
            }else{
                world_objs[y*dim.y + x] = ID::SPRITES_ID::NONE;
            }
        }
        
      
        SDL_UnlockSurface(map_surf);
        SDL_UnlockSurface(overlay_surf);
        generate_map();
    }
}

// Scans closest 4 blocks and inserts them into an array. Ordered clockwise starting from the North block.
scan_tuple Map::scan_sides(ID::SPRITES_ID a, Vector2D<std::size_t> tn){
    // Create an array of size 4 to fill with block ID's
    ID::SPRITES_ID d[4];
    // The 4 positions to be checked (tile-coordinates relative to tn)
    Vector2D<int> p[4]{{0,-1},{1,0},{0,1},{-1,0}};
    
    for (int i = 0; i < 4; i++){
        Vector2D<int> v{p[i]+tn.to_int()};
        // If any of the directions checked are outside of the map, insert the dummy ID "NONE"
        if(v.x < 0 || v.x > dim.x-1 || v.y < 0 || v.y > dim.y-1){
            d[i] = ID::SPRITES_ID::NONE;
        }
        else{
            d[i] = tiles[v.y*dim.y+v.x];
        }

    }
    
    return std::make_tuple(d[0], d[1], d[2], d[3]);
}

void Map::generate_map(){
    // First pass of the generation spawns the square blocks as they are drawn in the bitmap
    for (std::size_t i = 0; i < dim.x*dim.y; i++){
        std::size_t x = i%dim.x;
        std::size_t y = i/dim.y;
        new_sprite(tiles[y*dim.y+x], {x, y});
    }
    
    // Second pass of the generation overlays edges using edges_total_fill() [every side is overlayed]
    for (std::size_t i = 0; i < dim.x*dim.y; i++){
        edges_total_fill(ID::SPRITES_ID::SAND, ID::SPRITES_ID::GRASS, i);
        edges_total_fill(ID::SPRITES_ID::WATER, ID::SPRITES_ID::SAND, i);
        }
    
    // Third pass of the generation adds the overlay map.
    for (std::size_t i = 0; i < dim.x*dim.y; i++){
        std::size_t x = i%dim.x;
        std::size_t y = i/dim.y;
        new_sprite(world_objs[y*dim.y+x], {x, y});
    }

}
void Map::new_sprite(ID::SPRITES_ID id, Vector2D<std::size_t> tile_number, int f_frame, SDL_RendererFlip f_flip, float f_rot){
    int x = tile_number.x*CONSTANTS::SCALING*16;
    int y = tile_number.y*CONSTANTS::SCALING*16;
    
    switch(id){
        case ID::SPRITES_ID::GRASS : blocks.push_back(new GrassBlock{x, y, f_frame, f_flip, f_rot}); break;
        case ID::SPRITES_ID::WATER : blocks.push_back(new WaterBlock{x, y}); break;
        case ID::SPRITES_ID::SAND : blocks.push_back(new SandBlock{x, y, f_frame, f_flip, f_rot}); break;
        case ID::SPRITES_ID::TREE : blocks.push_back(new Tree{x, y, f_frame, f_flip, f_rot}); break;
    }
    blocks.back()->set_render_layer(ID::RENDER_LAYER::TILE);
}

void Map::update(Uint32 dt) const{
    for (auto& b : blocks){
        b->update(dt);
    }
}


void Map::edges_total_fill(ID::SPRITES_ID anchor, ID::SPRITES_ID fill, std::size_t i){
    
    std::size_t x = i%dim.x;
    std::size_t y = i/dim.y;
    ID::SPRITES_ID a = tiles[y*dim.y+x];

    if (a == anchor){
        scan_tuple s = scan_sides(a, {x,y});
        bool north = std::get<0>(s) == fill;
        bool east = std::get<1>(s) == fill;
        bool south = std::get<2>(s) == fill;
        bool west = std::get<3>(s) == fill;

        
//        1 BLOCK
        if (north && !east && !south && !west){
            new_sprite(fill, {x, y}, 3, SDL_FLIP_NONE);
        }
        else if(!north && east && !south && !west){
            new_sprite(fill, {x, y}, 3, SDL_FLIP_NONE, 90.0);
        }
        else if(!north && !east && south && !west){
            new_sprite(fill, {x, y}, 3, SDL_FLIP_VERTICAL);
        }
        else if(!north && !east && !south && west){
            new_sprite(fill, {x, y}, 3, SDL_FLIP_NONE, 270.0);
        }
        
//        2 BLOCKS
        else if(north && east && !south && !west){
            new_sprite(fill, {x, y}, 4, SDL_FLIP_HORIZONTAL);
        }
        else if(!north && east && south && !west){
            new_sprite(fill, {x, y}, 4, static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL|SDL_FLIP_VERTICAL));
        }
        else if(!north && !east && south && west){
            new_sprite(fill, {x, y}, 4, SDL_FLIP_VERTICAL);
        }
        else if(north && !east && !south && west){
            new_sprite(fill, {x, y}, 4, SDL_FLIP_NONE);
        }
        else if(north && !east && south && !west){
            new_sprite(fill, {x, y}, 3, SDL_FLIP_NONE);
            new_sprite(fill, {x, y}, 3, SDL_FLIP_VERTICAL);
        }
        else if(!north && east && !south && west){
            new_sprite(fill, {x, y}, 3, SDL_FLIP_NONE, 90.0);
            new_sprite(fill, {x, y}, 3, SDL_FLIP_VERTICAL, 90.0);
        }
        
//        3 BLOCKS
        else if(north && east && south && !west){
            new_sprite(fill, {x, y}, 4, SDL_FLIP_HORIZONTAL);
            new_sprite(fill, {x, y}, 4, static_cast<SDL_RendererFlip>(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL));
        }
        else if(north && east && !south && west){
            new_sprite(fill, {x, y}, 4, SDL_FLIP_NONE);
            new_sprite(fill, {x, y}, 4, SDL_FLIP_HORIZONTAL);
        }
        else if(north && !east && south && west){
            new_sprite(fill, {x, y}, 4, SDL_FLIP_NONE);
            new_sprite(fill, {x, y}, 4, SDL_FLIP_VERTICAL);
        }
        else if(!north && east && south && west){
            new_sprite(fill, {x, y}, 4, SDL_FLIP_VERTICAL);
            new_sprite(fill, {x, y}, 4, static_cast<SDL_RendererFlip>(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL));
        }
//        4 BLOCKS
        else if(north && east && south && west){
            new_sprite(fill, {x, y}, 4, SDL_FLIP_NONE);
            new_sprite(fill, {x, y}, 4, static_cast<SDL_RendererFlip>(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL));
        }
    }
}
