//
//  Level.cpp
//  Aurelius
//
//  Created by Haakon Svane on 09/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#include "Level.hpp"

Level::Level(const Renderer& _ren, Camera& _cam, const Map* _map):
cam{_cam},
map{_map},
ren{_ren}
{}

Level::~Level(){
    for (auto& p : players){
        delete p;
        p = nullptr;
    }
    players.clear();
}

void Level::render() const {
    for (auto& b : map->blocks){
        ren.render_sprite(*b);
    }
    for (auto& p : players){
        ren.render_sprite(*p);
    }
}

void Level::update(Uint32 dt) const {
    for (auto& b : map->blocks){
        if(b->get_center() > cam.get_updatezone()) continue;
        b->update(dt);
    }
    for (auto& p : players){
        p->update(dt);
    }
}


void Level::spawn_player(Vector2D<float> pos){
    players.push_back(new Player(pos.x, pos.y));
    players.back()->set_render_layer(ID::RENDER_LAYER::WORLD_OBJECT);
}
