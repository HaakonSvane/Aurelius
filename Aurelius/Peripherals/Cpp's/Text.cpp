//
//  Text.cpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "Text.hpp"
#include <utility>

Text::Text(std::string txt, const int x, const int y, const bool frame)
    :
    Text(txt, static_cast<float>(x), static_cast<float>(y), frame)
{}

Text::Text(std::string txt, const float x, const float y, const bool frame)
    :
    Peripheral{ ID::SPRITES_ID::s8_LETTERS_SYMBOLS, 8, false},
    text_{std::move(txt)}
{
    pos.x = x;
    pos.y = y;
    colors_.insert(0, COLORS::WHITE);
    if (frame){
        attach_sprite(new ContainerFrame{
                      x-8*CONSTANTS::SCALING, y-8*CONSTANTS::SCALING, static_cast<int>(text_.length()*CONSTANTS::CELL_DIM), CONSTANTS::CELL_DIM
                      });
    }
    color_sprite();
    bp = builder_function();
}

Text::~Text()
{
}

builder_pack Text::builder_function() const{
    builder_pack bp{};
    const int s = CONSTANTS::SCALING;
    const int d = CONSTANTS::CELL_DIM;
    
    for (unsigned int i = 0; i < text_.length(); i++){
        const int index = ID::ASCII_CODES.at(text_.at(i));
        bp.push_back(BuilderItem
                     {Vector2D<float>{static_cast<float>(i * s * d), 0}, &this_frames[index], SDL_FLIP_NONE, 0.0});
    }
    return bp;
}

void Text::set_text(std::string txt){
    for (auto& t : attached_sprites){
        Text* tex = dynamic_cast<Text*>(t);
        if (tex != nullptr){
            tex->set_text(txt);
        }else continue;
    }
    text_ = txt;
}

void Text::add_shadow(){
    Text* t = new Text{text_, pos.x-CONSTANTS::SCALING, pos.y+CONSTANTS::SCALING, false};
    t->set_texture_mod(0, 0, 0, texture_mod.a);
    attach_sprite(t);
}

void Text::update(const Uint32 dt){
    for (auto& t : attached_sprites){
        t->update(dt);
    }
    bp = builder_function();
}

