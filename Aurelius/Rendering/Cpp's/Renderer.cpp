//
//  Renderer.cpp
//  Aurelius
//
//  Created by Haakon Svane on 18/12/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "Renderer.hpp"


Renderer::Renderer(const Camera& cam)
:
camera{cam}
{}

bool Renderer::render_sprite(const Sprite& sprite) const{
    //TODO: For testing only
    //if (sprite.get_center()>camera.get_viewport()*padding) return true;
    
    bool success = false;
    for (auto& s : sprite.attached_sprites) {render_sprite(*s);};
    

    Color mod = sprite.get_texture_mod();
    SDL_SetTextureColorMod(sprite.get_texture(), mod.r, mod.g, mod.b);
    SDL_SetTextureAlphaMod(sprite.get_texture(), mod.a);
    
    
    for (unsigned int i = 0; i < sprite.bp.size(); i++){
//        New render function loop goes here!
        Vector2D<int> pos = sprite.bp[i].d_pos.to_int() + sprite.get_pos().to_int();
        
        if (!(sprite.get_render_layer() == ID::RENDER_LAYER::UI) && pos > camera.get_renderzone()){
            continue;
        }
        SDL_Rect dest_rect;
        // TODO: Change this to layers
        if (sprite.get_render_layer() == ID::RENDER_LAYER::UI){
            dest_rect.x = pos.x;
            dest_rect.y = pos.y;
        }else{
            dest_rect.x = pos.x-camera.get_delta_pos().x;
            dest_rect.y = pos.y-camera.get_delta_pos().y;
        }
        
        dest_rect.w = sprite.get_cell_size()*CONSTANTS::SCALING;
        dest_rect.h = sprite.get_cell_size()*CONSTANTS::SCALING;
        success = SDL_RenderCopyEx(TextureManager::get_renderer(), sprite.get_texture(), sprite.bp[i].src_rec, &dest_rect, sprite.bp[i].rot, NULL, sprite.bp[i].flip);
    }
    
    return success;
}

