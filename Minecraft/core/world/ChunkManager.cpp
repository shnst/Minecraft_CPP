//
//  ChunkManager.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/30/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "ChunkManager.hpp"

#include <iostream>

#include "Chunk.hpp"
#include "Constants.hpp"
#include "DBManager.hpp"
#include "TerrainGenerator.hpp"
#include "Utils.hpp"
#include "Vector3d.hpp"

inline int worldToBlockIndex(double world, int numBlocksInChunk) {
    if (world >= 0) {
        return static_cast<int>(world) % numBlocksInChunk;
    } else {
        int modded = abs(static_cast<int>(world)) % numBlocksInChunk;
        return modded == 0 ? 0 : numBlocksInChunk - modded;
    }
//    return world >= 0 ? static_cast<int>(world) % numBlocksInChunk : numBlocksInChunk - abs(static_cast<int>((world))) % numBlocksInChunk;
}
inline int worldToBlockIndex2(double world, int numBlocksInChunk) {
    return world >= 0 ? static_cast<int>(world) % numBlocksInChunk : numBlocksInChunk - abs(static_cast<int>((world))) % numBlocksInChunk;
}

ChunkManager::ChunkManager()
:terrainGenerator(new TerrainGenerator())
{
}

ChunkManager::~ChunkManager() {
    for (auto& chunk : chunks) {
        Utils::SafeDelete(chunk.second);
    }
}

const std::unordered_map<vec3n, Chunk*>& ChunkManager::getChunks() const {
    return chunks;
}

bool ChunkManager::isPassable(const vec3d& worldCoord) const {
    if (!isWorldCoordinateInsideCurrentChunks(worldCoord.x, worldCoord.y, worldCoord.z)) {
        return false;
    }
    
    return Blocks::isPassable(getBlock(worldCoord.x, worldCoord.y, worldCoord.z));
}

bool ChunkManager::isBlocked(double worldX, double worldY, double worldZ) const {
    if (!isWorldCoordinateInsideCurrentChunks(worldX, worldY, worldZ)) {
        return true;
    }
    
    int chunkX = floor(worldX / NUMBER_OF_BLOCKS_IN_CHUNK_X);
    int chunkY = floor(worldY / NUMBER_OF_BLOCKS_IN_CHUNK_Y);
    int chunkZ = floor(worldZ / NUMBER_OF_BLOCKS_IN_CHUNK_Z);
    
    int blockX = worldToBlockIndex(worldX, NUMBER_OF_BLOCKS_IN_CHUNK_X);
    int blockY = worldToBlockIndex(worldY, NUMBER_OF_BLOCKS_IN_CHUNK_Y);
    int blockZ = worldToBlockIndex(worldZ, NUMBER_OF_BLOCKS_IN_CHUNK_Z);
    
    vec3n key(chunkX, chunkY, chunkZ);
    return chunks.at(key)->isBlocked(blockX, blockY, blockZ);
}

void ChunkManager::setBlock(double worldX, double worldY, double worldZ, Blocks::Types block) {
    std::cout << "world x:" << worldX << " y:" << worldY << " z:" << worldZ << std::endl;
    if (!isWorldCoordinateInsideCurrentChunks(worldX, worldY, worldZ)) {
        return;
    }
    
    int chunkX = floor(worldX / NUMBER_OF_BLOCKS_IN_CHUNK_X);
    int chunkY = floor(worldY / NUMBER_OF_BLOCKS_IN_CHUNK_Y);
    int chunkZ = floor(worldZ / NUMBER_OF_BLOCKS_IN_CHUNK_Z);
    
    int blockX = worldToBlockIndex(worldX, NUMBER_OF_BLOCKS_IN_CHUNK_X);
    int blockY = worldToBlockIndex(worldY, NUMBER_OF_BLOCKS_IN_CHUNK_Y);
    int blockZ = worldToBlockIndex(worldZ, NUMBER_OF_BLOCKS_IN_CHUNK_Z);
    
    vec3n key(chunkX, chunkY, chunkZ);
    return chunks[key]->setBlock(blockX, blockY, blockZ, block);
}

Blocks::Types ChunkManager::getBlock(double worldX, double worldY, double worldZ) const {
    if (!isWorldCoordinateInsideCurrentChunks(worldX, worldY, worldZ)) {
        return Blocks::Brick;
    }
    
    int chunkX = floor(worldX / NUMBER_OF_BLOCKS_IN_CHUNK_X);
    int chunkY = floor(worldY / NUMBER_OF_BLOCKS_IN_CHUNK_Y);
    int chunkZ = floor(worldZ / NUMBER_OF_BLOCKS_IN_CHUNK_Z);
    
    int blockX = worldToBlockIndex(worldX, NUMBER_OF_BLOCKS_IN_CHUNK_X);
    int blockY = worldToBlockIndex(worldY, NUMBER_OF_BLOCKS_IN_CHUNK_Y);
    int blockZ = worldToBlockIndex(worldZ, NUMBER_OF_BLOCKS_IN_CHUNK_Z);
    
    vec3n key(chunkX, chunkY, chunkZ);
    return chunks.at(key)->getBlock(blockX, blockY, blockZ);
}

bool ChunkManager::isWorldCoordinateInsideCurrentChunks(double worldX, double worldY, double worldZ) const {
    int chunkX = floor(worldX / NUMBER_OF_BLOCKS_IN_CHUNK_X);
    int chunkY = floor(worldY / NUMBER_OF_BLOCKS_IN_CHUNK_Y);
    int chunkZ = floor(worldZ / NUMBER_OF_BLOCKS_IN_CHUNK_Z);
    return isChunkLoaded(vec3n(chunkX, chunkY, chunkZ));
}

bool ChunkManager::isChunkLoaded(const vec3n& coord) const {
    return chunks.find(coord) != chunks.end();
}

void ChunkManager::loadChunk(const vec3n& coord) {
    if (chunks.find(coord) != chunks.end()) {
        std::cout << "ChunkManager::loadChunk ERROR:chunk already loaded" << std::endl;
        return;
    }
    auto newChunk = new Chunk(coord);
    chunks.insert(std::make_pair(coord, newChunk));
#ifndef MAPPING_MODE
    terrainGenerator->generate(*this, *newChunk);
#endif
}

bool ChunkManager::createChunkMesh(const vec3n& coord) {
    auto it = chunks.find(coord);
    if (it == chunks.end()) {
        return false;
    }
    if (it->second->hasMeshCreated()) {
        return false;
    }
    it->second->createMesh(*this);
    return true;
}

vec3d ChunkManager::getSpawnPoint() const {
    if (true) {
        // found save file
        return vec3d();
    } else {
        return vec3d();
    }
}

void ChunkManager::updateChunksCoord(const vec3d& playerCoord) {
    
}

void ChunkManager::clearAllBlocks() {
    for (auto& chunk : chunks) {
        chunk.second->clearAllBlocks();
    }
}
