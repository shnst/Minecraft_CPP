//
//  ChunkRenderer.hpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/14/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef ChunkRenderer_hpp
#define ChunkRenderer_hpp

#include <list>

#include "Block.hpp"

class Chunk;
class Mesh;
class Texture;
class World;

class ChunkRenderer {
public:
    ChunkRenderer();
    ~ChunkRenderer();
    
    void createMesh(const World& world, const std::vector<std::vector<std::vector<Chunk*>>>& chunks);
    void render(const World& world, const std::vector<std::vector<std::vector<Chunk*>>>& chunks);
private:
    
    Mesh* mesh;
    Texture* texture;
    
    unsigned int vertexBuffer;
    unsigned int uvBuffer;
};

#endif /* ChunkRenderer_hpp */
