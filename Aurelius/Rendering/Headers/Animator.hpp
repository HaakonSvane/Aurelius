//
//  Animator.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <SDL2/SDL.h>
#include "Identifications.hpp"
#include <random>

class Animator
{
public:
    Animator( Uint8 n_frames, Uint8 n_states, ID::Anim_Modes mode = ID::Anim_Modes::ANIM_UP, Uint8 start_index = 0);
    
    void set_state(Uint8 new_anchor);
    void set_mode(ID::Anim_Modes mode);
    void set_tpf(Uint16 tpf);
    void pause(){paused = true;};
    void resume(){paused = false;};
    
    void update();
    Uint8 current_frame() const { return current_frame_+current_anchor_; };
    
private:
    ID::Anim_Modes current_mode_;
    bool paused;
    Uint8 current_anchor_;
    Uint8 current_frame_;
    Uint8 states_;
    Uint8 n_frames_;
    Uint32 old_time_;
    Uint16 tpf_;
    
    bool osc_up;
    Uint8 foil_step;
};



