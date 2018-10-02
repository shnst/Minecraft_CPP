//
//  ChunkManager.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/30/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "ChunkManager.hpp"

#include "Chunk.hpp"
#include "Constants.hpp"
#include "DBManager.hpp"
#include "TerrainGenerator.hpp"
#include "Utils.hpp"
#include "Vector3d.hpp"

ChunkManager::ChunkManager()
:terrainGenerator(new TerrainGenerator())
{
    generateChunks();
}

ChunkManager::~ChunkManager() {
    for (auto it=chunks.begin(); it!=chunks.end(); ++it) {
        for (auto it2=(*it).begin(); it2!=(*it).end(); ++it2) {
            for (auto it3=(*it2).begin(); it3!=(*it2).end(); ++it3) {
                Utils::SafeDelete(*it3);
            }
        }
    }
}

const std::vector<std::vector<std::vector<Chunk*>>>& ChunkManager::getChunks() const {
    return chunks;
}

bool ChunkManager::isPassable(const vec3d& coord) const {
    int chunkX = static_cast<int>(coord.x) / NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int chunkY = static_cast<int>(coord.y) / NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int chunkZ = static_cast<int>(coord.z) / NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    if (!doesChunkExist(chunkX, chunkY, chunkZ)) {
        return false;
    }
    return Blocks::isPassable(getBlock(static_cast<int>(coord.x), static_cast<int>(coord.y), static_cast<int>(coord.z)));
}

bool ChunkManager::isBlocked(int worldChunkX, int worldChunkY, int worldChunkZ) const {
    if (worldChunkX < 0 || worldChunkY < 0 || worldChunkZ < 0) {
        // TODO: World bounds
        //        std::cout << "World::isBlocked x:" << x << " y:" << y << " z:" << z << std::endl;
        return true;
    }
    
    int chunkX = worldChunkX / NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int chunkY = worldChunkY / NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int chunkZ = worldChunkZ / NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    if (!doesChunkExist(chunkX, chunkY, chunkZ)) {
        return true;
    }
    
    int blockX = worldChunkX % NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int blockY = worldChunkY % NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int blockZ = worldChunkZ % NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    
    return chunks[chunkX][chunkY][chunkZ]->isBlocked(blockX, blockY, blockZ);
}

void ChunkManager::setBlock(int worldChunkX, int worldChunkY, int worldChunkZ, Blocks::Types block) {
    int chunkX = worldChunkX / NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int chunkY = worldChunkY / NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int chunkZ = worldChunkZ / NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    if (!doesChunkExist(chunkX, chunkY, chunkZ)) {
        return;
    }
    
    int blockX = worldChunkX % NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int blockY = worldChunkY % NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int blockZ = worldChunkZ % NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    chunks[chunkX][chunkY][chunkZ]->setBlock(blockX, blockY, blockZ, block);
}

Blocks::Types ChunkManager::getBlock(int worldChunkX, int worldChunkY, int worldChunkZ) const {
    int chunkX = worldChunkX / NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int chunkY = worldChunkY / NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int chunkZ = worldChunkZ / NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    
    int blockX = worldChunkX % NUMBER_OF_BLOCKS_IN_CHUNK_X;
    int blockY = worldChunkY % NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    int blockZ = worldChunkZ % NUMBER_OF_BLOCKS_IN_CHUNK_Z;
    
    return chunks[chunkX][chunkY][chunkZ]->getBlock(blockX, blockY, blockZ);
}

bool ChunkManager::doesChunkExist(int chunkX, int chunkY, int chunkZ) const {
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

void ChunkManager::generateChunks() {
    // get spawn point
    auto spawnPoint = getSpawnPoint();
    
    auto spawnChunkX = spawnPoint.x / (NUMBER_OF_BLOCKS_IN_CHUNK_X);
    auto spawnChunkY = spawnPoint.y / (NUMBER_OF_BLOCKS_IN_CHUNK_Y);
    auto spawnChunkZ = spawnPoint.z / (NUMBER_OF_BLOCKS_IN_CHUNK_Z);
    
    auto startChunkX = 0;//spawnChunkX - NUMBER_OF_CHUNKS_IN_WORLD_X/2;
    auto startChunkY = 0;//spawnChunkY - NUMBER_OF_CHUNKS_IN_WORLD_Y/2;
    auto startChunkZ = 0;//spawnChunkZ - NUMBER_OF_CHUNKS_IN_WORLD_Z/2;
    
    for (int x=0; x<NUMBER_OF_CHUNKS_IN_WORLD_X; ++x) {
        chunks.push_back(std::vector<std::vector<Chunk*>>());
        for (int y=0; y<NUMBER_OF_CHUNKS_IN_WORLD_Y; ++y) {
            chunks[x].push_back(std::vector<Chunk*>());
            for (int z=0; z<NUMBER_OF_CHUNKS_IN_WORLD_Z; ++z) {
                auto newChunk = new Chunk(vec3n(startChunkX + x, startChunkY + y, startChunkZ + z));
//                if (!DBManager::get().loadChunk(*newChunk)) {
                    // data does not exist
//                    terrainGenerator->generate(*this, *newChunk);
//                }
                chunks[x][y].push_back(newChunk);
            }
        }
    }
    
    for (int x=0; x<NUMBER_OF_CHUNKS_IN_WORLD_X; ++x) {
        for (int y=0; y<NUMBER_OF_CHUNKS_IN_WORLD_Y; ++y) {
            for (int z=0; z<NUMBER_OF_CHUNKS_IN_WORLD_Z; ++z) {
//                auto newChunk = new Chunk(vec3n(startChunkX + x, startChunkY + y, startChunkZ + z));
                //                if (!DBManager::get().loadChunk(*newChunk)) {
                // data does not exist
                terrainGenerator->generate(*this, *chunks[x][y][z]);
                //                }
            }
        }
    }
}


vec3d ChunkManager::getSpawnPoint() const {
    if (true) {
        // found save file
        return vec3d();
    } else {
        auto centerX = NUMBER_OF_BLOCKS_IN_CHUNK_X * NUMBER_OF_CHUNKS_IN_WORLD_X / 2;
        auto centerZ = NUMBER_OF_BLOCKS_IN_CHUNK_Z * NUMBER_OF_CHUNKS_IN_WORLD_Z / 2;
        
        auto numY = NUMBER_OF_BLOCKS_IN_CHUNK_Y * NUMBER_OF_CHUNKS_IN_WORLD_Y;
        
        for (int y=0; y<numY-1; ++y) {
            if (!Blocks::isPassable(getBlock(centerX, y, centerZ)) && Blocks::isPassable(getBlock(centerX, y+1, centerZ))) {
                return vec3d(centerX, y+1, centerZ);
            }
        }
        return vec3d();
    }
}
