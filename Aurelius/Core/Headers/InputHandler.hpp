//
//  InputHandler.hpp
//  Aurelius
//
//  Created by Haakon Svane on 17/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <unordered_map>
#include "Identifications.hpp"

class InputHandler{
public:
    InputHandler(const ID::Controllers c);
    void update();
    bool quit() const {return q;};
    
    bool is_pressed(ID::Keys k);
    bool is_released(ID::Keys k);
    Uint32 key_time(ID::Keys k);
    Uint8 repeat(ID::Keys k);
    
    
private:
    const ID::Controllers mode;
    SDL_Event event;
    bool q;
    bool add_event(SDL_KeyboardEvent& value);
    std::unordered_map<ID::Keys, SDL_KeyboardEvent> key_map;

};
