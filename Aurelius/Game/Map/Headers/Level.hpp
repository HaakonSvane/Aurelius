//
//  Level.hpp
//  Aurelius
//
//  Created by Haakon Svane on 09/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#pragma once
#include <vector>
#include "Camera.hpp"
#include "Map.hpp"
#include "Renderer.hpp"
#include "Vector2D.hpp"
#include "Player.hpp"


class Level{
public:
    Level(const Renderer& rend, Camera& cam, const Map* map);
    ~Level();
    
    void render() const;
    void update(Uint32 dt) const;
    void spawn_player(Vector2D<float> pos);
    
    std::vector<Player*> players;
    Camera& cam;
    const Map* map;
    const Renderer& ren;
    
private:

    
};
