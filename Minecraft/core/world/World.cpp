//
//  World.cpp
//  MineCraft_CPP
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "World.hpp"

#include <iostream>

#include "Camera.hpp"
#include "Chunk.hpp"
#include "ChunkManager.hpp"
#include "ChunkRenderer.hpp"
#include "DBManager.hpp"
#include "Player.hpp"
#include "Skybox.hpp"
#include "SkyboxRenderer.hpp"
#include "TerrainGenerator.hpp"
#include "Utils.hpp"


std::mutex chunksMutex;

World::World()
:chunkRenderer(new ChunkRenderer())
,chunkManager(new ChunkManager())
,skyboxRenderer(new SkyboxRenderer())
,skybox(new Skybox(500))
,camera(new Camera())
,cameraBindedEntity(nullptr)
,isRunning(true)
{
    auto player = new Player(this);
    player->setPosition(getSpawnPoint());
    entities.push_back(player);
//    cameraBindedEntity = player;
    
    for (int i = 0; i < 1; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        chunkLoadThreads.emplace_back([&]() {
            loadChunks();
        });
    }
}

World::~World() {
    isRunning = false;
    for (auto& thread : chunkLoadThreads) {
        thread.join();
    }
    
    Utils::SafeDelete(chunkManager);
    for (auto it=entities.begin(); it!=entities.end(); ++it) {
        Utils::SafeDelete(*it);
    }
    
    Utils::SafeDelete(chunkRenderer);
    Utils::SafeDelete(skyboxRenderer);
    
    Utils::SafeDelete(skybox);
    
    Utils::SafeDelete(camera);
}

void World::update(double delta) {
    if (cameraBindedEntity != nullptr) {
        camera->setPosition(cameraBindedEntity->getFacePosition());
        camera->setLookat(cameraBindedEntity->getLookat());
    }
}

void World::save() {
    DBManager::get().save(*chunkManager);
}

void World::draw() const {
    chunksMutex.lock();
    chunkRenderer->render(*camera, *this, chunkManager->getChunks());
    chunksMutex.unlock();
    skyboxRenderer->render(*camera, *skybox);
}

Entity* World::getCameraBinidedEntity() {
    return cameraBindedEntity;
}

Camera* World::getCamera() {
    return camera;
}

vec3d World::getSpawnPoint() const {
    return chunkManager->getSpawnPoint();
}

bool World::isPassable(const vec3d& coord) const {
    return chunkManager->isPassable(coord);
}

bool World::isBlocked(int x, int y, int z) const {
    return chunkManager->isBlocked(x, y, z);
}
            
Blocks::Types World::getBlock(int x, int y, int z) const {
    return chunkManager->getBlock(x, y, z);
}

void World::setBlock(int x, int y, int z, Blocks::Types block) {
    chunkManager->setBlock(x, y, z, block);
}

void World::setHitBlock(const vec3d& cameraCoord, const vec3d& hitCoord) {
    std::cout << "World::setHitBlock camera x:" << cameraCoord.x << " y:" << cameraCoord.y << " z:" << cameraCoord.z << std::endl;
    std::cout << "World::setHitBlock hit x:" << hitCoord.x << " y:" << hitCoord.y << " z:" << hitCoord.z << std::endl;
    if (cameraCoord == hitCoord) {
        return;
    }
    
    auto difference = hitCoord - cameraCoord;
    auto differenceLength = difference.length();
    auto steps = cameraCoord;
    
    while (steps.distance(cameraCoord) < hitCoord.distance(cameraCoord)) {
        steps += difference * 0.3 / differenceLength;
        chunkManager->setBlock(steps.x, steps.y, steps.z, Blocks::Air);
    }
    
    chunkManager->setBlock(hitCoord.x, hitCoord.y, hitCoord.z, Blocks::Wood);
    
    if (isPartOfPlane(vec3n(hitCoord.x, hitCoord.y, hitCoord.z))) {
        chunkManager->setBlock(hitCoord.x, hitCoord.y, hitCoord.z, Blocks::Grass);
    }
}

