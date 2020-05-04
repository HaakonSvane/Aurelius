//
//  Game.cpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "Game.hpp"
#include "Constants.hpp"
#include <iostream>
#include "TextureManager.hpp"


Game::Game(const char* title, int x_pos, int y_pos, bool fullscreen) {
    Uint32 flags = SDL_WINDOW_RESIZABLE;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) std::fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    else
    {
        window = SDL_CreateWindow(title, x_pos, y_pos, CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT, flags);
        if (window == nullptr) std::fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        else
        {
            SDL_SetHint(SDL_HINT_RENDER_VSYNC, 0);
            screen_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (screen_renderer == nullptr) std::fprintf(stderr, "Renderer not created! SDL_Error: %s\n", SDL_GetError());
            else {
                SDL_GL_SetSwapInterval(1);
                running = true;
                SDL_SetRenderDrawColor(screen_renderer, 0x00, 0x00, 0xFF, 0xFF);
                
                TextureManager::init(screen_renderer, window);
                m = new Map{TextureManager::get_map_surf(), TextureManager::get_map_overlay_surf()};
                l = new Level{renderer, cam, m};
                l->spawn_player({1000, 1000});
                

                for (int i = 0; i < CONSTANTS::PLAYERS; ++i) {
                    text.push_back(new Text(CONSTANTS::msg, (float)CONSTANTS::SCREEN_WIDTH/4, (float)CONSTANTS::SCREEN_HEIGHT/6, true));
                    text[i]->add_shadow();
                    text[i]->set_render_layer(ID::RENDER_LAYER::UI);
                }
                l->cam.set_target(l->players[0]);
                fps_text = new Text("FPS: 0", (int)CONSTANTS::SCREEN_WIDTH-350, 10, false);
                tick_text = new Text("TIC: 0", (int)CONSTANTS::SCREEN_WIDTH-350, 40, false);
                fps_text->add_shadow();
                fps_text->set_render_layer(ID::RENDER_LAYER::UI);
                tick_text->add_shadow();
                tick_text->set_render_layer(ID::RENDER_LAYER::UI);
                
                fps_timer.start();
                tick_timer.start();
                
                fps_clock.start();
                tick_clock.start();
                
            }
        }
    }
    
}

Game::~Game() {
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(screen_renderer);
    SDL_Quit();
    std::cout << "Successfully quit the game!\n";
    
}

void Game::run() {
    /*
     TICK LOOP
     */
    
    int dt = SDL_GetTicks();
    
    if(tick_clock.getTicks() > 1000.f/CONSTANTS::TICK_RATE){
        tick(tick_clock.getTicks());
        tick_clock.reset();
        tick_stats();
        handle_events();

    }

    /*
     RENDER LOOP
     */
    if(fps_clock.getTicks() > 1000.f/CONSTANTS::SCREEN_FPS_CAP){
        render();
        render_stats();
        fps_clock.reset();
    }
    
    
    dt = SDL_GetTicks() - dt;
    if(dt < 1000.f/CONSTANTS::MASTER_RATE) SDL_Delay(1000.f/CONSTANTS::MASTER_RATE-dt);
    else return;
}

void Game::handle_events()
{
    inp_h.update();
    if (inp_h.quit()) running = false;

    for (auto p: l->players){
        p->move(ID::Move_dirs::MOVE_NONE);
        if (inp_h.is_pressed(ID::KEY_UP)) p->move(ID::Move_dirs::MOVE_UP);
        if (inp_h.is_pressed(ID::KEY_LEFT)) p->move(ID::Move_dirs::MOVE_LEFT);
        if (inp_h.is_pressed(ID::KEY_DOWN)) p->move(ID::Move_dirs::MOVE_DOWN);
        if (inp_h.is_pressed(ID::KEY_RIGHT)) p->move(ID::Move_dirs::MOVE_RIGHT);
    }
}


void Game::render()
{
    SDL_SetRenderDrawColor(screen_renderer, COLOR_MAP.at(COLORS::BLACK).r,COLOR_MAP.at(COLORS::BLACK).g, COLOR_MAP.at(COLORS::BLACK).b, 0xFF);
    SDL_RenderClear(screen_renderer);

    l->cam.update();
    l->render();
    for (auto t : text) renderer.render_sprite(*t);
    

    renderer.render_sprite(*fps_text);
    renderer.render_sprite(*tick_text);
    SDL_RenderPresent(screen_renderer);
}

void Game::render_stats()
{
    if (counted_frames >= 10) {
        avg_fps = counted_frames / (fps_timer.getTicks() / 1000.f);
        counted_frames = 0;
        fps_timer.reset();
    }
    
    ++counted_frames;
}

void Game::tick(Uint32 dt)
{
    fps_text->set_text("FPS: " + std::to_string(avg_fps));
    tick_text->set_text("TIC: "+std::to_string(avg_trate));
    fps_text->update(dt);
    tick_text->update(dt);
    
    l->update(dt);
    
}
void Game::tick_stats()
{
    if (counted_ticks >= 20) {
        avg_trate = counted_ticks / (tick_timer.getTicks() / 1000.f);
        counted_ticks = 0;
        tick_timer.start();
//        std::cout << "Tickrate: " << avg_trate<< "\n";
    }
    ++counted_ticks;
}
