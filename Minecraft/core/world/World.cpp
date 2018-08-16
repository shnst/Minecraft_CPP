//
//  World.cpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "World.hpp"

#include <iostream>

#include "Chunk.hpp"
#include "ChunkRenderer.hpp"
#include "Utils.hpp"

World::World()
:chunkRenderer(new ChunkRenderer())
{
    generateChunks();
}

World::~World() {
    for (auto it=chunks.begin(); it!=chunks.end(); ++it) {
        Utils::SafeDelete((*it));
    }
    Utils::SafeDelete(chunkRenderer);
}

void World::draw() const {
    std::cout << "World::draw number of chunks:" << chunks.size() << std::endl;
//    for (auto it=chunks.begin(); it!=chunks.end(); ++it) {
//        chunkRenderer->render(*(*it));
//    }
    chunkRenderer->render(chunks);
}

void World::generateChunks() {
    for (int x=0; x<NUMBER_OF_CHUNKS_IN_WORLD_X; ++x) {
        for (int y=0; y<NUMBER_OF_CHUNKS_IN_WORLD_Y; ++y) {
            for (int z=0; z<NUMBER_OF_CHUNKS_IN_WORLD_Z; ++z) {
                chunks.push_back(new Chunk(vec3n(x, y, z)));
            }
        }
    }
}
