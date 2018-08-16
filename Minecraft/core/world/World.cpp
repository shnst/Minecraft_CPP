//
//  World.cpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "World.hpp"

#include "Chunk.hpp"
#include "ChunkRenderer.hpp"
#include "Utils.hpp"

World::World()
:chunk(new Chunk(vec3n(0, 0, 0)))
,chunkRenderer(new ChunkRenderer())
{
    
}

World::~World() {
    Utils::SafeDelete(chunk);
    Utils::SafeDelete(chunkRenderer);
}

void World::draw() const {
    chunkRenderer->render(*chunk);
}
