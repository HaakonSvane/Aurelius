//
//  Map.hpp
//  Aurelius
//
//  Created by Haakon Svane on 25/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <vector>
#include <unordered_map>
#include "Surface.hpp"
#include "ColorManager.hpp"
#include "GrassBlock.hpp"
#include "WaterBlock.hpp"
#include "SandBlock.hpp"
#include "Tree.hpp"
#include "Renderer.hpp"

typedef std::tuple<ID::SPRITES_ID, ID::SPRITES_ID, ID::SPRITES_ID,
ID::SPRITES_ID> scan_tuple;
const std::unordered_map<Color, ID::SPRITES_ID> color_mapping{
    {{0x00, 0xFF, 0x00}, ID::SPRITES_ID::GRASS},
    {{0x00, 0x00, 0xFF}, ID::SPRITES_ID::WATER},
    {{0xFF, 0xFF, 0x00}, ID::SPRITES_ID::SAND},
    {{0xFF, 0x80, 0x00}, ID::SPRITES_ID::TREE}
};


class Sprite;
class Map{
public: 
    Map(const Surface* map_surface, const Surface* overlay_surface);
    ~Map();
    void update(Uint32 dt) const;
    
    std::vector<Sprite*> blocks;
private:

    ID::SPRITES_ID* tiles;
    ID::SPRITES_ID* world_objs;
    Vector2D<std::size_t> dim;
    
    scan_tuple scan_sides(ID::SPRITES_ID anchor, Vector2D<std::size_t> tile_number);
    void generate_map();
    void new_sprite(ID::SPRITES_ID id, Vector2D<std::size_t> tile_number, int f_frame = -1, SDL_RendererFlip f_flip = SDL_FLIP_NONE, float f_rot = 0.0);
    
    void edges_total_fill(ID::SPRITES_ID anchor, ID::SPRITES_ID fill, std::size_t i);
};
