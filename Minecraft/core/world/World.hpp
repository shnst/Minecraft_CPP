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
#include "Updatable.hpp"
#include "Vector3d.hpp"

class Camera;
class ChunkManager;
class ChunkRenderer;
class Entity;
class Skybox;
class SkyboxRenderer;
class TerrainGenerator;

class World: Drawable, Updatable {
public:
    World();
    ~World();
    
    void update(double delta) override;
    
    void save();
    
    Entity* getCameraBinidedEntity();
    void setBlock(int x, int y, int z, Blocks::Types block);
    
    Camera* getCamera();
    
    vec3d getSpawnPoint() const;
    Blocks::Types getBlock(int x, int y, int z) const;
    
    void draw() const override;
    bool isBlocked(int x, int y, int z) const;
    bool doesChunkExist(int chunkX, int chunkY, int chunkZ) const;
    bool isPassable(const vec3d& coord) const;
    
private:
    
    ChunkManager* chunkManager;
    Skybox* skybox;
    std::list<Entity*> entities;
    Entity* cameraBindedEntity;
    
    Camera* camera;
    
    SkyboxRenderer* skyboxRenderer;
    ChunkRenderer* chunkRenderer;
};

#endif /* World_hpp */
