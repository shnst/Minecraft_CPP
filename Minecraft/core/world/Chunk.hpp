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
    
    void setBlock(int x, int y, int z, Blocks::Types blockType);
    
    Blocks::Types getBlock(int x, int y, int z) const;
    const std::array<std::array<std::array<Blocks::Types, NUMBER_OF_BLOCKS_IN_CHUNK_Z>, NUMBER_OF_BLOCKS_IN_CHUNK_Y>, NUMBER_OF_BLOCKS_IN_CHUNK_X>& getBlocks() const;
    bool isBlocked(int x, int y, int z) const;
    const vec3n& getCoords() const;
    bool hasNoised() const;
private:
    bool isInside(int x, int y, int z) const;
    
    bool noised;
    vec3n coords;
    
    std::array<std::array<std::array<Blocks::Types, NUMBER_OF_BLOCKS_IN_CHUNK_Z>, NUMBER_OF_BLOCKS_IN_CHUNK_Y>, NUMBER_OF_BLOCKS_IN_CHUNK_X> blocks;
};

#endif /* Chunk_hpp */
