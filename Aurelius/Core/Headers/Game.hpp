//
//  Game.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "LTimer.hpp"
#include "Text.hpp"
#include "Identifications.hpp"

#include "InputHandler.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "Map.hpp"
#include "Level.hpp"

class Game {
    
public:
    Game(const char* title, int x_pos, int y_pos, bool fullscreen);
    ~Game();
    
    void run();
    bool is_running() const { return running;
        
    };
    
    
private:
    void handle_events();
    
    void render();
    void render_stats();
    
    void tick(Uint32 dt);
    void tick_stats();
    
    bool running;
    
    SDL_Window* window = nullptr;
    SDL_Renderer* screen_renderer = nullptr;
    
    LTimer fps_timer;
    LTimer tick_timer;
    
    int counted_frames = 0;
    int counted_ticks = 0;
    float avg_fps = 0;
    float avg_trate = 0;
    
    LTimer fps_clock;
    LTimer tick_clock;
    
    
    Camera cam{SDL_Rect{0, 0, CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT}};
    Renderer renderer{cam};
    
    std::vector<Text*> text;
    
    Map* m;
    Level* l;
    Text* fps_text;
    Text* tick_text;
    
    InputHandler inp_h{ID::KEYBOARD_MOUSE};
    
};
