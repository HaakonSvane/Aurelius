//
//  Chunk.hpp
//  Aurelius
//
/*

 Keeping references to the tiles in a sized chunk of the map.
 Chunks contain NxN sized arrays with pointers to blocks.


*/
//  Created by Haakon Svane on 23/01/2020.
//  Copyright © 2020 Haakon Svane. All rights reserved.
//

#pragma once
#include "Sprite.hpp"

class Chunk{
public:
    Chunk(const Surface* map_surf, const Vector2D<Uint8> chunk_indexes);
private:
    static constexpr Uint8 chunk_size = 16;
    const Vector2D<Uint8> chunk_ind;
    const Sprite* tiles[chunk_size*chunk_size];
};
