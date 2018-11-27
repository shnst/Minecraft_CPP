//
//  World.hpp
//  MineCraft_CPP
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <list>
#include <unordered_map>
#include <thread>
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
    
    void setHitBlock(const vec3d& position, const vec3d& hitCoord);
    
    void clearAllBlocks();
private:
    void loadChunks();
    bool isPartOfPlane(const vec3n& coord);
    void detectPlaneRecursion(const vec3n& coord, std::unordered_map<vec3n, bool>& memory, int& depth);
    
    ChunkManager* chunkManager;
    Skybox* skybox;
    std::list<Entity*> entities;
    Entity* cameraBindedEntity;
    
    Camera* camera;
    
    SkyboxRenderer* skyboxRenderer;
    ChunkRenderer* chunkRenderer;
    
    
    std::vector<std::thread> chunkLoadThreads;
    
    bool isRunning;
};

#endif /* World_hpp */
