//
//  World.hpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <list>
#include <vector>

#include "Block.hpp"
#include "Drawable.hpp"

class Chunk;
class ChunkRenderer;
class TerrainGenerator;

class World: Drawable {
public:
    World();
    ~World();
    
    void draw() const override;
    bool isBlocked(int x, int y, int z) const;
    void setBlock(int x, int y, int z, Blocks::Types block);
    bool isInside(int x, int y, int z) const;
private:
    void generateChunks();
    
    std::vector<std::vector<std::vector<Chunk*>>> chunks;
    ChunkRenderer* chunkRenderer;
    TerrainGenerator* terrainGenerator;
};

#endif /* World_hpp */
