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

class Chunk;
class PerlinNoise;
class World;

class TerrainGenerator {
public:
    TerrainGenerator();
    ~TerrainGenerator();
    
    void generate(World& world, const std::vector<std::vector<std::vector<Chunk*>>>& chunks);
private:
    void initializeNoises();
    
    int seed;
    std::vector<PerlinNoise*> noises;
};

#endif /* TerrainGenerator_hpp */
