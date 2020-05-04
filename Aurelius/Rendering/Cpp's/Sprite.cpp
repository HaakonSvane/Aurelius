//
//  Sprite.cpp
//  Aurelius
//
//  Created by Haakon Svane on 26/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "Sprite.hpp"
#include <iostream>

std::unordered_map<ID::SPRITES_ID, Surface*> Sprite::self_surfaces_map;
std::unordered_map<ID::SPRITES_ID, SDL_Texture*> Sprite::self_textures_map;
std::unordered_map<ID::SPRITES_ID, SDL_Rect*> Sprite::self_frames_map;


BuilderItem::BuilderItem()
:
BuilderItem{Vector2D<float>{0,0}, nullptr, SDL_FLIP_NONE, 0.0}
{}

BuilderItem::BuilderItem(Vector2D<float> _d_pos, SDL_Rect* _src_rec, SDL_RendererFlip _flip, float _rot)
:
d_pos{_d_pos},
src_rec{_src_rec},
flip{_flip},
rot{_rot}
{}

Sprite::Sprite(const ID::SPRITES_ID id, const Uint8 cell_s, bool volatile_coloring)
    :
    id_{id},
    pos{0, 0},
    cell_size{cell_s},
    volatile_colors(volatile_coloring),
    active_frame_index{0},
    texture_mod{255, 255, 255, 255},
    flip{SDL_FLIP_NONE},
    render_layer{ID::RENDER_LAYER::NONE}
{
    this_texture = nullptr;
    this_frames = nullptr;
    
    // Default builder pack for all sprites. Specific builder instructions are specified in inherited classes
    bp = builder_function();
    
}

Sprite::~Sprite()
{
    if(volatile_colors){
        SDL_DestroyTexture(this_texture);
        this_texture = nullptr;
    }
    for (auto s : attached_sprites){
        delete s;
        s = nullptr;
    }
}


builder_pack Sprite::builder_function() const{
    
//  If no builder function is specified for the specific sprite, return
    return builder_pack{BuilderItem(Vector2D<float>{0, 0}, &this_frames[active_frame_index],
        flip, 0.0)};
}

const Vector2D<float> Sprite::get_center() const{
    Vector2D<float> m{cell_size*CONSTANTS::SCALING/2.f, cell_size*CONSTANTS::SCALING/2.f};
    return pos + m;
}

void Sprite::set_texture_mod(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    texture_mod.r = r;
    texture_mod.g = g;
    texture_mod.b = b;
    texture_mod.a = a;
}
void Sprite::set_render_layer(ID::RENDER_LAYER rl){
    render_layer = rl;
    for (auto s : attached_sprites) s->set_render_layer(rl);
}

bool Sprite::color_sprite()
{
    bool success = true;
    
    if ((self_surfaces_map.find(id_) == self_surfaces_map.end()) && (self_frames_map.find(id_) == self_frames_map.end())){
        self_surfaces_map[id_] = TextureManager::get_sheet_from_id(id_)->create_strip(ID::SPRITESHEET_LOC.at(id_), cell_size);
        this_frames = TextureManager::get_sheet_from_id(id_)->create_frames(ID::SPRITESHEET_LOC.at(id_), cell_size);
        self_frames_map[id_] = this_frames;
        std::cerr << "Sprite with ID: " << ID::ID_to_string(id_) << " does not have a surface and frames already.\n";
    }
    else{
        this_frames = self_frames_map[id_];
    }
    
    Surface* colored_surf = nullptr;
    if(!volatile_colors){
        colored_surf = self_surfaces_map[id_];
    }
    else{
        colored_surf = TextureManager::get_sheet_from_id(id_)->create_strip(ID::SPRITESHEET_LOC.at(id_), cell_size);
        if (colored_surf == NULL){
            success = false;
            std::cerr << "Could not allocate new RGB surface for coloring. Error: " << SDL_GetError() << "\n";
        }
    }

    if(self_textures_map.find(id_) == self_textures_map.end()){
        success = colored_surf->color_surface(colors_);
        if (!volatile_colors){
            self_textures_map[id_] = SDL_CreateTextureFromSurface(TextureManager::get_renderer(), colored_surf->get_surface());
            this_texture = self_textures_map[id_];
        }
        else{
            this_texture = SDL_CreateTextureFromSurface(TextureManager::get_renderer(), colored_surf->get_surface());
        }
        std::cerr << "Sprite with ID: " << ID::ID_to_string(id_) << " needs color and will be colored. \n";
    }
    else{
        this_texture = self_textures_map[id_];
    }

    if(volatile_colors) delete colored_surf;
    
    return success;
}


void Sprite::attach_sprite(Sprite *s){
    attached_sprites.push_back(s);
}
