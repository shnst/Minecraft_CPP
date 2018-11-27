//
//  TerrainGenerator.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/16/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef TerrainGenerator_hpp
#define TerrainGenerator_hpp

#include <vector>

#include "Vector3d.hpp"

class Chunk;
class PerlinNoise;
class ChunkManager;

class TerrainGenerator {
public:
    TerrainGenerator();
    ~TerrainGenerator();
    
    void generate(ChunkManager& chunkManager, Chunk& chunk);
private:
    void initializeNoises();
    
    int seed;
    std::vector<PerlinNoise*> noises;
};

#endif /* TerrainGenerator_hpp */
