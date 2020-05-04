//
//  Camera.cpp
//  Aurelius
//
//  Created by Haakon Svane on 25/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(SDL_Rect viewport):
    init_pos{viewport.x, viewport.y}
{
    this->viewport = viewport;
    this->renderzone = (this->viewport) * rzone_padding;
    this->updatezone = (this->viewport) * uzone_padding;
    
    deadzone.w = deadzone_limit.x;
    deadzone.h = deadzone_limit.y;
    center_rect(deadzone, this->viewport);
    center_rect(renderzone, this->viewport);
    center_rect(updatezone, this->viewport);
    
}

void Camera::center_rect(SDL_Rect &target, SDL_Rect &ref){
    target.x = ref.x + static_cast<int>((ref.w-target.w)/2.f);
    target.y = ref.y + static_cast<int>((ref.h-target.h)/2.f);

}

void Camera::set_target(Sprite* t){
    target = t;
    following = true;
}

void Camera::clear_target(){
    target = nullptr;
    following = false;
}

void Camera::set_viewport(SDL_Rect vp){
    viewport = vp;
}

void Camera::update(){
    if (!target) clear_target();
    if (!following) return;
    
    if (target->get_center() > deadzone){
        Vector2D<int> delta = (target->get_center()-deadzone).to_int();
        deadzone.x += delta.x;
        deadzone.y += delta.y;
        center_rect(viewport, deadzone);
        center_rect(renderzone, viewport);
        center_rect(updatezone, viewport);
    }

}





