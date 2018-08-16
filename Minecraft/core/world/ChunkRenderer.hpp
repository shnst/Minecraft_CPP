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

class ChunkRenderer {
public:
    ChunkRenderer();
    ~ChunkRenderer();
    
    void createMesh(const std::list<Chunk*>& chunks);
    void render(const std::list<Chunk*>& chunks);
private:
    bool isBlocked(const Chunk& chunk, int x, int y, int z, BlockFace::Types face) const;
    
    Mesh* mesh;
    
    unsigned int verticesVBO;
    unsigned int textureVBO;
    
};

#endif /* ChunkRenderer_hpp */
