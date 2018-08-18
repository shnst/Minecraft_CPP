//
//  Chunk.cpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/14/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "Chunk.hpp"

#include <iostream>


Chunk::Chunk(const vec3n& coords)
:coords(coords)
{
    for (auto xIt=blocks.begin(); xIt!=blocks.end(); ++xIt) {
        for (auto yIt=(*xIt).begin(); yIt!=(*xIt).end(); ++yIt) {
            for (auto zIt=(*yIt).begin(); zIt!=(*yIt).end(); ++zIt) {
                (*zIt) = Blocks::Types::Air;
            }
        }
    }
}

Chunk::~Chunk() {
    
}

const std::array<std::array<std::array<Blocks::Types, NUMBER_OF_BLOCKS_IN_CHUNK_Z>, NUMBER_OF_BLOCKS_IN_CHUNK_Y>, NUMBER_OF_BLOCKS_IN_CHUNK_X>& Chunk::getBlocks() const {
    return blocks;
}

const vec3n& Chunk::getCoords() const {
    return coords;
}

bool Chunk::isBlocked(int x, int y, int z) const {
    if (!isInside(x, y, z)) {
        return false;
    }
    
//    std::cout << "Chunk::isBlocked x:" << x << " y:" << y << " z:" << z << std::endl;
    return !Blocks::isTransparent(blocks[x][y][z]);
}

bool Chunk::isInside(int x, int y, int z) const {
    if (x < 0 || NUMBER_OF_BLOCKS_IN_CHUNK_X <= x) {
        return false;
    }
    if (y < 0 || NUMBER_OF_BLOCKS_IN_CHUNK_Y <= y) {
        return false;
    }
    if (z < 0 || NUMBER_OF_BLOCKS_IN_CHUNK_Z <= z) {
        return false;
    }
    return true;
}

Blocks::Types Chunk::getBlock(int x, int y, int z) const {
    return blocks[x][y][z];
}

void Chunk::setBlock(int x, int y, int z, Blocks::Types blockType) {
    if (!isInside(x, y, z)) {
        return;
    }
    blocks[x][y][z] = blockType;
}

bool Chunk::hasNoised() const {
    return noised;
}