void World::clearAllBlocks() {
    chunkManager->clearAllBlocks();
}

bool World::isPartOfPlane(const vec3n& coord) {
    std::unordered_map<vec3n, bool> memory;
    int depth = 0;
    
    //detectPlaneRecursion(coord, memory, depth);
    
    return depth > 9;
}

void World::detectPlaneRecursion(const vec3n& coord, std::unordered_map<vec3n, bool>& memory, int& depth) {
    if (memory.find(coord) != memory.end()) {
        return;
    }
    auto block = getBlock(coord.x, coord.y, coord.z);
    if (block == Blocks::Air) {
        return;
    }
    
    if (block == Blocks::Grass) {
        depth += 20;
    }
    
    if (++depth > 20) {
        setBlock(coord.x, coord.y, coord.z, Blocks::Grass);
    }
    
    memory[coord] = true;
    
    detectPlaneRecursion(vec3n(coord.x+1, coord.y, coord.z), memory, depth);
    detectPlaneRecursion(vec3n(coord.x-1, coord.y, coord.z), memory, depth);
    detectPlaneRecursion(vec3n(coord.x, coord.y, coord.z+1), memory, depth);
    detectPlaneRecursion(vec3n(coord.x, coord.y, coord.z-1), memory, depth);
    detectPlaneRecursion(vec3n(coord.x+1, coord.y, coord.z+1), memory, depth);
    detectPlaneRecursion(vec3n(coord.x-1, coord.y, coord.z-1), memory, depth);
    detectPlaneRecursion(vec3n(coord.x+1, coord.y, coord.z-1), memory, depth);
    detectPlaneRecursion(vec3n(coord.x-1, coord.y, coord.z+1), memory, depth);
}

void World::loadChunks() {
    std::cout << "World::loadChunks start" << std::endl;
    
    int loadDistance = HORIZONTAL_CHUNK_LOAD_DISTANCE;
    while(isRunning) {
        bool isMeshMade = false;
        int cameraX = camera->getPosition().x / NUMBER_OF_BLOCKS_IN_CHUNK_X;
        int cameraZ = camera->getPosition().z / NUMBER_OF_BLOCKS_IN_CHUNK_Z;
        
//        std::cout << "World::loadChunks cameraX:" << camera->getPosition().x << " cameraZ:" << camera->getPosition().z << std::endl;
        
        {
            int minX = cameraX - loadDistance;
            int minZ = cameraZ - loadDistance;
            int maxX = cameraX + loadDistance;
            int maxZ = cameraZ + loadDistance;
            
            for (int x=minX; x<=maxX; ++x) {
                for (int z=minZ; z<=maxZ; ++z) {
                    for (int y=0; y<WORLD_HEIGHT; ++y) {
                        vec3n chunkCoord(x, y, z);
                        if (!chunkManager->isChunkLoaded(chunkCoord)) {
                            chunksMutex.lock();
                            chunkManager->loadChunk(chunkCoord);
                            chunksMutex.unlock();
                        }
                    }
                }
            }
        }
        
        for (int i=0; i<loadDistance;  ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            int minX = cameraX - i;
            int minZ = cameraZ - i;
            int maxX = cameraX + i;
            int maxZ = cameraZ + i;
            
            for (int x=minX; x<=maxX; ++x) {
                for (int z=minZ; z<=maxZ; ++z) {
                    for (int y=0; y<WORLD_HEIGHT; ++y) {
                        chunksMutex.lock();
                        bool tmp = chunkManager->createChunkMesh(vec3n(x, y, z));
                        chunksMutex.unlock();
                        isMeshMade = isMeshMade ? true : tmp;
                    }
                }
            }
            if (isMeshMade) {
                break;
            }
        }

        if (isMeshMade) {
            chunksMutex.lock();
            chunkRenderer->updateMesh(chunkManager->getChunks());
            chunksMutex.unlock();
        }
    }
}
