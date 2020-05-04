//
//  Renderer.hpp
//  Aurelius
//
//  Created by Haakon Svane on 18/12/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include "Camera.hpp"
#include "UtilitiesSDL.hpp"

class Sprite;
class Renderer{
public:
    Renderer(const Camera& cam);
    bool render_sprite(const Sprite& sprite) const;
private:
    const Camera& camera;

};
