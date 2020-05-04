//
//  Animator.cpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "Animator.hpp"
#include "Randomizer.hpp"
Animator::Animator(Uint8 n_frames, Uint8 n_states, ID::Anim_Modes mode, Uint8 start_index)
    :
    current_mode_{ mode },
    paused{false},
    current_anchor_{ 0 },
    current_frame_{ start_index },
    states_{ n_states },
    n_frames_{ n_frames },
    old_time_{ 0 },
    tpf_{ 130 },
    osc_up{ true },
    foil_step{ 1 }
{
    if (!n_frames%n_states) throw std::invalid_argument("Animation state- and frame number does not meet the requirement.");
    if (start_index > n_frames) throw std::invalid_argument("Start index of animator is greater than total amount of frames.");
}

void Animator::set_state(Uint8 new_anchor)
{
    if (new_anchor > states_-1) throw std::invalid_argument("Input value is not possible: Value too high! ");
    current_anchor_ = new_anchor*(n_frames_/states_);
}

void Animator::set_mode(ID::Anim_Modes mode)
{
    current_mode_ = mode;
}

void Animator::set_tpf(Uint16 tpf){
    tpf_= tpf;
}

void Animator::update()
{
    if (old_time_ + tpf_ > SDL_GetTicks() || paused) return;

    switch (current_mode_){
        case ID::Anim_Modes::ANIM_UP:
            current_frame_ = (current_frame_ >= n_frames_ / states_ - 1) ? 0 : current_frame_ + 1;
            break;
        case ID::Anim_Modes::ANIM_DOWN:
            current_frame_ = (current_frame_ == 0) ? n_frames_ / states_ - 1 : current_frame_ - 1;
            break;
        case ID::Anim_Modes::ANIM_OSC: {
            if (osc_up && current_frame_ >= n_frames_ / states_ - 1)
            {
                osc_up = false;
                current_frame_--;
            }
            else if (!osc_up && current_frame_ <= 0)
            {
                osc_up = true;
                current_frame_++;
            }
            else if (osc_up) current_frame_++;
            else if (!osc_up) current_frame_--;
            break;
        }
        case ID::Anim_Modes::ANIM_FOIL:
        {
            if (current_frame_ == 0) current_frame_ += foil_step;
            else current_frame_ = 0;
            if (current_frame_ + 1 >= n_frames_ / states_) foil_step = 1;
            else if (current_frame_ != 0)foil_step++;
            break;
        }
        case ID::Anim_Modes::ANIM_RAND: current_frame_ = Randomizer::random_int(0,n_frames_/states_-1);
    }
    old_time_ = SDL_GetTicks();
}
