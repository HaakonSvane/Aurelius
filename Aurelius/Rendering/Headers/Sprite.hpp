///
//  Sprite.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include "Constants.hpp"
#include "Identifications.hpp"
#include "TextureManager.hpp"
#include "Spritesheet.hpp"
#include "Surface.hpp"
#include "ColorManager.hpp"

// ikke i bruk enda
struct SpriteData{
    SpriteData(Surface* s, SDL_Texture* t, SDL_Rect* f): surface{s}, texture{t}, frames{f}{};
    Surface* surface;
    SDL_Texture* texture;
    SDL_Rect* frames;
};

struct BuilderItem{
    
    Vector2D<float> d_pos;
    SDL_Rect* src_rec;
    SDL_RendererFlip flip;
    float rot;
    
    BuilderItem();
    BuilderItem(Vector2D<float> pos, SDL_Rect* src_rec, SDL_RendererFlip flip, float rot);
//    BuilderItem(const BuilderItem& bi);
    
};

typedef std::tuple<Vector2D<float>, SDL_Rect*, SDL_RendererFlip, float> builder_tuple;
typedef std::vector<BuilderItem> builder_pack;


class Sprite {
public:
    // TODO: Should these be public??
    builder_pack bp;
    std::vector<Sprite*> attached_sprites;
    
    Sprite(const ID::SPRITES_ID id, const Uint8 cell_size, const bool volatile_coloring);
    virtual ~Sprite();
    
    virtual void update(const Uint32 dt) = 0;
    
    void set_texture_mod(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void set_render_layer(ID::RENDER_LAYER rl);
    void attach_sprite(Sprite* s);
    
    const Vector2D<float> get_pos() const {return pos;};

    const Vector2D<float> get_center() const;
    
    SDL_Texture* get_texture() const {return this_texture;};
    
    const ID::SPRITES_ID get_id() const{return id_ ;};
    const ID::TYPES get_type() const {return ID::SPRITE_TYPES.at(id_);};
    const Uint8 get_cell_size() const{return cell_size;};
    const Color get_texture_mod() const {return texture_mod;};
    
    const ID::RENDER_LAYER get_render_layer() const {return render_layer;};
//    std::vector<Sprite*> get_attached_sprites() const {return attached_sprites;};

    
protected:
    virtual builder_pack builder_function() const;
    const ID::SPRITES_ID id_;
    SDL_Rect* this_frames;
    Uint8 active_frame_index;
    
    SDL_Texture* this_texture;
    Color texture_mod;
    ColorPalette colors_;
    
    
    Vector2D<float> pos;
    
    ID::RENDER_LAYER render_layer;
    SDL_RendererFlip flip;
    
    bool color_sprite();
    
private:
    const Uint8 cell_size;
    bool volatile_colors;
    static std::unordered_map<ID::SPRITES_ID, Surface*> self_surfaces_map;
    static std::unordered_map<ID::SPRITES_ID, SDL_Texture*> self_textures_map;
    static std::unordered_map<ID::SPRITES_ID, SDL_Rect*> self_frames_map;
    
//    static std::unordered_map<ID::SPRITES_ID, SpriteData> sprite_data_map;
};







