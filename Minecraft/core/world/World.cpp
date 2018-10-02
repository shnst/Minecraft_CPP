//
//  World.cpp
//  OpenGLPractice1
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

World::World()
:chunkRenderer(new ChunkRenderer())
,chunkManager(new ChunkManager())
,skyboxRenderer(new SkyboxRenderer())
,skybox(new Skybox(500))
,camera(new Camera())
,cameraBindedEntity(nullptr)
{
    auto player = new Player(this);
    player->setPosition(getSpawnPoint());
    entities.push_back(player);
//    cameraBindedEntity = player;
}

World::~World() {
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
    chunkRenderer->render(*camera, *this, chunkManager->getChunks());
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
