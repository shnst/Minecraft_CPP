//
//  Chunk.cpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/14/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "Chunk.hpp"


Chunk::Chunk(const vec3n& coords) {
    for (auto xIt=blocks.begin(); xIt!=blocks.end(); ++xIt) {
        for (auto yIt=(*xIt).begin(); yIt!=(*xIt).end(); ++yIt) {
            for (auto zIt=(*yIt).begin(); zIt!=(*yIt).end(); ++zIt) {
                (*zIt) = Blocks::Types::Soil;
            }
        }
    }
}

Chunk::~Chunk() {
    
}

const std::array<std::array<std::array<Blocks::Types, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE>& Chunk::getBlocks() const {
    return blocks;
}

const vec3n& Chunk::getCoords() const {
    return coords;
}

bool Chunk::isBlocked(int x, int y, int z) const {
    if (x < 0 || CHUNK_SIZE <= x) {
        return false;
    }
    if (y < 0 || CHUNK_SIZE <= y) {
        return false;
    }
    if (z < 0 || CHUNK_SIZE <= z) {
        return false;
    }
    
//    return isTransparent(blocks[x][y][z])
    return true;
}
