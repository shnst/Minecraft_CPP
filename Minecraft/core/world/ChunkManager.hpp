//
//  ChunkManager.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/30/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef ChunkManager_hpp
#define ChunkManager_hpp

#include <unordered_map>
#include <vector>

#include "Block.hpp"
#include "Vector3d.hpp"

class Chunk;
class TerrainGenerator;

class ChunkManager {
public:
    ChunkManager();
    ~ChunkManager();
    
    const std::unordered_map<vec3n, Chunk*>& getChunks() const;
    bool isPassable(const vec3d& coord) const;
    bool isBlocked(double worldX, double worldY, double worldZ) const;
    void setBlock(double worldX, double worldY, double worldZ, Blocks::Types block);
    Blocks::Types getBlock(double worldX, double worldY, double worldZ) const;
    vec3d getSpawnPoint() const;
    bool isWorldCoordinateInsideCurrentChunks(double worldX, double worldY, double worldZ) const;
    void updateChunksCoord(const vec3d& playerCoord);
    
    void clearAllBlocks();
    
    bool isChunkLoaded(const vec3n& coord) const;
    void loadChunk(const vec3n& coord);
    bool createChunkMesh(const vec3n& coord);
    
    void updateMesh();
private:
    
    vec3n chunksCoord;
    std::unordered_map<vec3n, Chunk*> chunks;
    
    TerrainGenerator* terrainGenerator;
};

#endif /* ChunkManager_hpp */
