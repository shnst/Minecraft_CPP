//
//  World.cpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "World.hpp"

#include <iostream>

#include "Chunk.hpp"
#include "ChunkRenderer.hpp"
#include "Skybox.hpp"
#include "SkyboxRenderer.hpp"
#include "TerrainGenerator.hpp"
#include "Utils.hpp"

World::World()
:chunkRenderer(new ChunkRenderer())
,terrainGenerator(new TerrainGenerator())
,skyboxRenderer(new SkyboxRenderer())
,skybox(new Skybox(500))
{
    generateChunks();
}

World::~World() {
    for (auto it=chunks.begin(); it!=chunks.end(); ++it) {
        for (auto it2=(*it).begin(); it2!=(*it).end(); ++it2) {
            for (auto it3=(*it2).begin(); it3!=(*it2).end(); ++it3) {
                Utils::SafeDelete(*it3);
            }
        }
    }
    Utils::SafeDelete(chunkRenderer);
    
    Utils::SafeDelete(skyboxRenderer);
    Utils::SafeDelete(skybox);
}

void World::draw() const {
//    std::cout << "World::draw number of chunks:" << chunks.size() << std::endl;
    
    chunkRenderer->render(*this, chunks);
    skyboxRenderer->render(*skybox);
}

void World::generateChunks() {
    for (int x=0; x<NUMBER_OF_CHUNKS_IN_WORLD_X; ++x) {
        chunks.push_back(std::vector<std::vector<Chunk*>>());
        for (int y=0; y<NUMBER_OF_CHUNKS_IN_WORLD_Y; ++y) {
            chunks[x].push_back(std::vector<Chunk*>());
            for (int z=0; z<NUMBER_OF_CHUNKS_IN_WORLD_Z; ++z) {
                chunks[x][y].push_back(new Chunk(vec3n(x, y, z)));
            }
        }
    }
    
    terrainGenerator->generate(*this, chunks);
}

bool World::isBlocked(int x, int y, int z) const {
    if (x < 0 || y < 0 || z < 0) {
        // TODO: World bounds
//        std::cout << "World::isBlocked x:" << x << " y:" << y << " z:" << z << std::endl;
        return true;
    }
    
    int chunkX = x / NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int chunkY = y / NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int chunkZ = z / NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    if (!isInside(chunkX, chunkY, chunkZ)) {
        return true;
    }
    
    int blockX = x % NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int blockY = y % NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int blockZ = z % NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    
    return chunks[chunkX][chunkY][chunkZ]->isBlocked(blockX, blockY, blockZ);
}

void World::setBlock(int x, int y, int z, Blocks::Types block) {
    int chunkX = x / NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int chunkY = y / NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int chunkZ = z / NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    if (!isInside(chunkX, chunkY, chunkZ)) {
        return;
    }

    int blockX = x % NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int blockY = y % NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int blockZ = z % NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    chunks[chunkX][chunkY][chunkZ]->setBlock(blockX, blockY, blockZ, block);
}

bool World::isInside(int chunkX, int chunkY, int chunkZ) const {
    if (chunkX < 0 || chunks.size() <= chunkX) {
        return false;
    }
    if (chunkY < 0 || chunkY >= chunks.front().size()) {
        return false;
    }
    if (chunkZ < 0 || chunkZ >= chunks.front().front().size()) {
        return false;
    }
    
    return true;
}
