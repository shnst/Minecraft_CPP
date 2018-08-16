//
//  Chunk.hpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/14/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Chunk_hpp
#define Chunk_hpp

#include <array>

#include "Block.hpp"
#include "Constants.hpp"
#include "Vector3d.hpp"

class Chunk {
public:
    Chunk(const vec3n& coords);
    ~Chunk();
    
    const std::array<std::array<std::array<Blocks::Types, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE>& getBlocks() const;
    
    bool isBlocked(int x, int y, int z) const;
    
    const vec3n& getCoords() const;
private:
    vec3n coords;
    
    std::array<std::array<std::array<Blocks::Types, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> blocks;
};

#endif /* Chunk_hpp */
