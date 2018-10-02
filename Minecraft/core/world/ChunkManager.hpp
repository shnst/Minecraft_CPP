//
//  ChunkManager.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/30/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef ChunkManager_hpp
#define ChunkManager_hpp

#include <vector>

#include "Block.hpp"
#include "Vector3d.hpp"

class Chunk;
class TerrainGenerator;

class ChunkManager {
public:
    ChunkManager();
    ~ChunkManager();
    
    const std::vector<std::vector<std::vector<Chunk*>>>& getChunks() const;
    bool isPassable(const vec3d& coord) const;
    bool isBlocked(int worldChunkX, int worldChunkY, int worldChunkZ) const;
    void setBlock(int x, int y, int z, Blocks::Types block);
    Blocks::Types getBlock(int x, int y, int z) const;
    vec3d getSpawnPoint() const;
private:
    bool doesChunkExist(int chunkX, int chunkY, int chunkZ) const;
    void generateChunks();
    
    std::vector<std::vector<std::vector<Chunk*>>> chunks;
    TerrainGenerator* terrainGenerator;
};

#endif /* ChunkManager_hpp */
