//
//  InputHandler.cpp
//  Aurelius
//
//  Created by Haakon Svane on 17/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "InputHandler.hpp"
#include <iostream>

InputHandler::InputHandler(const ID::Controllers c)
    :
    mode{c},
    q{false}
{
}
void InputHandler::update(){
    while(SDL_PollEvent(&event)){
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ) add_event(event.key);
        else if (event.type == SDL_QUIT) q = true;
    }
}

bool InputHandler::is_pressed(ID::Keys k){
    if(key_map.find(k) != key_map.end()) return key_map[k].type == SDL_KEYDOWN;
    else return false;
}

bool InputHandler::is_released(ID::Keys k){
    if(key_map.find(k) != key_map.end()) return key_map[k].type == SDL_KEYUP;
    else return false;
}

Uint32 InputHandler::key_time(ID::Keys k){
    if(key_map.find(k) != key_map.end()) return key_map[k].timestamp;
    else return 0;
}

Uint8 InputHandler::repeat(ID::Keys k){
    if(key_map.find(k) != key_map.end()) return key_map[k].repeat;
    else return 0;
}



bool InputHandler::add_event(SDL_KeyboardEvent& value){
    if(ID::KEYBOARD_MAP.find(value.keysym.sym) != ID::KEYBOARD_MAP.end()){
        key_map[ID::KEYBOARD_MAP.at(value.keysym.sym)] = value;
        return true;
    }else return false;
}
