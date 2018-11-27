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
#include <unordered_map>

#include "Block.hpp"
#include "Vector3d.hpp"

class Camera;
class Chunk;
class Mesh;
class Shader;
class Texture;
class World;

class ChunkRenderer {
public:
    ChunkRenderer();
    ~ChunkRenderer();
    
    void render(const Camera& camera, const World& world, const std::unordered_map<vec3n, Chunk*>& chunks) const;
    void updateMesh(const std::unordered_map<vec3n, Chunk*>& chunks);
private:
    
    Mesh* mesh;
    Texture* texture;
    Shader* shader;
    
    unsigned int vertexBuffer;
    unsigned int uvBuffer;
};

#endif /* ChunkRenderer_hpp */
