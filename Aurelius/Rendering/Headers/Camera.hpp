//
//  Camera.hpp
//  Aurelius
//
//  Created by Haakon Svane on 25/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include "Sprite.hpp"
#include "UtilitiesSDL.hpp"

class Camera{
public:
    Camera(SDL_Rect viewport);
    bool is_following() const{return following;};
    const Sprite* get_target() const{ return target;};
    SDL_Rect get_viewport() const {return viewport;};
    SDL_Rect get_deadzone() const {return deadzone;};
    SDL_Rect get_renderzone() const {return renderzone;};
    SDL_Rect get_updatezone() const {return updatezone;};
    const Vector2D<int> get_delta_pos() const {return Vector2D<int>{viewport.x-init_pos.x, viewport.y-init_pos.y};};
    
    void set_viewport(SDL_Rect vp);
    void set_target(Sprite* t);
    void clear_target();
    void update();
    
private:
    void center_rect(SDL_Rect& target, SDL_Rect& reference);
    const Vector2D<int> init_pos;
    
    SDL_Rect viewport;
    SDL_Rect deadzone;
    SDL_Rect renderzone;
    SDL_Rect updatezone;
    
    const Vector2D<int> deadzone_limit{50, 50};
    const float rzone_padding = 1.2f;
    const float uzone_padding = 1.3f;

    
    bool following;
    Sprite* target;
};
